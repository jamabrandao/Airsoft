/*
 * Keyboard methods
 */

byte getRealNumber()
{
  while(1)
  {
    char key = keypad.waitForKey();

    if (key)
    {
      switch (key) 
      {
        case '1': 
          return 1;
          break;
        case '2': 
          return 2;
          break;
        case '3': 
          return 3;
          break;
        case '4': 
          return 4;
          break;
        case '5': 
          return 5;
          break;
        case '6': 
          return 6;
        case '7': 
          return 7;
          break;
        case '8': 
          return 8;
          break;
        case '9': 
          return 9;
          break;
          case '0': 
          return 0;
          break;        
        default:
          return 11;
          break;
      }
    }    
    return 11;
  }
}
