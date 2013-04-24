#include <WaveHC.h>
#include <WaveUtil.h>
#include <FatReader.h>

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // Holds the file to play
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

uint8_t dirLevel; // indent level for file/dir names    (for prettyprinting)
dir_t dirBuf;     // buffer for directory reads

// Define macro to put error messages in flash memory
#define error(msg) error_P(PSTR(msg))

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging  
  putstring_nl("\nWave test!");  // say we woke up!
  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(FreeRam());

  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    error("Card init. failed!");  // Something went wrong, lets print out why
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
  
  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {   // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                           // we found one, lets bail
  }
  if (part == 5) {                     // if we ended up not finding one  :(
    error("No valid FAT partition!");  // Something went wrong, lets print out why
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    error("Can't open root dir!");      // Something went wrong,
  }
  
}

// Function definitions (we define them here, but the code is below)
void play(FatReader &dir);


void loop() {
  root.rewind();
  
  //Figure out what class we should play
  String theclass = randomclass();
  Serial.print("Our Random class is:");
  Serial.println(theclass);
  
  //Play class specific prelude
  String preludefile = "PRELUDES/" + theclass + ".WAV";
  char charfile[50];
  preludefile.toCharArray(charfile, 50);
  playfile(charfile);
    
  // Play random class sound
  //play(root);
  
  delay(5000);
  
}

