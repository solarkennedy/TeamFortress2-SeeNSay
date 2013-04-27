String randomclass() {
    switch (random(1, 10)) {
    case 1:
      return "DEMOMAN";
      break;
    case 2:
      return "ENGINEER";
      break;
    case 3:
      return "HEAVY";
      break;
    case 4:
      return "MEDIC";
      break;
    case 5:
      return "PYRO";
      break;
    case 6:
      return "SCOUT";
      break;
    case 7:
      return "SNIPER";
      break;
    case 8:
      return "SOLDIER";
      break;
    case 9:
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
