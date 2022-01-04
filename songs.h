/* 

 * Song definitions - 4 variables per song
 * 1st array defines notes in melody
 * 2nd array defines duration of notes
   * Note durations:
   * 4 = quarter note, 8 = eighth note, etc.
 * Int length of song i.e. number of notes
 * Int tempo multiplier

*/

/* shave and a haircut */
int haircut[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, REST, NOTE_B3, NOTE_C4
};
int haircutDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int haircutLength = 8;
int haircutTempo = 1000;

/* mario theme */
int mario[] = {
  NOTE_E4, NOTE_E4, REST, NOTE_E4, REST, NOTE_C4, NOTE_E4, REST, NOTE_G4, REST, NOTE_G3
};
int marioDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 8
};
int marioLength = 11;
int marioTempo = 1000;

/* mii theme */
int mii[] = {
  NOTE_FS4, REST, NOTE_A4, NOTE_CS5, REST, NOTE_A4, REST, NOTE_FS4,
  NOTE_D4, NOTE_D4, NOTE_D4, REST, NOTE_D5, NOTE_D5, NOTE_D5
};
int miiDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};
int miiLength = 15;
int miiTempo = 1600;

/* harry potter */
int hp[] = {
  NOTE_D4, NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5,
  NOTE_A4, NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_GS4, NOTE_D4
};
int hpDurations[] = {
  4, -4, 8, 4, 2, 4, -2, -2, -4, 8, 4, 2, 4, 1
};
int hpLength = 14;
int hpTempo = 1050;

/* take on me */
int takeonme[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5,
  REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5, 
  REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};
int takeonmeDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};
int takeonmeLength = 32;
int takeonmeTempo = 1200;
