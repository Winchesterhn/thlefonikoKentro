

int ledBoard[5] = {2, 3, 4, 5, 6}; //declare led pins
int lightTimesBoard[5] = {3, 2, 4, 3, 1};//declare how many times each led has to light up
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
  // 2 problems. na mou elegxei kai apo pou erxete reyma oxi mono an pernaei. Kai na moy sbhnei amesws otan to jesyndew(na dokimasw for mesa sth for alla poly xronoboro)

}

void loop() {

  for (int i = 0; i < 5; i = i + 1) // blinking. Puzzle reset
  {
    if (CorrectConnection[i] == 0) { //this if prevents the for puzzle reset loop from turning off the correctly connected light

      digitalWrite(ledBoard[i], LOW);// if it got disconnected it turns it off
      blinkLED(ledBoard[i], 500);

    }
  }

  for (int i = 0; i < 5; i = i + 1) {


    if (CorrectConnection[i] == 1) {//checks if connected??useful?
      digitalWrite(ledBoard[i], HIGH);
    }
    else //(CorrectConnection[i] == 0) {  //checks if disconnected
    {
      digitalWrite(ledBoard[i], LOW);//turns off disconnected
      blinkCount(ledBoard[i], lightTimesBoard[i]);

    }
    digitalWrite(UpJackBoard[i], HIGH);

    unsigned long time_start = millis();// start time

    while (millis() - time_start <= 2000) {
      CorrectConnection[i] = digitalRead (DownJackBoard[i]);
    }

    if ( CorrectConnection[i] == 1) {
      digitalWrite(ledBoard[i], HIGH);
      delay(2000);
    }
    else {
      digitalWrite(ledBoard[i], LOW);
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
    blinkLED(pin, 500);
    delay(500);
  }

}
