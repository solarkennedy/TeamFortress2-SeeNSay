
String randomclass() {
  return tf2class(random(1,10));
}

String tf2class(int input) {
    // I guess I could use strings throughout,
    // But defines are cool
    switch (input) {
    case DEMOMAN:
      return "DEMOMAN";
      break;
    case ENGINEER:
      return "ENGINEER";
      break;
    case HEAVY:
      return "HEAVY";
      break;
    case MEDIC:
      return "MEDIC";
      break;
    case PYRO:
      return "PYRO";
      break;
    case SCOUT:
      return "SCOUT";
      break;
    case SNIPER:
      return "SNIPER";
      break;
    case SOLDIER:
      return "SOLDIER";
      break;
    case SPY:
      return "SPY";
      break;
    default: 
      return "ERROR: No class?";
  }
}

void play_tf2class(String tf2class) {
  char classfolder[8];
  // Need space to hold 8 characters and a newline?
  tf2class.toCharArray(classfolder, 9);

  root.openRoot(vol);
  if (!root.open(root, classfolder)) {
    Serial.println("Couldn't open dir:" + tf2class);
    delay(3000);
  }
  int folderSize = 0;

  while (root.readDir(dirBuf) > 0)
  {
   folderSize ++;
   //printEntryName(dirBuf);
   //Serial.println();
  }
  root.rewind();

  int filetoplay = random(1, folderSize+1);
  int counter = 0;
  
  // Move the dirBuf to the random location in the directory structure
  while ( filetoplay != counter ) 
  {
    root.readDir(dirBuf);
    counter++;
  }
  
  Serial.print("Going to play file #");
  Serial.print(filetoplay);
  Serial.print("/");
  Serial.print(folderSize);
  Serial.print(" : ");
  printEntryName(dirBuf);
  playone(root);
  Serial.println("");
}

void play_tf2prelude(String tf2class){
  root.open(root, "preludes");
  playcomplete(tf2class + ".wav");
}


int class_decode(int resistor) {
  // Maps resistor values to what class physically on the face of the seeNsay
  switch (resistor) {
    case 220:
      return ENGINEER;
    case 330:
      return HEAVY;
    case 470:
      return SCOUT;
    case 680:
      return SPY;
    case 1000:
      return PYRO;
    case 2200:
      return SOLDIER;
    case 3300:
      return MEDIC;
    case 4700:
      return SNIPER;
    case 10000:
      return DEMOMAN;
    default:
      // This should never happen
      Serial.println("class_decode couldn't find the class?");
      return 0;
  }
}

