/*
 *  Utilities
 */

 void cls()
 {
  lcd.clear();
  lcd.setCursor(0, 0);
}

void checkArrows(byte i,byte max)
{

  if(i == 0){
    lcd.setCursor(15, 1);
    lcd.write(6); 
  }
  
  if(i == max){  
    lcd.setCursor(15 ,0);
    lcd.write(5);
  }
  
  if(i > 0 && i< max){
    lcd.setCursor(15, 1);
    lcd.write(6);
    lcd.setCursor(15, 0);
    lcd.write(5);  
  }
}

void beep(int note, int duration)
{
  if(soundEnable)
  {
    tone(tonepin, note, duration);
    delay(50);
  }
}

void tickSound()
{
  if(soundEnable)
  {
    tone(tonepin, TickSound, 20);
  } 
}

void tockSound()
{
  if(soundEnable)
  {
    tone(tonepin, TockSound, 20);
  } 
}

