#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <string.h>


//#define ARDUINO


#if defined ARDUINO
//voor arduino
#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above
int zaspin = 7;
#else
//voor esp
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
int zaspin = 0;
#endif






MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup()
{
  Serial.begin(115200); // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println(F("Write or read data of a RFID card "));
  pinMode(zaspin, OUTPUT);
}

void loop()
{
  if (digitalRead(zaspin) == HIGH) //writing
  {

    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++)
      key.keyByte[i] = 0xFF;

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent())
    {
      return;
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
    // Serial.print(F(" PICC type: ")); // Dump PICC type
    // MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    // Serial.println(mfrc522.PICC_GetTypeName(piccType));

    byte buffer[32] = "NL99 INGB 0123 4567 89";
    char buf2[32];
    for (int i = 0; i < 32; i++)
    {
      buf2[i] = (char)buffer[i];
    }

    byte block;
    MFRC522::StatusCode status;
    int len = strlen(buf2);
    Serial.println(strlen(buf2));
    for (int i = len; i < 32; i++)
      buffer[i] = ' '; // pad with spaces

    block = 1;
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
    status = mfrc522.MIFARE_Write(block, &buffer[0], 16);
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("MIFARE_Write() failed: block 1 "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else
      Serial.println(F("MIFARE_Write() success: block 1 "));

    block = 2;
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("PCD_Authenticate() failed: block 2 "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    // Write block &buffer[16]
    status = mfrc522.MIFARE_Write(block, &buffer[16], 16);
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("MIFARE_Write() failed: block 2"));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else
      Serial.println(F("MIFARE_Write() success: block 2 "));

    Serial.println(" ");
    mfrc522.PICC_HaltA();      // Halt PICC
    mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD
    delay(100);
    Serial.println(F("done"));
  }
  else //reading
  {
    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++)
      key.keyByte[i] = 0xFF;

    //some variables we need
    byte block;
    byte len;
    MFRC522::StatusCode status;

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }

    if (!mfrc522.PICC_ReadCardSerial())
    {
      return;
    }

    //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

    byte buffer1[18];
    block = 1;
    len = sizeof(buffer1);

    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("Authentication failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    status = mfrc522.MIFARE_Read(block, buffer1, &len);
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("Reading failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    byte buffer2[18];
    block = 2;
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("Authentication failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    status = mfrc522.MIFARE_Read(block, buffer2, &len);
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print(F("Reading failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    Serial.write(buffer1, 16);
    // Serial.println(" ");
    Serial.write(buffer2, 16);
    Serial.print("|");
    Serial.println(" ");

    // char vak[34];
    // for (int i = 0; i < 16; i++)
    // {
    //   vak[i] = buffer1[i];
    // vak[i + 16] = buffer2[i];
    // Serial.write(vak, 32);
    // char output[32];
    // for (int i = 0; i < 16; i++)
    // {
    //   output[i] = (char)buffer1[i];
    //   output[i + 16] = (char)buffer2[i];
    // }
    // for (int i = 0; i < 32; i++)
    // {
    //   Serial.print(output[i]);
    // }
    // Serial.println("|");

    delay(100); //change value if you want to read cards faster

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    Serial.println(F("done"));
  }
}
