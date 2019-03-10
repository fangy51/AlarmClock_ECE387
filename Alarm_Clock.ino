



//Alarm clock
//Yifan Fang, ECE387, Spring 2019

#include <Wire.h>
#include <RTClib.h>

int hr;
int mint;
int buzzer = 13;
bool set = false;
extern volatile unsigned long timer0_millis;
void setup(){

  pinMode(9, INPUT);//button for 'set'
  pinMode(10, INPUT);//button for '+1'
  pinMode(11, INPUT);//button for '-1'
  pinMode(12, INPUT);//button for 'switch set alarm between hour and minute'
  pinMode(8,INPUT);//button for 'on/off' alarm
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);

}
//set alarm hour range: 0-23, minute range: 0-59
void setAlarm(){
  hr = 0;
  mint = 0;
  //set button
  if(digitalRead(9) != HIGH){
  //switch button(hour)  
    if(digitalRead(12) == HIGH){
  //+1    
    if(digitalRead(10) == HIGH){
      delay(1000);
      if(hr < 23){
         hr = hr + 1;
      }else{
        hr = 0;
      }
      }
    //-1  
    if(digitalRead(11) == HIGH){
      delay(1000);
      if(hr > 0){
         hr = hr - 1;
      }else{
        hr = 23;
      }
      }
  }
  //switch button(minute)
  if(digitalRead(12) != HIGH){
    if(digitalRead(10) == HIGH){
      delay(1000);
      if(mint < 59){
         mint = mint + 1;
      }else{
        mint = 0;
      }
      }
    if(digitalRead(11) == HIGH){
      delay(1000);
      if(mint > 0){
         hr = mint - 1;
      }else{
        mint = 59;
      }
      }
    }
  }
  Serial.print("SetAlarm: ");
  Serial.print(hr);
  Serial.print(" hour, ");
  Serial.print(mint);
  Serial.print(" minute");
  if(!set){
    Serial.println("alarm off!");
    }
}

void loop(){
  if(digitalRead(8) == HIGH){
    set = true;
    }
  if(digitalRead(8) != HIGH){
    set = false;
    }  
    //sound when system time >= alarm set
  if(millis() >= ((hr*60*60000) + (mint*60000)) && set){
    tone(buzzer,1000);
    delay(3000);//sound on for 3s
    noTone(buzzer);
    delay(1000);//sound off for 1s
    }
    //display something when system time < alarm set
   if(set){
    Serial.print("not time yet(repeat per 30s)");
    delay(30000);
    }
    //if one day is passed reset millis() to 0
    if(millis() >= (24*60*60000)){
      noInterrupts ();
      timer0_millis = 0;
      interrupts (); 
      }
  }
