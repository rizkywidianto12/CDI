
#include <parsing.h>


int CDI() 
{
  // uint8_t map1 [30] = { E_0, E_500, E_1000, E_1500, E_2000, E_2500, E_3000, E_3500, E_4000, E_4500, E_5000, E_5500, E_6000, E_6500, E_7000, E_7500, E_8000, E_8500, E_9000, E_9500, E_10000, E_10500, E_11000, E_11500, E_12000, E_12500, E_13000, E_13500, E_14000, E_14500 };
  uint8_t led = 0;
  uint32_t pulse_delay,curve_select;
  PORTB = 0x02;
  DDRB  = 0x22;
  TCCR1B = 0x03;
  while (true)
  {    
    while ((PINB&0x01)==0x00);
    while ((PINB&0x01)==0x01);
    pulse_delay = TCNT1;
    TCNT1 = 0;
    curve_select = 30000/pulse_delay;
    pulse_delay *= pulser_angle - map1[curve_select];
    pulse_delay /= 360;
    led++;
    if(led==8)
    {
      PORTB = 0x22;
      led = 0;
    }
    if(curve_select < 30)
    {
      while(TCNT1<pulse_delay);
      PORTB = 0x00;
      while(TCNT1<pulse_delay+25);
      PORTB = 0x02;
    }
  }
}

void map_update()
{
    bluetooth.println("update");
  for (int i = 0; i<30 ; i++){
    bluetooth.println(i);
    uint8_t b = EEPROM.read(i);
    bluetooth.println(b);
    delay(100);
    
    map1[i] = b;
  }
}

void reset(){
  for(int i = 0; i < 31; i++){
    map1[i] = map_default[i];
  }
}

void report_function(){ // print nilai ke bluetooth serial

    bluetooth.print("report");
  for(i=0;i<30;i++){
    int report = map1[i];
    bluetooth.println(report);
  }
    bluetooth.println("end");
}


void error_1() {
  bluetooth.print(action);
  bluetooth.println("error code");
}

void parsingData() {

  dt[0] = "";
  if (dataIn[0] == 'A' && dataIn[1] == 'A') {
    action += 1;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'B') {
    action += 2;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'C') {
    action += 3;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'D') {
    action += 4;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'E') {
    action += 5;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'F') {
    action += 6;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'G') {
    action += 7;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'H') {
    action += 8;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'I') {
    action += 9;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'J') {
    action += 10;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'K') {
    action += 11;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'L') {
    action += 12;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'M') {
    action += 13;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'N') {
    action += 14;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'O') {
    action += 15;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'P') {
    action += 16;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'Q') {
    action += 17;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'R') {
    action += 18;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'S') {
    action += 19;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'T') {
    action += 20;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'U') {
    action += 21;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'V') {
    action += 22;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'W') {
    action += 23;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'X') {
    action += 24;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'Y') {
    action += 25;
  }
  else if (dataIn[0] == 'A' && dataIn[1] == 'Z') {
    action += 26;
  }
  else if (dataIn[0] == 'B' && dataIn[1] == 'A') {
    action += 27;
  }
  else if (dataIn[0] == 'B' && dataIn[1] == 'B') {
    action += 28;
  }
  else if (dataIn[0] == 'B' && dataIn[1] == 'C') {
    action += 29;
  }
  else if (dataIn[0] == 'B' && dataIn[1] == 'D') {
    action += 30;
  }

  else if (dataIn[0] =='S')
  {
    reset();
  }

  else if (dataIn[0] =='R' && dataIn[1] == 'T')
  {
    report_function();
  }

  else if (dataIn[0] =='U' && dataIn[1] == 'P')
  {
    map_update();
  }
  

  else error_1();

  //proses parsing data

  for (i = 2; i < dataIn.length(); i++) {
    dt[0] = dt[0] + dataIn[i];
  }

if (action){
  bluetooth.println(action);
  int data_value = dt[0].toInt();
  bluetooth.println(data_value);
  EEPROM.update(action-1,data_value);
}
// else error_1();
/*
  if (action) {

    if (action == 1) {
      bluetooth.println(dt[0]);
      EEPROM.
    }
    else if (action == 2) {
    }
    else if (action == 3) {
    }
    else if (action == 4) {
    }
    else if (action == 5) {
    }
    else if (action == 6) {
    }
    else if (action == 7) {
    }
    else if (action == 8) {
    }
    else if (action == 9) {
    }
    else if (action == 10) {
    }
    else if (action == 11) {
    }
    else if (action == 12) {
    }
    else if (action == 13) {
    }
    else if (action == 14) {
    }
    else if (action == 15) {
    }
    else if (action == 16) {
    }
    else if (action == 17) {
    }
    else if (action == 18) {
    }
    else if (action == 19) {
    }
    else if (action == 20) {
    }
    else if (action == 21) {
    }
    else if (action == 22) {
    }
    else if (action == 23) {
    }
    else if (action == 24) {
    }
    else if (action == 25) {
    }
    else if (action == 26) {
    }
    else if (action == 27) {
    }
    else if (action == 28) {
    }
    else if (action == 29) {
    }
    else if (action == 30) {
    }
    else if (action == 31) {
    }

      else error_1();
  }
*/
}
void parsing_function() 
{
  if (bluetooth.available() > 0) {
    delay(1);
    char inChar = (char)bluetooth.read();
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
  action = NO_ACTION;
}


void setup() 
{
  bluetooth.begin(9600);
  EEPROM.begin();
  uint8_t wrote = EEPROM.read(1);
  bluetooth.println(wrote);
  if (0){ //wrote == 0){
    for(i = 0 ; i < 30 ; i++){
      EEPROM.write(i,map_default[i]);
    }
    EEPROM.update(255,1);
  }
}

void loop() {
    parsing_function();
}