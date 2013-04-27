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
  char classfolder[sizeof(tf2class)];
  tf2class.toCharArray(classfolder, sizeof(tf2class));
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
  Serial.print("The number of files here is: ");
  Serial.println(folderSize);
  
  // Even though random will give us a file one less than the number
  // When we "play" will actually play the "next" file
  // So 0 will end up playing file #1
  int filetoplay = random(0, folderSize);
  int counter = 0;
  while ( filetoplay != counter ) 
  {
    root.readDir(dirBuf);
    counter++;
  }
  Serial.print("Going to play file: ");
  printEntryName(dirBuf);
  playone(root);
  Serial.println("");
}

void play_tf2prelude(String tf2class){
  root.open(root, "preludes");
  playcomplete(tf2class + ".wav");
}
