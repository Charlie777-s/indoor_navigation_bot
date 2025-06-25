#include <LedControl.h>
#include <MD_Parola.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <IRremote.h>
#include <SD.h>
const int sw= 8;
const int l_step= 11;
const int l_dir= 13;
const int r_step= 6;
const int r_dir= 7;
const int hor= 1;
const int vert= 0;
const int gas= 2;
const int ir= 10;
const int RECV_PIN = 10;
const int cs= 53;
const int sd_di= 51;
const int sd_do= 50;
const int sck= 52;
const int g_pin=18;
int g= 0;
int cnt_cp=0;
int cnt_o=0;
int cnt_c= 0;
int i=0;
int j=0;
int h=0;
int v=0;
int x=0;
int x1=0;
int y=0;
int m=0;
int xo=0;
int yo=0;
int temp=0;
int n_o= 0;
int n_c= 0;
int l=0;
LedControl lc = LedControl(2, 4, 3, 4);
LiquidCrystal_I2C lcd(0x27,  16, 2);
File f;
File f1;
//IRrecv receiver(PIN_RECEIVER);
struct point
{
  int x;
  int y;
}cp[5], o[20], c[8], cp_s[5], o_s[20], c_s[8], path[256];
void checkpoint()
{
 /* lc.setLed(0, 7, 7, true);
  lc.setLed(1, 0, 7, true); 
  lc.setLed(2, 7, 7, true);
  lc.setLed(3, 0, 7, true);*/
  cp[0].x= 0; cp[0].y= 0;
  cp[1].x= 7; cp[1].y= 7;
  cp[2].x= 15; cp[2].y= 0;
  cp[3].x= 23; cp[3].y= 7;
  cp[4].x= 31; cp[4].y= 0;
}
void obstacle()
{
  /*lc.setLed(0, 3, 0, true);
  lc.setLed(0, 1, 6, true);
  lc.setLed(1, 6, 2, true);
  lc.setLed(1, 1, 3, true);
  lc.setLed(1, 3, 7, true);
  lc.setLed(1, 6, 7, true);
  lc.setLed(2, 4, 5, true);
  lc.setLed(2, 1, 7, true);
  lc.setLed(3, 2, 2, true);
  lc.setLed(3, 6, 4, true);*/

  o[0].x= 0; o[0].y= 3;
  o[1].x= 6; o[1].y= 1;
  o[2].x= 10; o[2].y= 6;
  o[3].x= 11; o[3].y= 1;
  o[4].x= 15; o[4].y= 3;
  o[5].x= 15; o[5].y= 6;
  o[6].x= 21; o[6].y= 4;
  o[7].x= 23; o[7].y= 1;
  o[8].x= 26; o[8].y= 2;
  o[9].x= 28; o[9].y= 6;
}

void component()
{
 /* lc.setLed(0, 2, 2, true);
  lc.setLed(0, 5, 5, true);
  lc.setLed(1, 4, 5, true);
  lc.setLed(2, 1, 2, true);
  lc.setLed(2, 4, 6, true);
  lc.setLed(3, 5, 1, true);
  lc.setLed(3, 2, 5, true);
  lc.setLed(3, 5, 6, true);*/
  c[0].x= 2; c[0].y= 2;
  c[1].x= 5; c[1].y= 5;
  c[2].x= 13; c[2].y= 4;
  c[3].x= 18; c[3].y= 1;
  c[4].x= 22; c[4].y= 4;
  c[5].x= 25; c[5].y= 5;
  c[6].x= 29; c[6].y= 2;
  c[7].x= 30; c[7].y= 5;

}
void move(int p_step, int p_dir, bool val, int step, int time)
{
  digitalWrite(p_dir, val);
  for  (i=0; i<step; i++)
  {
    digitalWrite(p_step, HIGH);
    delayMicroseconds(time);
    digitalWrite(p_step, LOW);
    delayMicroseconds(time);
  }
}
int gas_s(int cx, int cy, int cnt)
{
  o_s[cnt].x=cx;
      o_s[cnt].y= cy;
      cnt++;
  f.print("obstacle: ");
      f.print(cx);
      f.print(" ");
      f.println(cy);
      f.println(analogRead(gas));
}
void check_cp(int cx, int cy, int n_c, int n_o)
{

  for(i=0; i<5; i++)
  {
    if (cp[i].x==cx && cp[i].y==cy)
    {
      lcd.setCursor(0,0);
      lcd.print("checkpoint");
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("components:");
      lcd.setCursor(0,1);
      lcd.print(n_c);
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("obstacle:");
      lcd.setCursor(0,1);
      lcd.print(n_o);
      delay(500);
      cp_s[cnt_cp].x=cx;
      cp_s[cnt_cp].y= cy;
       f.print("checkpoint: ");
      f.print(cx);
      f.print(" ");
      f.println(cy);
      f.println(analogRead(gas));
      cnt_cp++;
      break;
    }
  }
  //delay(500);
}
int check_o(int cx, int cy, int xo, int yo)
{

  for(i=0; i<10; i++)
  {
    if (o[i].x==cx && o[i].y==cy)
    {
      lcd.setCursor(0,0);
      lcd.print("obstacle");
      f.print("obstacle: ");
      f.print(cx);
      f.print(" ");
      f.println(cy);
      f.println(analogRead(gas));
      o_s[cnt_o].x=cx;
      o_s[cnt_o].y= cy;
      cnt_o++;
      blink(y, x);
      blink(y, x);
      y= yo;
      x= xo;

      break;
    }
  }
  //delay(500);
  return cnt_o;
}
int check_c(int cx, int cy, int xo, int yo)
{

  for(i=0; i<8; i++)
  {
    if (c[i].x==cx && c[i].y==cy)
    {
      lcd.setCursor(0,0);
      lcd.print("component");
      f.print("component: ");
      f.print(cx);
      f.print(" ");
      f.println(cy);
      f.println(analogRead(gas));
      c_s[cnt_c].x=cx;
      c_s[cnt_c].y= cy;
      cnt_c++;
      blink(y, x);
      //y= yo;
      //x= xo;
      break;
    }
  }
  //delay(500);
  return cnt_c;
}

void blink(int y, int x)
{
  temp= x/8;
  x%=8;
  lc.setLed(temp, y, x, true);  // Turn ON
  delay(500);
  lc.setLed(temp, y, x, false); // Turn OFF
  delay(500);
}
void press_1(int l)
{
  for(i=l-1; i>=0; i--)
  {
    x= path[i].x;
    y= path[i].y;
    temp= x/8;
    x%=8;
    delay(100);
    lc.setLed(temp, y, x, false);
  }

}

int press_0(int l)
{
  for(i=l-1; i>=0; i--)
  {
   
    x= path[i].x;
    y= path[i].y;
    for(j=0; j<5; j++)
    {
      if (cp[j].x== x && cp[j].y==y)
      {
      l=i;
      return j;
      }
      
    }
    temp= x/8;
    x%=8;
    delay(100);
    lc.setLed(temp, y, x, false);
  }

}
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  pinMode(l_step, OUTPUT);
  pinMode(r_step, OUTPUT);
  pinMode(l_dir, OUTPUT);
  pinMode(r_dir, OUTPUT);
  pinMode(hor, INPUT);
  pinMode(vert, INPUT);
  pinMode(gas, OUTPUT);
  digitalWrite(cs, HIGH);
  pinMode(g_pin, INPUT_PULLUP);
  IrReceiver.begin(RECV_PIN, true);
 // attachInterrupt(digitalPinToInterrupt(g_pin), gas_s(x, y, cnt_o), LOW);
  for(i=0; i<4; i++)
  {
    lc.shutdown(i, false);
  lc.setIntensity(i, 8);   
  lc.clearDisplay(i);
  }
  checkpoint();
  obstacle();
  component();
  Serial.begin(9600);
  SD.begin(53);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  f= SD.open("data.txt", FILE_WRITE);
  f1= SD.open("data.txt", FILE_READ);
  h= analogRead(hor);
  v= analogRead(vert);
  if (v > 900 && h > 400 && h < 600)
  {
    move(l_step, l_dir, HIGH, 200, 500);
    move(r_step, r_dir, HIGH, 200, 500);
    y--;
  }
  else if (h < 100 && v > 400 && v < 600)
  {
    move(l_step, l_dir, HIGH, 200, 500);
    move(r_step, r_dir, LOW, 200, 500);
    x--;
  }
  else if(v < 100 && h > 400 && h < 600)
  {
    move(l_step, l_dir, LOW, 200, 500);
    move(r_step, r_dir, LOW, 200, 500);
    y++;
  }
  else if(h > 900 && v > 400 && v < 600)
  {
    move(l_step, l_dir, LOW, 200, 500);
    move(r_step, r_dir, HIGH, 200, 500);
    x++;
  }
  if(x>31)
  x=32;
  else if (x<0)
  x=0;
  if(y>7)
  y=7;
  else if(y<0)
  y=0;
  path[l].x= x;
  path[l].y= y;
  
  if(!((xo==x)&&(yo==y)))
  {
    
    check_cp(x, y, n_c, n_o);
    
    n_c= check_c(x, y, xo, yo);
    /*Serial.println("after component");
    Serial.print(x);
  Serial.print(" ");
  Serial.println(y);*/
    n_o= check_o(x, y, xo, yo);
    /*Serial.println("after obstacle");
    Serial.print(x);
  Serial.print(" ");
  Serial.println(y);*/
    lcd.clear();
    xo=x;
    yo=y;
    l++;
    //Serial.println(l);
  }
  
  m= x/8;
  x1= x%8;
  lc.setLed(m, y, x1, true); 
  
   if (IrReceiver.decode()) {
    if(IrReceiver.decodedIRData.command==48)
    {
      press_1(l);
      x=0;
      xo=0;
      y=0;
      yo=0;
      l=0;
    }
    
    else if (IrReceiver.decodedIRData.command==104)
    {
      j= press_0(l);
      xo= cp[j].x;
      x=xo;
      yo= cp[j].y;
      y= yo;

    }
    
    IrReceiver.resume(); // Prepare for next signal
  }
  //g= gas_s();
  f.close();
  f1.close();
  delay(150);
}
