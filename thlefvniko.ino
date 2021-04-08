

int ledBoard[5] = {12, 10, 8, 6, 2};
int lightTimesBoard[5] = {3, 9, 6, 11, 1};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i = i + 1)
  {
    pinMode(ledBoard[i], OUTPUT); // declare LED pins as output
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // flash each of the LEDs for 1000 milliseconds (1 second)

  for (int i = 0; i < 5; i = i + 1)
  {
    blinkLED(ledBoard[i], 800);
  }

  for (int i = 0; i < 5; i = i + 1)
  {
    blinkCount(ledBoard[i], lightTimesBoard[i]);
  }


}

// blink the LED on the given pin for the duration in milliseconds

void blinkLED(int pin, int duration)
{
  digitalWrite(pin, HIGH); // turn LED on
  delay(duration);
  digitalWrite(pin, LOW); // turn LED off
  delay(duration);
}

void blinkCount(int pin, int times)
{

  for (int i = 1; i <= times; i = i + 1)
  {
    blinkLED(pin, 800);
    delay(800);

  }

}
