#include <WaveHC.h>
#include <WaveUtil.h>
#include <FatReader.h>

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // Holds the file to play
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time
dir_t dirBuf;     // buffer for directory reads

int spinner_pin = 5;

#define DEMOMAN 1
#define ENGINEER 2
#define HEAVY 3
#define MEDIC 4
#define PYRO 5
#define SCOUT 6
#define SNIPER 7
#define SOLDIER 8
#define SPY 9

// Define macro to put error messages in flash memory
#define error(msg) error_P(PSTR(msg))

// Function definitions (we define them here, but the code is below)
void play(FatReader &dir);


void setup() {
  randomSeed(analogRead(1));
  Serial.begin(115200);           // set up Serial library at 9600 bps for debugging  
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


void loop() {
  root.openRoot(vol);
  
  //Figure out what class we should play
//  String theclass = randomclass();
  String theclass = spinner_detect();
  Serial.print("Our Random class is: ");
  Serial.println(theclass);
  
  //Play class specific prelude
  play_tf2prelude(theclass);
  
  // Play random class sound
  play_tf2class(theclass);

  delay(500);
}

