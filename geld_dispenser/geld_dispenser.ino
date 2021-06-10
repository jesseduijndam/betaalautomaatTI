#include <AccelStepper.h>

const long stepsPerRevolution = 4096;
#define relay_pin 2

// initialize steppermotors
AccelStepper stepper1 = AccelStepper(8, 8, 10, 9, 11);
AccelStepper stepper2 = AccelStepper(8, 4, 6, 5, 7);

// function to turn the stepper motors n amount of time
void push(AccelStepper &step, long aantal)
{
  digitalWrite(relay_pin, HIGH);

  long steps = (stepsPerRevolution * aantal);

  step.move(steps);
}

void setup()
{

  pinMode(relay_pin, OUTPUT);
  stepper1.setMaxSpeed(1200.0);
  stepper1.setAcceleration(1500.0);
  stepper2.setMaxSpeed(1200.0);
  stepper2.setAcceleration(1500.0);

  Serial.begin(115200);

  Serial.println("start");
}

//read messages received via serial. function is blocking until data is received
String read_serial()
{
  Serial.flush();
  String data_serial = "";
  while (!Serial.available())
  {
  }
  while (Serial.available())
  {
    data_serial = Serial.readStringUntil('\n');
  }
  Serial.flush();
  return data_serial;
}

void loop()
{

  String serial_receive = read_serial();    //read serial input
  if (serial_receive == "geld")             //if received command is "geld" begin the money dispense function
  {
    Serial.println("send aantal 50");

    int aantal_50 = read_serial().toInt();  //receive turn amount for $50 bill

    Serial.println("send aantal 10");
    int aantal_10 = read_serial().toInt();  //receive turn amount for $10 bill

    if (aantal_50 > 0)
    {
      push(stepper1, aantal_50);            //turn stepper motor1
    }
    if (aantal_10 > 0)
    {
      push(stepper2, -aantal_10);            //turn stepper motor2
    }

    while (stepper1.isRunning() || stepper2.isRunning())    //while a stepper motor needs to turn
    {
      stepper1.run();                                       // do 1 step if step is needed
      stepper2.run();                                       // do 1 step if step is needed
    }
    if (aantal_50 > 0 || aantal_10 > 0)
    {
      delay(2000);
      digitalWrite(relay_pin, LOW);                         //turnoff relay for motors
    }
  }
}
