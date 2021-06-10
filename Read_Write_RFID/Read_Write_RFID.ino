#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <string.h>
#include <Keypad.h> //keypad library

#define RST_PIN 9
#define SS_PIN 10

boolean blocking = false;
String data_serial = "";
String data_rfid = "";
// char output[32];
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

const byte ROWS = 4; //row size
const byte COLS = 4; //column size

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2, 1};
Keypad Key = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char customKey;
String Data_pin = "";

void read_card()
{
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++)
    key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  byte buffer1[18];
  block = 1;
  len = sizeof(buffer1);

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK)
  {
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK)
  {
    return;
  }

  Serial.write(buffer1, 16);
  Serial.println("");

  data_rfid = "";
  for (int i = 0; i < 16; i++)
  {
    data_rfid += (char)buffer1[i];
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  blocking = true;
  delay(1000);
}

void setup()
{
  Serial.begin(115200); // Initialize serial communications with the PC
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 card
}
void write_rfid()
{
  // byte buffer[] = "KC01NIEK23456789";
  byte buffer2[16];
  int i = 0;
  while (i < 16)
  {
    while (Serial.available() > 0)
    {
      if (i == 16)
      {
        break;
      }
      char c = Serial.read();
      if (c != '\n')
      {
        buffer2[i] = c;
        i++;
      }
    }
  }
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++)
    key.keyByte[i] = 0xFF;

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  while (!mfrc522.PICC_IsNewCardPresent())
  {
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print(F("Card UID:")); //Dump UID
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println("");

  byte block = 1;
  MFRC522::StatusCode status;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
    Serial.println(F("PCD_Authenticate() success: "));

  // Write block
  status = mfrc522.MIFARE_Write(block, &buffer2[0], 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("MIFARE_Write() failed: block 1 "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
    Serial.println(F("MIFARE_Write() success: block 1 "));

  mfrc522.PICC_HaltA();      // Halt PICC
  mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD
  delay(100);
  Serial.println(F("done"));
}

void read_serial()
{
  data_serial = "";
  // while (!Serial.available() > 0)
  // {
  // }

  while (Serial.available() > 0)
  {
    // data_serial = Serial.readStringUntil('\n');
    char c = Serial.read();
    data_serial += c;
  }
  Serial.flush();
}

void loop()
{
  read_serial();
  if (data_serial == "pin")
  {
    int j = 0;
    while (j < 4)
    {
      customKey = Key.getKey();
      if (customKey)
      {
        Data_pin += customKey;
        j++;
      }
      customKey = 0;
    }
    Serial.println(Data_pin);
    Data_pin = "";
    data_rfid = "";
    data_serial = "";
    delay(1000);
    blocking = false;
  }
  if (data_serial == "write\n")
  {
    write_rfid();
    data_serial = "";
  }
  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      read_card();
    }
  }
}
