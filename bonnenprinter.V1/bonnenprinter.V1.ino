/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.

  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/
#include <TimeLib.h>
#include "Adafruit_Thermal.h"






// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------
int bedrag = 100;
String Bank = "Rabobank";
String Tijd = "12:00";
String Kaart = "NL27*****3515";
String incomingByte;
String readstring;

void setup() {
  Serial.begin(9600);
  
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  
  
  
  
}

void loop() {

 
  
if (Serial.available() > 0){
    incomingByte = Serial.readStringUntil('\n');
    
    //char c = Serial.read();
    //readstring += c;
    
    //if(incomingByte == "Ja"){
      printReceipt();
      Serial.write("Aan het printen");
      
    
 
 
    }
//}
if (readstring.length() >0)
{
  Serial.println(readstring);
  
}
delay(500);

}



  // Bank info
  void printReceipt(){
    mySerial.begin(9600);
  printer.begin();
    
  
  printer.justify('C');
  printer.boldOn();
  printer.setSize('L');
  printer.println("CINA");
  printer.println("_____________");
  printer.justify('L');
  printer.setSize('M');

  
  
 // printer.boldOff();


  
  
  printer.print(incomingByte);

  printer.println("\n------");
  delay(1000);
  printer.print("Kaart: " +Kaart);
  delay(1000);
  printer.println("\n------");
  delay(1000);
  
  


  // Barcode examples:
  // CODE39 is the most common alphanumeric barcode:
  //printer.printBarcode("Bitch", CODE39);
  //printer.setBarcodeHeight(100);
  // Print UPC line on product barcodes:
  //printer.printBarcode("123456789123", UPC_A);

  
  printer.println(F("Tot ziens!"));
  printer.feed(2);

  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
  }
  


    
  
