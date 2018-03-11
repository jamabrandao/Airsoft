/*
 * Game menus
 */

void mainMenu() {
  
  keypad.setHoldTime(50);
  keypad.setDebounceTime(50);  
  
  // Menu position
  int menuPos = 0;
  
  // If whe start a new game from another we need to restart propertly this variables
  sdStatus = false;
  saStatus = false;
  doStatus = false;
  baStatus = false;
  stStatus = false;
  
  printMenuOption(menuPos);
  
  while(1)
  {
    char key = keypad.waitForKey();
  
    if(key == btPrev && menuPos > 0)
    {
        beep(NOTE_DS7, 30);
        menuPos--;
        printMenuOption(menuPos);
        delay(50);
    }
  
    if(key == btNext && menuPos < 4)
    {
        beep(NOTE_DS7, 30);
        menuPos++;
        printMenuOption(menuPos);
        delay(50);
    }
  
    if(key == btEnter)
    {
      beep(NOTE_DS7, 30);
      cls();
      switch (menuPos)
      {
        case 0:  // Search and Destroy Game        
          sdStatus = true;
          configQuickGame();
          //startGameCount();
          //startSearchDestroy();
          break;
         case 1: 
          saStatus = true;
          //configQuickGame();
          //startGameCount();
          //startSabotage();
          break;          
        case 2:
          doStatus = true;
          //configQuickGame();
          //startGameCount();
          //domination();
          break;
        case 3:
          stStatus = true;    
          //startConfig();
          break;
        case 4:            
          baStatus = true;
          //startBattery();
          break;
      }
    }
  }
}

void printMenuOption(int pos) {
  // Clear lcd and set cursor to 0,0
  cls();
  lcd.print(GAME_TYPE);  
  lcd.setCursor(0, 1);
  lcd.print(menu1[pos]);
  checkArrows(pos, 4);
}

void configQuickGame()
{
  cls();
  
  // GAME TIME
  if(sdStatus || doStatus || saStatus)
  {
    menu1:
    cls();
    lcd.print(GAME_TIME);
    delay(100);
    
    lcd.setCursor(0, 1);
    lcd.print(ZERO_HOURS);
    lcd.cursor();
    lcd.blink();
    lcd.setCursor(0, 1);
    
    byte var2 = 0;
    for(int i = 0;i < 4;i++)
    { 
      while(1)
      {
        if(i == 2 && var2 == 0)
        {
          lcd.print(":");
          var2 = 1;
        }
    
        byte varu= getRealNumber();
        if(varu != 11)
        {
          time[i] =  varu;
          lcd.print(varu);
          beep(NOTE_DS7, 30);
          break;
        }
      }  
    }
    
    lcd.noCursor();
    lcd.noBlink();
    lcd.setCursor(13, 1);
    lcd.print(OK);
    // Save the select items
    while(1)
    {
      char key = keypad.waitForKey();
      
      if(key == btEnter) // select button
      {
        beep(NOTE_DS7, 30);
        GAMEMINUTES = ((time[0] * 600) + (time[1] * 60) + (time[2] * 10) + (time[3]));
        break;
      }
          
      if(key == btCancel) // Cancel or Back Button
      {
        beep(NOTE_DS7, 30);
        goto menu1;
      }           
    }
    beep(NOTE_DS7, 30);
    cls();    
  }

  // BOMB TIME
  if(sdStatus || saStatus)
  {
    menu2:
    cls();
    lcd.print(BOMB_TIME);
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print(ZERO_MINUTES);
    lcd.cursor();
    lcd.blink();
    lcd.setCursor(0,1);
    for(int i = 0;i < 2;i++)
    { 
      while(1)
      {
        byte varu= getRealNumber();
        if(varu != 11)
        {
          time[i] =  varu;
          lcd.print(varu);
          beep(NOTE_DS7, 30);
          break;
        }
      }  
    }
    lcd.noCursor();
    lcd.noBlink();   
    lcd.setCursor(13,1);
    lcd.print(OK);
    // Save the select items
    while(1)
    {
      char key = keypad.waitForKey();
      if(key == btEnter) // select button
      {
        beep(NOTE_DS7, 30);
        BOMBMINUTES = ((time[0] * 10 )+ (time[1]));
        break;
      }
          
      if(key == btCancel) // Cancel or Back Button
      {
        beep(NOTE_DS7, 30);
        goto menu2;
      }           
    }
    beep(NOTE_DS7, 30);
    cls();
  }
  cls();
  
  
}

