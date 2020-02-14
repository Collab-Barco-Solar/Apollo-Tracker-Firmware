
// Bibliotecas utilizadas
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>


#define NUMERO_BARCO 7 // Número da embarcação


// Pinos do LoRa  e GPS na TTGO T-beam
#define SCK     5     // GPIO5  -- LoRa SX1278's SCK
#define MISO    19    // GPIO19 -- LoRa SX1278's MISnO
#define MOSI    27    // GPIO27 -- LoRa SX1278's MOSI
#define SS      18    // GPIO18 -- LoRa SX1278's CS
#define RST     14    // GPIO14 -- LoRa SX1278's RESET
#define DI0     26    // GPIO26 -- LoRa SX1278's IRQ(Interrupt Request)

#define RXPin    15  // Neo6M RX pin
#define TXPin    12  // Neo6M TX pin
#define GPSBaud 9600 // Neo6M Baud rate

// Parâmetros de transmissão do protocolo LoRa
#define FREQ  915E6   // Operating LoRa frequency
#define SF      7     // Operating LoRa Spread Factor
#define BAND  125E3   // Operating LoRa Bandwidth
#define TXPOWER 20    // Operating LoRa Transmition Power
#define CODINGRATE 8  // LoRa Coding Rate (between 4 and 8)
#define BAUD 2000000  // BAUD serial rate

TinyGPSPlus gps;      // GPS object
HardwareSerial ss(2); // Hardware Serial comunication object

double LatitudeGPS( ) {
  return gps.location.lat();
}

double LongitudeGPS( ) {
  return gps.location.lng();
}
char CSV_Separator() {
  return (';');
}

void setup() {

  Serial.begin(BAUD);
  ss.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin); // GPS serial communication


  while (!Serial);
  Serial.println();
  Serial.print("Barco ");
  Serial.println(NUMERO_BARCO);

  SPI.begin(SCK, MISO, MOSI, SS); // LoRa SPI communication
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(FREQ)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSignalBandwidth(BAND);
  LoRa.setTxPower(TXPOWER);
  LoRa.enableCrc();
  LoRa.setCodingRate4(CODINGRATE);

  Serial.println("Initialization: ok");

  delay(1500);
}

void loop() {

  // Create and send packet

  // Update GPS

  gps.encode(ss.read());
  LoRa.beginPacket();
  // Write GPS Latitude
  LoRa.print(LatitudeGPS());
  LoRa.print(CSV_Separator());
  // Write GPS Longitude
  LoRa.print(LongitudeGPS());
  LoRa.print(CSV_Separator());
  // Write GPS speed
  double boat_speed = gps.speed.knots();
  LoRa.print(boat_speed);
  LoRa.print(CSV_Separator());

  LoRa.endPacket();

  delay(10);
}
