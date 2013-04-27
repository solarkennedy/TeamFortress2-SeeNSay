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

