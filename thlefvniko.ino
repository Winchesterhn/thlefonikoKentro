
int ledBoard[5] = {2, 3, 4, 5, 6}; //declare led pins
int lightTimesBoard[5] = {5, 1, 4, 2, 3 };//declare how many times each led has to light up. This is basicly the riddle's hint.
int UpJackBoard[5] = {8, 9, 10, 11, 12};//declare the pins connected to the upper jacks (male jacks)
int DownJackBoard[5] = {A0, A1, A2, A3, A4};//declare the pins connected to the lower jacks (female jacks)
bool CorrectConnection[5] = {0, 0, 0, 0, 0};//This board has flags. Zeros or ones, based on whether its connection is correct or not
bool puzzleSolved = false;//flag
int nDoor = 13;//this pin will be set HIGH when the riddle is solved

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i = i + 1)
  {
    pinMode(ledBoard[i], OUTPUT); // declare LED pins as output
    pinMode(UpJackBoard[i], OUTPUT);// declare male jack pins as output
    pinMode(DownJackBoard[i], INPUT);// declare the female jack pins as output
  }
  pinMode(nDoor, OUTPUT);
  digitalWrite(nDoor, LOW);//set the "riddle solved" pin to 0
  Serial.begin(9600);// start the serial communication. Help us debug.
}

void loop() {
  // There is a problem yet to be solved. It needs to be more interactive. React immediately to the connection changes, not wait until it is checked again.

  while (puzzleSolved == false) {
    // blinking. This is basically the Puzzle reset. After this, the hints will start showing.
    for (int i = 0; i < 5; i = i + 1)
    {
      CorrectConnection[i] = testConnection(i);
      if (CorrectConnection[i] == 0) { //this "if check", prevents the puzzle reset loop from turning off the led of the correctly connected jacks.

        digitalWrite(ledBoard[i], LOW);// if the jack got disconnected, it turns off its led
        blinkLED(ledBoard[i], 500);
        delay(1000);
      }
    }

    for (int i = 0; i < 5; i = i + 1) {

      CorrectConnection[i] = testConnection(i);// runs the "test connection" function
      if (CorrectConnection[i] == 1) {// if it returns true then light up its led.

        digitalWrite(ledBoard[i], HIGH);
      }
      else  //*if it is not correctly connected or it got disconnected...
      {
        blinkCount(ledBoard[i], lightTimesBoard[i]);//show puzzle hint for this one...

        unsigned long time_start = millis();// start time
        // Give 2 seconds to the players to connect it correctly...
        while (millis() - time_start <= 2000) {

          CorrectConnection[i] = testConnection(i);

        }
        if ( CorrectConnection[i] == 1 ) {// if they did connect it, light up its led.*

          digitalWrite(ledBoard[i], HIGH);
          delay(1000);
        }
        else {
          digitalWrite(ledBoard[i], LOW);

        }

      }

    }
    puzzleSolved = openDoor();// call openDoor funtion and set the variable puzzleSolved as needed.
  }
  // Calls the "Door" function only if the riddle is solved.
  if (puzzleSolved == true) {
    Door();
  }
}

// blinks the LED on the given pin for the duration in milliseconds
void blinkLED(int pin, int duration)
{
  digitalWrite(pin, HIGH); // turn LED on
  delay(duration);
  digitalWrite(pin, LOW); // turn LED off
  delay(duration);
}

// blinks each led as many times, as it is declared on the lightTimesBoard. Basically shows the hint for this specific pin
void blinkCount(int pin, int times)
{
  for (int i = 1; i <= times; i = i + 1)// Calls the "blinkLed" function, as many times as this hint needs.
  {
    blinkLED(pin, 500);
    delay(500);
    CorrectConnection[i] = digitalRead (DownJackBoard[i]);// checks connection and changes its the flag as needed
  }
}

// checks if the connection is correct. Not only if it is connected, but also if it is correctly connected.
bool testConnection(int cable) {
  bool cableConnected;
  for (int i = 0; i < 5; i = i + 1) {
    digitalWrite(UpJackBoard[i], LOW);// pull all male jacks to ground. No power.
  }
  digitalWrite(UpJackBoard[cable], HIGH);//Give 5V to this specific male jack.
  cableConnected = digitalRead (DownJackBoard[cable]);//check if this specific female one takes 5V, if it is connected. And update the cableConnected variable.
  digitalWrite(UpJackBoard[cable], LOW);//Then pull this male jack to ground again. 
  return cableConnected;// return if this is correctly connected or not.
}

//This function checks if all 5 cables are correctly connected and changes the variable "puzzleSolved" accordingly.
bool openDoor() {
  for (int i = 0; i < 5; i = i + 1) {
    digitalRead (CorrectConnection[i]);
  }
  if ((CorrectConnection[0] && CorrectConnection[1] && CorrectConnection[2] && CorrectConnection[3] && CorrectConnection[4]) == 1) {
    puzzleSolved = true;
    Serial.print("SOLVED");
  }
  else {
    puzzleSolved = false;
    Serial.print("notSolved");
  }
  return puzzleSolved;//Returns if the puzzle is solved or not.
}

//This function opens the door to the waits until reset.
bool Door() {
  digitalWrite(nDoor, HIGH);
  while (true);
}
