#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
Servo servo1,servo2;
LiquidCrystal_I2C lcd(32,16,2);

uint8_t pinler[4]={A0,A1,3,5};
int ortalama1,ortalama2;
int sens1_deger,sens2_deger;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  if(!Serial)
  {
    Serial.println(F("Seri haberlesme baslatilamadi"));
    while(-1);
  }
  else
  {
    for(uint8_t i=0; i<4; i++)
    {
      if(i==0 or i==1){pinMode(pinler[i],INPUT);}
      else if(i==2){servo1.attach(pinler[i]);servo1.write(0);}
      else {servo2.attach(pinler[i]);servo2.write(0);}
    }
  }
  lcd.init();lcd.backlight();
  lcd.setCursor(2,0);lcd.print(F("DENGE SISTEMI"));
  
  
}

void loop()
{
  sens1_deger=egim_sens_1_y(2,pinler[0]);
  sens2_deger=egim_sens_2_y(2,pinler[1]);
 
  sens1_deger=map(sens1_deger,255,59,0,180);
  sens2_deger=map(sens2_deger,255,59,0,180);
   
  servo_sol_aci(sens1_deger);
  servo_sag_aci(sens2_deger);
  lcd_ekran();
  
}
int egim_sens_1_y(uint8_t limit,uint8_t p) {
 	
  uint16_t sens_degeri;
  if(!bool(0))
  {
    for(uint8_t x=0; x<limit; x++)
    {
      sens_degeri=analogRead(p);
      ortalama1+=sens_degeri;
    }
    ortalama1=(ortalama1/(limit+1));
  }
  return ortalama1;

}
int egim_sens_2_y(uint8_t limit,uint8_t p) {
 	
  uint16_t sens_degeri;
  if(!bool(0))
  {
    for(uint8_t x=0; x<limit; x++)
    {
      sens_degeri=analogRead(p);
      ortalama2+=sens_degeri;
    }
    ortalama2=(ortalama2/(limit+1));
  }
  return ortalama2;

}

void servo_sol_aci(uint8_t aci) {
  servo1.write(aci);
  
}
void servo_sag_aci(uint8_t aci) {
  servo2.write(aci);
  
}

void lcd_ekran(void) {
 
  lcd.setCursor(1,1);lcd.print(F("SAG="));lcd.print(sens1_deger);
  if(sens1_deger<10){lcd.setCursor(6,1);lcd.print(F(" "));}
  else if(sens1_deger<100){lcd.setCursor(7,1);lcd.print(F(" "));}
  lcd.setCursor(8,1);lcd.print(F("SOL="));lcd.print(sens2_deger);
  if(sens2_deger<10){lcd.setCursor(13,1);lcd.print(F(" "));}
  else if(sens2_deger<100){lcd.setCursor(14,1);lcd.print(F(" "));}

}

