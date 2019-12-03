#include "megalovania.h"

// notes in the melody:
/*int melody[] = {
  NOTE_G7, NOTE_FS7, NOTE_DS7, NOTE_A6, NOTE_GS6, NOTE_E7, NOTE_GS7, NOTE_C7
};*/

int melody[] = {
  NOTE_D6, NOTE_D6, NOTE_D5, NOTE_A6,0, NOTE_GS6, NOTE_G6, NOTE_F6,0, NOTE_D6, NOTE_F6, NOTE_G6,0,
  NOTE_C6, NOTE_C6, NOTE_D5, NOTE_A6,0, NOTE_GS6, NOTE_G6, NOTE_F6,0, NOTE_D6, NOTE_F6, NOTE_G6,0,
  NOTE_B7, NOTE_B7, NOTE_D5, NOTE_A6,0, NOTE_GS6, NOTE_G6, NOTE_F6,0, NOTE_D6, NOTE_F6, NOTE_G6,0,
  NOTE_AS7, NOTE_AS7, NOTE_D5,NOTE_A6,0, NOTE_GS6, NOTE_G6, NOTE_F6,0, NOTE_D6, NOTE_F6, NOTE_G6,0
};

int noteDurations[] = {
  8,8,4,4,8,4,4,8,8,8,8,4,8,
  8,8,4,4,8,4,4,8,8,8,8,4,8,
  8,8,4,4,8,4,4,8,8,8,8,4,8,
  8,8,4,4,8,4,4,8,8,8,8,4,8
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
/*int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8
};
*/

void megalovania(int pin) {

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 52; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(pin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(22);
  }
}