// put your setup code here, to run once:
/*
 
                                                          SoftSerial (Saídas Digitais)      Objeto EBYTE (Saídas Digitais)    
                                                          ** 7,6 - LORA Rx, Tx              ** 10, 9, 8, - AUX, M0, M1    *O pino 10 deve estar presente na declaração da função, mas
 */                                                                                                                      //seu uso fisicamente é opcional

#include <EBYTE.h>
#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial mySerial(7,6); //Rx - Tx

EBYTE emissor(&mySerial, 9, 8, 10);

void setup() {
  
Serial.begin(9600); //Inicia a serial física
mySerial.begin(9600); //Inicia a serial lógica

iniciarLORA();
}

void loop() 
 {  
            percursoFake();
 }


 void iniciarLORA () 
  {
     mySerial.listen();                   
       
     emissor.init();                                            //Inicia o módulo

     emissor.SetMode(MODE_NORMAL);                              //Modo de funcionamento do módulo
     emissor.SetAddressH(0);                                    //Endereço H(?)
     emissor.SetAddressL(0);                                    //Endereço L(?)
     emissor.SetAirDataRate(ADR_2400);                          //AirDataRate 2400kbps
     emissor.SetUARTBaudRate(UDR_9600);                         //BAUDRate 9600
     emissor.SetChannel(23);                                    //Canal 23
     emissor.SetParityBit(PB_8N1);                              //Bit Paridade 8N1
     emissor.SetTransmitPower(OPT_TP20);                        //Força de transmissão 20db
     emissor.SetWORTIming(OPT_WAKEUP250);                       //WakeUP Time(?) 2000
     emissor.SetFECMode(OPT_FECENABLE);                         //FEC(?) ENABLE
     emissor.SetTransmissionMode(OPT_FMDISABLE);                //Transmission Mode
     emissor.SetPullupMode(OPT_IOPUSHPULL);                     //IO Mode PushPull
     emissor.SaveParameters(PERMANENT);                         //Salva as modificações na memória do módulo
         
     emissor.PrintParameters();                                 //Exibe os parâmetros configurados
  } //Fim iniciarLORA 

  void percursoFake() 
 {

   int vel = 100;
   int LO = 4660;
   int NS = 2370;

   while (LO > 1880)
    {
     LO -= vel ;
     mySerial.print("[06,-26.242370,-48.64"+(String)LO+"]*");
     delay(random(1000, 1500));
    }
   
   while (NS < 5150)
    {
     LO = 1880;
     NS += vel;
     mySerial.print("[06,-26.24"+(String)NS+",-48.641880]*");
     delay(random(1000, 1500));
    }
    
   while (LO < 4660)
    {
     NS = 5150;
     LO += vel;
     mySerial.print("[06,-26.245150,-48.64"+(String)LO+"]*");
     delay(random(1000, 1500));
    }
    
   while (NS > 2370)
    {
     NS -= vel;
     mySerial.print("[06,-26.24"+(String)NS+",-48.644660]*");
     delay(random(1000, 1500));
    }
}
