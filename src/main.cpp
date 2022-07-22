#include <Arduino.h>



void parsing_function() {
  if (Serial.available() > 0) {
    delay(10);
    char inChar = (char)Serial.read();
    inChar = toUpperCase(inChar);
    dataIn += inChar;
    if (inChar == '\n') {
      parsing = true;
    }
  }
  if (parsing) {
    parsingData();
    parsing = false;
    dataIn = "";
  }
  pinRead();
  action = NO_ACTION;
  delay(100);
}

void parsingData() {

  dt[0] = "";
  if (dataIn[0] == 'I') {
    action += OIL_CHANGE_IN;
  }
  else if (dataIn[0] == 'N') {
    action += OIL_CHANGE_SEC;
  }
  else if (dataIn[0] == 'O') {
    action += OIL_ON;
  }
  else if (dataIn[0] == 'C') {
    action += ALARM_CLEAR;
  }
  else error_1();
  //proses parsing data
  for (i = 1; i < dataIn.length(); i++) {
    //pengecekan tiap karakter dengan karakter (#) dan (,)

    //proses tampung data saat pengecekan karakter selesai.
    dt[0] = dt[0] + dataIn[i];

  }
  if (action) {

    if (action == OIL_CHANGE_IN) {
      Tcount=dt[0].toInt();
      if(Tcount>99||Tcount==0) {
        error_1(); 
        return;
      }
      EEPROM.update(0,Tcount);
      ReadC = EEPROM.read(0);
      //Serial.print("Interval = ");
      //Serial.println(ReadC);
      Serial.println("OK");
      action = NO_ACTION;
    }
    else if (action == OIL_CHANGE_SEC) {
      TcountOn=dt[0].toInt();
      if(TcountOn>60||TcountOn==0){
        error_1();
        return;
      }
      EEPROM.update(1,TcountOn);
      ReadOn = EEPROM.read(1);
      //Serial.print("ON Time = ");
      //Serial.println(ReadOn);
      Serial.println("OK");
      action = NO_ACTION;
    }
    else if (action == OIL_ON){
      if(dt[0].toInt()==1){
        Serial.println("OK");
        digitalWrite(Oil_Pump,HIGH);
        //Serial.println("OLI_ON");
        delay (TcountOn*1000);
        digitalWrite(Oil_Pump,LOW);
        //Serial.println("OLI_OFF");
      } else {
        digitalWrite(Oil_Pump,LOW);
        //Serial.println("OLI_OFF");
      }
      action = NO_ACTION;
      }
      else if (action == ALARM_CLEAR){
        if(dt[0].toInt()==1){
          Serial.println("OK");
          digitalWrite(Alarm_Clear,HIGH);
          delay (1000);
          digitalWrite(Alarm_Clear,LOW);
          action = NO_ACTION;
        }
      }
      else error_1();
  }
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}