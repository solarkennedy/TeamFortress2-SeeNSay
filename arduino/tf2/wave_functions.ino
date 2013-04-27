/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}


// Plays a full file from beginning to end with no pause.
void playcomplete(String namestring) {
  
  char name[50];
  namestring.toCharArray(name, 50);
  // call our helper to find and play this name
  playfile(name);
  while (wave.isplaying) {
  // do nothing while its playing
  }
  // now its done playing
}

void playfile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!file.open(root, name)) {
    putstring("Couldn't open file "); Serial.println(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(file)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}

void playone(FatReader &dir) {
  FatReader file;
  Serial.println();            // clear out a new line
    
  if (!file.open(vol, dirBuf)) {        // open the file in the directory
    error("file.open failed");          // something went wrong
  }
    
  putstring("Playing ");
  printEntryName(dirBuf);              // print it out
  if (!wave.create(file)) {            // Figure out, is it a WAV proper     
    putstring(" Not a valid WAV");     // ok skip it
  } else {
    Serial.println();                  // Hooray it IS a WAV proper!
    wave.play();                       // make some noise!
        
    uint8_t n = 0;
    while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
      putstring(".");         if (!(++n % 32))Serial.println();
      delay(100);
    }       
    sdErrorCheck();                    // everything OK?
    if (wave.errors)Serial.println(wave.errors);     // wave decoding errors
  }
}

