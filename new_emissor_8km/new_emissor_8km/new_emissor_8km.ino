// put your setup code here, to run once:
/*
 
 SD card attached to SPI bus as follows:                  SoftSerial (Saídas Digitais)      Objeto EBYTE (Saídas Digitais)    LEDs Indicativos (Saídas Analógicas)
  ** MOSI - pin 11                                        ** 2,3 - GPS Rx, Tx               ** 7, 8, 9 - M0, M1, AUX          ** A1 - LED Mensagem Recebida
  ** MISO - pin 12                                        ** 5,6 - LORA Rx, Tx                                                ** A2 - LED GPS
  ** CLK - pin 13                                                                                                             ** A3 - LED LORA
  ** CS - pin 10 (for MKRZero SD: SDCARD_SS_PIN)
  
 */

#include <EBYTE.h>
#include <SoftwareSerial.h>

//String mensagem = "[07,-12.345678,-ab.cdefgh]";


#define DEBUG true

SoftwareSerial mySerial(5,6); //Rx - Tx

EBYTE emissor(&mySerial, 7, 8, 9);

void setup() {
  
Serial.begin(9600); //Inicia a serial física
mySerial.begin(9600); //Inicia a serial lógica

iniciarLORA();
}

void loop() 
 {  
             //mySerial.println(mensagem);
             percursoFake();
             //delay(random(1000, 2000));
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
     emissor.SetTransmitPower(OPT_TP30);                        //Força de transmissão 30db
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
     mySerial.print("[07,-26.242370,-48.64"+(String)LO+"]*");
     delay(random(1000, 1500));
    }
   
   while (NS < 5150)
    {
     LO = 1880;
     NS += vel;
     mySerial.print("[07,-26.24"+(String)NS+",-48.641880]*");
     delay(random(1000, 1500));
    }
    
   while (LO < 4660)
    {
     NS = 5150;
     LO += vel;
     mySerial.print("[07,-26.245150,-48.64"+(String)LO+"]*");
     delay(random(1000, 1500));
    }
    
   while (NS > 2370)
    {
     NS -= vel;
     mySerial.print("[07,-26.24"+(String)NS+",-48.644660]*");
     delay(random(1000, 1500));
    }
}
