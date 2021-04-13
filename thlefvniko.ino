

int ledBoard[5] = {2, 3, 4, 5, 6}; //declare led pins
int lightTimesBoard[5] = {3, 8, 6, 9, 1};//declare how many times each led has to light up
int UpJackBoard[5] = {8, 9, 10, 11, 12};
int DownJackBoard[5] = {A0, A1, A2, A3, A4};
bool CorrectConnection[5] = {0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i = i + 1)
  {
    pinMode(ledBoard[i], OUTPUT); // declare LED pins as output
    pinMode(UpJackBoard[i], OUTPUT);
    pinMode(DownJackBoard[i], INPUT);
  }


}

void loop() {

  for (int i = 0; i < 5; i = i + 1)// blinking. Puzzle reset
  {
    blinkLED(ledBoard[i], 800);
  }

  for (int i = 0; i < 5; i = i + 1) {

    blinkCount(ledBoard[i], lightTimesBoard[i]);
    digitalWrite(UpJackBoard[i], HIGH);

    unsigned long time_start = millis();// start time

    while (millis() - time_start <= 3000) {
      CorrectConnection[i] = digitalRead (DownJackBoard[i]);
    }

    if ( CorrectConnection[i] == 1) {
      //CorrectConnection[i] = 1;
      digitalWrite(ledBoard[i], HIGH);
      delay(3000);
    }
  }
}

void blinkLED(int pin, int duration) // blink the LED on the given pin for the duration in milliseconds
{
  digitalWrite(pin, HIGH); // turn LED on
  delay(duration);
  digitalWrite(pin, LOW); // turn LED off
  delay(duration);
}

void blinkCount(int pin, int times)
{

  for (int i = 1; i <= times; i = i + 1)// blinks each led as manny times as it is declared on the lightTimesBoard
  {
    blinkLED(pin, 800);
    delay(800);
  }

}
