//program 1
******************************************************************************
#define pulser_angle 82
#define E_0     0
#define E_500   8
#define E_1000  15
#define E_1500  20
#define E_2000  24
#define E_2500  28
#define E_3000  30
#define E_3500  32
#define E_4000  34
#define E_4500  34
#define E_5000  34
#define E_5500  34
#define E_6000  34
#define E_6500  34
#define E_7000  34
#define E_7500  34
#define E_8000  34
#define E_8500  34
#define E_9000  34
#define E_9500  34
#define E_10000 34
#define E_10500 32
#define E_11000 30
#define E_11500 27
#define E_12000 23
#define E_12500 19
#define E_13000 17
#define E_13500 15
#define E_14000 15
#define E_14500 15

int main() 
{
  uint8_t map1 [30] = { E_0, E_500, E_1000, E_1500, E_2000, E_2500, E_3000, E_3500, E_4000, E_4500, E_5000, E_5500, E_6000, E_6500, E_7000, E_7500, E_8000, E_8500, E_9000, E_9500, E_10000, E_10500, E_11000, E_11500, E_12000, E_12500, E_13000, E_13500, E_14000, E_14500 };
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
******************************************************************************
