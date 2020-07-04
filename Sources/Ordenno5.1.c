/************************************************************************************************
* MIGUEL ALEJANDRO RIVERA NIÑO                                                                 	*
* Este programa se encarga de hacer el control de las valvulas de succion de un ordeño simple   *
* de dos posiciones FEAR y REAR, lo cual hace que las ubres de las vacas sean succionadas solo  *
* adelante y atras, con la posibilidad de configurar por medio de dos (2) DIP switch tanto el   *
* RATIO y RATE del ciclo respectivamente.                                                       *
*                                                                                              	*
*versiones:                                                                                    	*
*v1.1:                                                                                         	* 
* -se agrego la documentacion del programa para posteriores versiones y cambios en el codigo    *
* -se aclaro de nuevo cual DIP pertenece al RATIO y cual al RATE, se vuelve a configurar el     *
* tiempo de apagado de las valvulas debido a que el cliente pidio volver a tenerlos en cuenta   *
* cuando habia pedido quitarlos desde un principio.												*
*                                                                                               *
*v2.0:																							*
* -se cambia el uso de puertos GPIO como salidas para las valvulas, para usar el modulo TPM		*
*  con sus ambos canales para un mejor control de las valvulas, se debe cambiar la PCB para		*
*  poder usar los puertos del modulo TPM adecuadamente, también se cambian los puertos de los	*
*  DIP para liberar el TPMCH0, dejando las entradas de los DIP en el PTA1-PTA3 y PTB0-PTB2		*
*  para RATE y RATIO respectivamente.															*
*																								*
************************************************************************************************/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "main_asm.h" /* interface to the assembly module */

//VARIABLES
int milli=0;
int i=0;
int DIP1=0; //RATIO
int DIP2=0; //RATE
int maskA=0;
int maskB=0;
unsigned long Val=0;
unsigned long RATIO=0;
unsigned long RATIO2=0;
unsigned int RATE=0;
int FlagCH0=0;
//FUNCIONES
void tiempo(int);
void retardo1m(void);
void ConfigIni(void);
void ConfigGPIO(void);
void ConfigPWM(void);
void SetPWM(void);
void Stop(void);
void retardo(void);
void LeerDIP1(void);
void LeerDIP2(void);
void tiempoD(int millisD);
void Stop2(void);


void main(void) {
	
	  /* include your code here */
	  asm_main();		/* call the assembly function */
	  ConfigIni();
	  Stop();
	  ConfigPWM();
	  SetPWM();
	  EnableInterrupts;
  //-----------------------------
  //	LOOP Infinito POLLING
  //-----------------------------
  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
void ConfigIni(){
	  milli=0;
	  ConfigGPIO();
	  LeerDIP2();
	  LeerDIP1();
	  tiempo(10);
	  
}
void tiempo(int milli){
	for(i=0;i<milli;i++){
		retardo1m();
	}
	milli=0;
}
void retardo1m(){
	retardo();
}
void ConfigGPIO(){
	//SOPT1
	SOPT1=0x53;
	//SOPT1_RSTPE=1;		//1=Pin RESET //0= Pin PTA5
	//SOPT1_COPE=0;
	
	// 0= input // 1= output
	//PUERTO B
	PTBD=0x00;
	PTBDD=0b11000000;
	//PTBDS=0b01100000;
	PTBD=0x00;
	
	//PUERTO A
	PTAD=0b00000000;
	PTADD=0b11111000;
	//PTASE=0b00000000;
	PTAD=0x00;
}	
void Stop(){
	tiempo(1000);
	PTBD_PTBD7=1;
	tiempo(1000);
	PTBD_PTBD7=0;
}
void LeerDIP1(){ //RATIO
	PTBD=0x00;
	//char DIP_1=PTB
	maskB=0b00000111;
	DIP1=(maskB&PTBD);
	Val=RATE;
	switch (DIP1){
		case 7:
			RATIO=(Val/2);	//50 //50
			RATIO2=((Val*40)/100);	//60 //40
			break;
		case 6:
			RATIO=(Val*55)/100;	//55 //45
			RATIO2=(Val*40)/100;	//60 //40
			break;
		case 5:
			RATIO=(Val/2);	//50 //50
			RATIO2=(Val/2);	//50 //50
			break;
		case 4:
			RATIO=(Val*60)/100;	//60 //40
			RATIO2=(Val*40)/100;	//60 //40
			break;
		case 3:
			RATIO=(Val*65)/100;	//65 //35
			RATIO2=(Val*35)/100;	//65 //35
			break;
		case 2:
			RATIO=(Val*70)/100;	//70 //30
			RATIO2=(Val*30)/100;	//70 //30
			break;
		default:
			Stop2();
			//break;
	}
}
void LeerDIP2(){ //RATE
	PTAD=0x00;
	maskA=0b00000111;
	DIP2=(maskA&PTAD);
	switch (DIP2){
		case 7:
			RATE=18300;		// 55 puls/min		
			break;
		case 6:
			RATE=16800;		// 60 puls/min
			break;
		case 5:
			RATE=11200;		// 90 puls/min
			break;
		case 4:
			RATE=8404;		// 120 puls/min
			break;
		case 3:
			RATE=6700;		// 150 puls/min
			break;
		case 2:
			RATE=5600;		// 180 puls/min
			break;
		default:
			Stop2();
			//break;
		}
}
void Stop2(){
	for(;;){
		PTBD_PTBD7=1;
		tiempo(500);
		PTBD_PTBD7=0;
		tiempo(500);
	}
}
void ConfigPWM(){
	TPMSC=0b00101111;
	TPMMOD=RATE;
	TPMC0SC=0b01001000;
	TPMC0V=RATIO;
	TPMC1SC=0b00000100;
	TPMC1V=RATIO2;
}
void SetPWM(){
	
}
interrupt 5 void Trans(){
	PTBD_PTBD6=!PTBD_PTBD6;
	FlagCH0=TPMC0SC;
	TPMC0SC_CH0F=0;
}
