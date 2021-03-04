/*

kaart  21 E8 83 1A
chip   67 C9 5C 34


*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop()
{
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent())
  {
    read();
  }
  //read();
}

void read() {
  // Select one of the cards
  //  if ( ! mfrc522.PICC_ReadCardSerial())
  //  {
  //    return;
  //  }
  mfrc522.PICC_ReadCardSerial();
  //Show UID on serial monitor

  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "21 E8 83 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");

  }

  else   {
    Serial.println(" Access denied");
  }
  //Serial.println(content);
  delay(500);
}
