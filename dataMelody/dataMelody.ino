//Plays a melody based on collected data
//circuit: 8-ohm speaker on digital pin 3 

// paste data in { }brackets:
int melody[] = {
  1000};

void setup() {
}

void loop() {
                                // iterate over the notes of the melody:
  for (int note = 0; note < sizeof(melody); note++) {
    tone(3, melody[note]/30,melody[note]/30);
    delay(100);
    //delay(melody[note]/100);  //optional adjustment to delay
    noTone(3);
  }
  delay(1000);                //one second before song repeats
}
