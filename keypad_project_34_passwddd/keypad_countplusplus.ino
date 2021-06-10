#include <Keypad.h> //keypad library



using namespace std;

//Lenght of password +1 for null character
#define Password_Length 5
//Character to hold password input
char Data[Password_Length];
//Password
char Master[Password_Length] = {'1', '2', '3', '4'};

int count = 0;

const byte ROWS = 4; //row size
const byte COLS = 4; //column size

char hexaKeys [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins [ROWS] = {9, 8, 7, 6};
byte colPins [COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char customKey;

int position = 0;

int wrong = 0; //Variable to calculate the wrong inputs.



void setup() {
  Serial.begin(9600);



}

void loop() {
  char customKey = customKeypad.getKey ();



  if (customKey != NO_KEY) {
    Serial.println (customKey);
    if (customKey == 'A')
    {
      if (count < 3) {
        Serial.println ("Enter Password");
        int j = 0;
        while (j < 4)
        {
          char customKey = customKeypad.getKey ();
          if (customKey)
          {
            Serial.println (customKey);
            Data[j++] = customKey;
          }
          customKey = 0;
        }
      } else  {
        Serial.println("blocked");
      }
      
    }

    if (customKey == 'D')
    {

      if (!(strncmp(Master, Data, 5)))
      {
        Serial.println("Access Granted");

        if ("Acces Granted"){
        count = 0;
      }
      }
      else
      {
        count++;
        Serial.print (count);
        Serial.println("Access Denied");
      }
      
    }
  }
}
