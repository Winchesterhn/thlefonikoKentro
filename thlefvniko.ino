
int ledBoard[5] = {2, 3, 4, 5, 6}; //declare led pins
int lightTimesBoard[5] = {3, 2, 4, 1, 3 };//declare how many times each led has to light up
int UpJackBoard[5] = {8, 9, 10, 11, 12};
int DownJackBoard[5] = {A0, A1, A2, A3, A4};
bool CorrectConnection[5] = {0, 0, 0, 0, 0};
bool puzzleSolved = false;
int nDoor = {13};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i = i + 1)
  {
    pinMode(ledBoard[i], OUTPUT); // declare LED pins as output
    pinMode(UpJackBoard[i], OUTPUT);
    pinMode(DownJackBoard[i], INPUT);
    pinMode(nDoor, OUTPUT);
  }
  // 1 problem. Kai na moy sbhnei amesws otan to jesyndew(na dokimasw for mesa sth for alla poly xronoboro)
  Serial.begin(9600);
}

void loop() {
  while (puzzleSolved = true) {
    for (int i = 0; i < 5; i = i + 1) // blinking. Puzzle reset
    {
      CorrectConnection[i] = testConnection(i);
      if (CorrectConnection[i] == 0) { //this if prevents the for puzzle reset loop from turning off the correctly connected light

        digitalWrite(ledBoard[i], LOW);// if it got disconnected it turns it off
        blinkLED(ledBoard[i], 500);
        delay(1000);
      }
    }

    for (int i = 0; i < 5; i = i + 1) {

      CorrectConnection[i] = testConnection(i);
      if (CorrectConnection[i] == 1) {//checks if connected??useful?

        digitalWrite(ledBoard[i], HIGH);
      }
      else  //checks if disconnected
      {
        blinkCount(ledBoard[i], lightTimesBoard[i]);//puzzle hint

        unsigned long time_start = millis();// start time

        while (millis() - time_start <= 2000) {

          CorrectConnection[i] = testConnection(i);

        }
        if ( CorrectConnection[i] == 1 ) {

          digitalWrite(ledBoard[i], HIGH);
          delay(1000);
        }
        else {
          digitalWrite(ledBoard[i], LOW);

        }

      }
    }
    Door();
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
    CorrectConnection[i] = digitalRead (DownJackBoard[i]);//new check trial
  }

}

bool testConnection(int cable) {// checks if the connection is correct. From where the 1 comes.
  bool cableConnected;
  for (int i = 0; i < 5; i = i + 1) {
    digitalWrite(UpJackBoard[i], LOW);
  }
  digitalWrite(UpJackBoard[cable], HIGH);
  cableConnected = digitalRead (DownJackBoard[cable]);
  digitalWrite(UpJackBoard[cable], LOW);
  return cableConnected;
}

bool Door() {
  for (int i = 0; i < 5; i = i + 1) {
    digitalRead (CorrectConnection[i]);
    if (CorrectConnection[i] == 0) {
      puzzleSolved = true;
      Serial.print("not solved");
    }
    else {
      puzzleSolved = false;
      return puzzleSolved;
      digitalWrite(nDoor, HIGH);
      Serial.print("solved");
    }
  }
}
