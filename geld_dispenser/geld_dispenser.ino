#include <Arduino.h>
#include <string.h>
#include <AccelStepper.h>

const long stepsPerRevolution = 4096;
#define relay_pin 2

AccelStepper stepper1 = AccelStepper(8, 8, 10, 9, 11);
AccelStepper stepper2 = AccelStepper(8, 4, 6, 5, 7);

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

  String serial_receive = read_serial();
  if (serial_receive == "geld")
  {
    Serial.println("send aantal 50");

    int aantal_50 = read_serial().toInt();

    Serial.println("send aantal 10");
    int aantal_10 = read_serial().toInt();

    if (aantal_50 > 0)
    {
      push(stepper1, aantal_50);
    }
    if (aantal_10 > 0)
    {
      push(stepper2, aantal_10);
    }

    while (stepper1.isRunning() || stepper2.isRunning())
    {
      stepper1.run();
      stepper2.run();
    }
    if (aantal_50 > 0 || aantal_10 > 0)
    {
      delay(2000);
      digitalWrite(relay_pin, LOW);
    }
  }
}