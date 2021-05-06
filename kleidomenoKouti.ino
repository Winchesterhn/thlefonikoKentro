#include <Servo.h>
int servoPin = 12;
Servo boxLock;
int nDoor = 13;// this pin is set to 5V when the riddle is solved

int buttonsAndCode[4] = {A0, A1, A2, A5};
int buttonState[4] = {0, 0, 0, 0};

void setup() {
  boxLock.attach(servoPin);

  for (int i = 0; i < 4; i++) {
    pinMode(buttonsAndCode[i], INPUT);
  }
  pinMode(nDoor, OUTPUT);
  digitalWrite(nDoor, LOW);// pull the "riddle solved" pin to ground
  Serial.begin(9600);
}

void loop() {
  int pressed;
  int i = 0;
  while (i < 4) {
    for (int j = 0; j < 4; j++) {
      buttonState[j] = analogRead(buttonsAndCode[j]);
      while (analogRead(buttonsAndCode[j]) >= 1000) {
        delay(100);
      }
    }
    pressed = -1;
    for (int j = 0; j < 4; j++) {
      if (buttonState[j] >= 1000) {
        pressed = j;
        break;
      }
    }
    if (pressed >= 0) {
      if ( pressed == i ) {
        i = i + 1;
        Serial.print("correct: ");
        Serial.println(pressed);
      }
      else {
        Serial.println("wrong! resets");
        i = 0;
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    Serial.print(buttonState[i]);
    Serial.print("\n");
  }
  Door();
}


//void untilCorrectPressed(int i) {
//
//  while (buttonState[i] < 800) {
//
//    buttonState[i] = analogRead(buttonsAndCode[i]);
//    Serial.print(buttonState[i]);//shows the value of its button. Helps in debugging
//    Serial.print(",");
//    //    Serial.print("\n");
//    delay(2000);
//    if (buttonState[i] >= 800) {
//      Serial.println("pressed correctly");
//    }
//  }
//}

void Door() {
  digitalWrite(nDoor, HIGH);//Opens the box and waits until reset.
  boxLock.write(180);// Make servo go to 90 degrees, unlocks the box.
  Serial.print("the box unlocks\n");
  while (true);
}

//int pressed;
//int i = 0;
//while (i < 4) {
//  for (int j = 0; j < 4; j++) {
//    buttonState[j] = analogRead(buttonsAndCode[j]);
//    while (analogRead(buttonsAndCode[j]) >= 1000) {
//      delay(100);
//    }
//  }
//  pressed = -1;
//  for (int j = 0; j < 4; j++) {
//    if (buttonState[j] >= 1000) {
//      pressed = j;
//      break;
//    }
//  }
//  if (pressed >= 0) {
//    if ( pressed == i ) {
//      i = i + 1;
//    }
//    else {
//      Serial.print("wrong! resets\n");
//      i = 0;
//    }
//  }
//}
