#include <Arduino.h>
#define GPS_RX 12
#define GPS_TX 15
#define PMTK_LOCUS_STARTLOG  "$PMTK185,0*22"
#define PMTK_LOCUS_LOGSTARTED "$PMTK001,185,3*3C"
#define PMTK_LOCUS_QUERY_STATUS "$PMTK183*38"
#define PMTK_LOCUS_ERASE_FLASH "$PMTK184,1*22"
#define LINE "-------------------------------------------------------"
#define LOCUS_OVERLAP 0
#define LOCUS_FULLSTOP 11

int incomingByte = 0; 

#include <axp20x.h>

//TinyGPSPlus gps;
HardwareSerial GPS(1);
AXP20X_Class axp;

void setup() {
  Serial.begin(115200);
 // Serial1.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.write("test\n");
  Wire.begin(21, 22);
  if (!axp.begin(Wire, AXP192_SLAVE_ADDRESS)) {
    Serial.println("AXP192 Begin PASS");
  } else {
    Serial.println("AXP192 Begin FAIL");
  }
  axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
  axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON);
  axp.setPowerOutPut(AXP192_EXTEN, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
  GPS.begin(9600, SERIAL_8N1, 34, 12);   //17-TX 18-RX
  GPS.print("$PMTK185,0*22");

}


void loop() {
  while (GPS.available()) {
    Serial.write(GPS.read());
  }
  while (Serial.available()) {
    incomingByte = Serial.read();
    Serial.println(incomingByte, DEC);
    switch (incomingByte)
    {
    case '1':
            Serial.println(LINE);
             Serial.println(PMTK_LOCUS_STARTLOG);
            GPS.println(PMTK_LOCUS_STARTLOG);
            break;
    case '2':
           Serial.println(LINE);
           Serial.println(PMTK_LOCUS_LOGSTARTED);
            GPS.println(PMTK_LOCUS_LOGSTARTED);
            break;
    case '3':
            Serial.println(LINE);
            Serial.println(PMTK_LOCUS_QUERY_STATUS);
            GPS.println(PMTK_LOCUS_QUERY_STATUS);
            break;
    case '4':
            Serial.println(LINE);
            Serial.println(PMTK_LOCUS_ERASE_FLASH);
            GPS.println(PMTK_LOCUS_ERASE_FLASH);
            break;
    }
  }
}