/**
 * There are 5 male 3.5mm jacks. They have to be plugged into 5 out of 20 female ones.
 * Each female one has a number above it from 1 to 20.
 * 
 * There are 5 LEDs above each male jack. They flash a specific amount of times and
 * indicate which male plug connects to which female one.
 * 
 * When all the jacks are connected successfully the riddle is solved
 * 
 * ---------------------
 * 
 * To test if a plug is connected correctly, all the others are connected to ground
 * except one which is raised to 5V. If this 5V signal is detected in the correct female
 * plug then it is connected correctly.
 * 
*/

#define num_of_LEDs 5

int ledBoard[5] = {2, 3, 4, 5, 6}; //declare led pins
int lightTimesBoard[5] = {3, 2, 4, 1, 3 };//declare how many times each led has to light up
int hintBlinkDelay = 500;// How much time an LED will stay on or off

int UpJackBoard[5] = {8, 9, 10, 11, 12};// The male plugs
int DownJackBoard[5] = {A0, A1, A2, A3, A4};// The female plugs

bool CorrectConnection[5] = {0, 0, 0, 0, 0};// Note if a plug is connected correctly
bool puzzleSolved = false;
int nDoor = 13;// This pin is raised to 5V when the riddle is solved

void setup() {
  
  for (int i = 0; i < 5; i = i + 1)
  {
    pinMode(ledBoard[i], OUTPUT); // declare LED pins as output
    pinMode(UpJackBoard[i], OUTPUT);// declare male plugs as output
    pinMode(DownJackBoard[i], INPUT);// declare female plugs as input
  }

  pinMode(nDoor, OUTPUT);
  digitalWrite(nDoor, LOW);// pull the "riddle solved" pin to ground
  
  Serial.begin(9600);
}

/* 
 * The info of the LED for which the hint is showning
*/
int times_the_LED_has_blinked = 0;// How many times the LED has already been turned on
bool LED_state = false;// If the LED is off or on (to change its state when the timer runs out)
unsigned long time_start;// How much time has passed since the LED has flipped state

// For which LED to show the hint. Basically, the first wrongly connected cable
int what_hint_to_show = num_of_LEDs + 1;
int previously_shown_LED_hint = what_hint_to_show;

void loop() {
  what_hint_to_show = num_of_LEDs + 1;// Assume at the start that the riddle is solved
  checkConnections();
  
  if (what_hint_to_show == num_of_LEDs + 1) {
    // All plugs are correct, the riddle is solved
    Door();
  }

  /*
   * The riddle is not yet solved, show the appropriate hint.
  */

  // Check if the LED to show the hint has changed
  if (previously_shown_LED_hint != what_hint_to_show) {
    // A different connection than before has been changed and is also incorrect
    // forget about the first incorrect connection and focus on this one.
    
    // Turn off the previous LED
    digitalWrite(what_hint_to_show, LOW);

    // Reset all the flags
    times_the_LED_has_blinked = 0;
    LED_state = false;
    previously_shown_LED_hint = what_hint_to_show;
  }

  if (times_the_LED_has_blinked == lightTimesBoard[what_hint_to_show]) {
    // Has already blinked the correct amount of times
    // Reset the flags
    times_the_LED_has_blinked = 0;
    LED_state = false;
    digitalWrite(what_hint_to_show, LED_state);
  }

  if (times_the_LED_has_blinked == 0) {
    // The LED has not blinked. Start the blinking
    LED_state = true;
    digitalWrite(what_hint_to_show, LED_state);
    times_the_LED_has_blinked++;
    time_start = millis();
  }

  if (millis() - time_start > hintBlinkDelay){
    // It is time to change state
    LED_state = !LED_state;
    digitalWrite(what_hint_to_show, LED_state);
  }

  // A full blink is an < on, -wait-, off, -wait- >
  //                                   ^      ^
  //                                 easy    difficult
  // It is difficult (i.e. not worth it) to know when the second -wait-
  // is happening. The same result can be achieved if the <off> state
  // is used.
  if (LED_state == false) {
    times_the_LED_has_blinked++;
  }

}


/**
 * Updates the CorrectConnection[] table by calling
 * testConnection() for each cable. Also updates the
 * state of the LEDs.
 * 1 0 0 1 0 
*/
void checkConnections() {
  for (int i=0; i<5; i++){
    CorrectConnection[i] = testConnection(i);

    if (CorrectConnection[i]) {
      // Correctly connected, light it up
      digitalWrite(ledBoard[i], HIGH);
    } else {
      // Wrongly connected

      if (what_hint_to_show == i) {
        // The hint for this LED is currently showing.
        // Leave it alone, check the next connection
        continue;
      } else {
        // This is an LED that perhaps was previously connected correctly
        digitalWrite(ledBoard[i], LOW);
      }

      if (what_hint_to_show > i) {
        // Remember the earliest plug that is not connected correctly
        what_hint_to_show = i;
      }
    }
  }
}

/**
 * Checks if the connection is correct. From where the 1 comes.
 * Pulls all wires to GND except the one that is to be tested.
 * Then reads if the signal is detected in the correct plug.
*/
bool testConnection(int cable) {
  bool cableConnected;
  for (int i = 0; i < 5; i = i + 1) {
    digitalWrite(UpJackBoard[i], LOW);
  }
  digitalWrite(UpJackBoard[cable], HIGH);
  cableConnected = digitalRead(DownJackBoard[cable]);
  digitalWrite(UpJackBoard[cable], LOW);
  return cableConnected;
}

/**
 * Opens the door.
 * For now it pulls the appropriate pin to 5V
 * and pauses until full reset.
*/
void Door() {
  digitalWrite(nDoor, HIGH);
  while (true);
}
