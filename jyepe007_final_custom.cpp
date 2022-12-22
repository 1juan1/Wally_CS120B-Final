#include <stdlib.h>
#include <EEPROM.h>


// initialze OUTPUTS
int red = 9;
int green = 8;
int blue = 2;
int pwr_btn = 13;
int rst_btn = 10;

#define echoPin 12
#define trigPin 11
long time1 = 0;
long time2 = 0;


enum pins {
  PIN_CLK = 3,
  PIN_DN = 4,
  PIN_DC = 5,
  PIN_RST = 6,
  PIN_SCE = 7,
  };

  
//GAME SCORES
float seconds = 0;
int gameLvl=0;


// PWR SM
int pb_check;
int pb_val;



// RST SM 
int rst_check;
int rst_val;


// GLOBAL VARIABLES
 int pwr;
 int rst;
 long duration;
 int distance;
 


// NOKIA SCREEN 
char string1[8];
long seed = 1;

float Random() {

  const long a = 16807;
  const long m = 2147483647;
  const long q = 127773;
  const long r = 2836;

  long lo;
  long hi;
  long test;
  float escape;

  hi = seed / q;
  lo = seed % q;
  test = a * lo - r * hi;

  if(test > 0){
    seed = test;
    }

    else{
      seed = test + m;
      }
   escape = ((float)seed / m);
      return escape;
  }


int rngDist;
int dog = 21*Random();
int randdd = 21*Random();

int cat = 21*Random();
int rngDist1 = 21*Random();
int rngDist2 = 21*Random();
int rngDist3 = 21*Random();
int rngDist4 = 21*Random();
int grape = 21*Random();

int properRandom(int r){
  while(r <=1){
    r = 21 * Random();
    }

    return r;
  }

static const char ASCII[][5] =
{
{0x00, 0x00, 0x00, 0x00, 0x00}, // 20
{0x00, 0x00, 0x5f, 0x00, 0x00}, // 21 !
{0x00, 0x07, 0x00, 0x07, 0x00}, // 22 "
{0x14, 0x7f, 0x14, 0x7f, 0x14}, // 23 #
{0x24, 0x2a, 0x7f, 0x2a, 0x12}, // 24 $
{0x23, 0x13, 0x08, 0x64, 0x62}, // 25 %
{0x36, 0x49, 0x55, 0x22, 0x50}, // 26 &
{0x00, 0x05, 0x03, 0x00, 0x00}, // 27 ’
{0x00, 0x1c, 0x22, 0x41, 0x00}, // 28 (
{0x00, 0x41, 0x22, 0x1c, 0x00}, // 29 )
{0x14, 0x08, 0x3e, 0x08, 0x14}, // 2a *
{0x08, 0x08, 0x3e, 0x08, 0x08}, // 2b +
{0x00, 0x50, 0x30, 0x00, 0x00}, // 2c ,
{0x08, 0x08, 0x08, 0x08, 0x08}, // 2d -
{0x00, 0x60, 0x60, 0x00, 0x00}, // 2e .
{0x20, 0x10, 0x08, 0x04, 0x02}, // 2f /
{0x3e, 0x51, 0x49, 0x45, 0x3e}, // 30 0
{0x00, 0x42, 0x7f, 0x40, 0x00}, // 31 1
{0x42, 0x61, 0x51, 0x49, 0x46}, // 32 2
{0x21, 0x41, 0x45, 0x4b, 0x31}, // 33 3
{0x18, 0x14, 0x12, 0x7f, 0x10}, // 34 4
{0x27, 0x45, 0x45, 0x45, 0x39}, // 35 5
{0x3c, 0x4a, 0x49, 0x49, 0x30}, // 36 6
{0x01, 0x71, 0x09, 0x05, 0x03}, // 37 7
{0x36, 0x49, 0x49, 0x49, 0x36}, // 38 8
{0x06, 0x49, 0x49, 0x29, 0x1e}, // 39 9
{0x00, 0x36, 0x36, 0x00, 0x00}, // 3a :
{0x00, 0x56, 0x36, 0x00, 0x00}, // 3b ;
{0x08, 0x14, 0x22, 0x41, 0x00}, // 3c <
{0x14, 0x14, 0x14, 0x14, 0x14}, // 3d =
{0x00, 0x41, 0x22, 0x14, 0x08}, // 3e >
{0x02, 0x01, 0x51, 0x09, 0x06}, // 3f ?
{0x32, 0x49, 0x79, 0x41, 0x3e}, // 40 @
{0x7e, 0x11, 0x11, 0x11, 0x7e}, // 41 A
{0x7f, 0x49, 0x49, 0x49, 0x36}, // 42 B
{0x3e, 0x41, 0x41, 0x41, 0x22}, // 43 C
{0x7f, 0x41, 0x41, 0x22, 0x1c}, // 44 D
{0x7f, 0x49, 0x49, 0x49, 0x41}, // 45 E
{0x7f, 0x09, 0x09, 0x09, 0x01}, // 46 F
{0x3e, 0x41, 0x49, 0x49, 0x7a}, // 47 G
{0x7f, 0x08, 0x08, 0x08, 0x7f}, // 48 H
{0x00, 0x41, 0x7f, 0x41, 0x00}, // 49 I
{0x20, 0x40, 0x41, 0x3f, 0x01}, // 4a J
{0x7f, 0x08, 0x14, 0x22, 0x41}, // 4b K
{0x7f, 0x40, 0x40, 0x40, 0x40}, // 4c L
{0x7f, 0x02, 0x0c, 0x02, 0x7f}, // 4d M
{0x7f, 0x04, 0x08, 0x10, 0x7f}, // 4e N
{0x3e, 0x41, 0x41, 0x41, 0x3e}, // 4f O
{0x7f, 0x09, 0x09, 0x09, 0x06}, // 50 P
{0x3e, 0x41, 0x51, 0x21, 0x5e}, // 51 Q
{0x7f, 0x09, 0x19, 0x29, 0x46}, // 52 R
{0x46, 0x49, 0x49, 0x49, 0x31}, // 53 S
{0x01, 0x01, 0x7f, 0x01, 0x01}, // 54 T
{0x3f, 0x40, 0x40, 0x40, 0x3f}, // 55 U
{0x1f, 0x20, 0x40, 0x20, 0x1f}, // 56 V
{0x3f, 0x40, 0x38, 0x40, 0x3f}, // 57 W
{0x63, 0x14, 0x08, 0x14, 0x63}, // 58 X
{0x07, 0x08, 0x70, 0x08, 0x07}, // 59 Y
{0x61, 0x51, 0x49, 0x45, 0x43}, // 5a Z
{0x00, 0x7f, 0x41, 0x41, 0x00}, // 5b [
{0x02, 0x04, 0x08, 0x10, 0x20}, // 5c ¥
{0x00, 0x41, 0x41, 0x7f, 0x00}, // 5d ]
{0x04, 0x02, 0x01, 0x02, 0x04}, // 5e ^
{0x40, 0x40, 0x40, 0x40, 0x40}, // 5f _
{0x00, 0x01, 0x02, 0x04, 0x00}, // 60 `
{0x20, 0x54, 0x54, 0x54, 0x78}, // 61 a
{0x7f, 0x48, 0x44, 0x44, 0x38}, // 62 b
{0x38, 0x44, 0x44, 0x44, 0x20}, // 63 c
{0x38, 0x44, 0x44, 0x48, 0x7f}, // 64 d
{0x38, 0x54, 0x54, 0x54, 0x18}, // 65 e
{0x08, 0x7e, 0x09, 0x01, 0x02}, // 66 f
{0x0c, 0x52, 0x52, 0x52, 0x3e}, // 67 g
{0x7f, 0x08, 0x04, 0x04, 0x78}, // 68 h
{0x00, 0x44, 0x7d, 0x40, 0x00}, // 69 i
{0x20, 0x40, 0x44, 0x3d, 0x00}, // 6a j
{0x7f, 0x10, 0x28, 0x44, 0x00}, // 6b k
{0x00, 0x41, 0x7f, 0x40, 0x00}, // 6c l
{0x7c, 0x04, 0x18, 0x04, 0x78}, // 6d m
{0x7c, 0x08, 0x04, 0x04, 0x78}, // 6e n
{0x38, 0x44, 0x44, 0x44, 0x38}, // 6f o
{0x7c, 0x14, 0x14, 0x14, 0x08}, // 70 p
{0x08, 0x14, 0x14, 0x18, 0x7c}, // 71 q
{0x7c, 0x08, 0x04, 0x04, 0x08}, // 72 r
{0x48, 0x54, 0x54, 0x54, 0x20}, // 73 s
{0x04, 0x3f, 0x44, 0x40, 0x20}, // 74 t
{0x3c, 0x40, 0x40, 0x20, 0x7c}, // 75 u
{0x1c, 0x20, 0x40, 0x20, 0x1c}, // 76 v
{0x3c, 0x40, 0x30, 0x40, 0x3c}, // 77 w
{0x44, 0x28, 0x10, 0x28, 0x44}, // 78 x
{0x0c, 0x50, 0x50, 0x50, 0x3c}, // 79 y
{0x44, 0x64, 0x54, 0x4c, 0x44}, // 7a z
{0x00, 0x08, 0x36, 0x41, 0x00}, // 7b {
{0x00, 0x00, 0x7f, 0x00, 0x00}, // 7c |
{0x00, 0x41, 0x36, 0x08, 0x00}, // 7d }
{0x10, 0x08, 0x08, 0x10, 0x08}, // 7e ?
{0x00, 0x06, 0x09, 0x09, 0x06}, // 7f ?
};

   enum instructions {
    
    FUNCTION_SET =  bit(5),
    BASIC_INSTR  =  FUNCTION_SET,
    EXTENDED_INSTR = FUNCTION_SET | bit(0),
    DISPLAY_CONTROL = bit(3),

    SET_Y = bit(6),
    SET_X = bit(7),
    NORMAL_MODE = DISPLAY_CONTROL | bit(2),
    BIAS_SYS = bit(4),
    MUX_48  = BIAS_SYS | bit(1) | bit(0),
    SET_VOP = bit(7),
    };

// used code from: https://forum.arduino.cc/t/anyone-know-the-code-for-the-shiftout-function/45638
void shifter(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
      uint8_t i;

      for (i = 0; i < 8; i++)  {
            if (bitOrder == LSBFIRST)
                  digitalWrite(dataPin, !!(val & (1 << i)));
            else      
                  digitalWrite(dataPin, !!(val & (1 << (7 - i))));
                  
            digitalWrite(clockPin, HIGH);
            digitalWrite(clockPin, LOW);            
      }
}

void send_cmd(uint8_t cmd){
  digitalWrite(PIN_SCE, 1);
  digitalWrite(PIN_CLK, 0);
  digitalWrite(PIN_DC, 0);
  digitalWrite(PIN_SCE, 0);
  shifter(PIN_DN, PIN_CLK, MSBFIRST, cmd);
  digitalWrite(PIN_SCE, 1);
  
  
  }


 void send_data(uint8_t dta){
  digitalWrite(PIN_SCE, 1);
  digitalWrite(PIN_CLK, 0);
  digitalWrite(PIN_DC, 1);
  digitalWrite(PIN_SCE, 0);
  shiftOut(PIN_DN, PIN_CLK, MSBFIRST, dta);
  digitalWrite(PIN_SCE, 1);
   
  }

  void initial(void) {

  digitalWrite(PIN_RST, 1);
  digitalWrite(PIN_SCE, 1);

  digitalWrite(PIN_RST, 0);
  delay(1);
  digitalWrite(PIN_RST, 1);
  send_cmd(EXTENDED_INSTR); // using the extended instruction set
  send_cmd(MUX_48); // SENDING MUX TO 1:48
  send_cmd(SET_VOP | 0x20);
  send_cmd(BASIC_INSTR);
  send_cmd(NORMAL_MODE);
}

void lcd_xy(int x, int y){
      send_cmd(0x80 | x);
      send_cmd(0x40 | y);
      }

void send_char(char c){
  int i;
  for(i = 0; i < 5; i++){
    send_data(ASCII[c - 0x20][i]);
    }

    send_data(0x00);
  }

void lcd_write(char *str){
    
  while(*str){
    send_char(*str++);
    }
  }


  void lcd_clear(void){
    send_cmd(SET_Y | 0x00);
    send_cmd(SET_X | 0x00);
    int i;
    for(i = 0; i < 504; i++){
      send_data(0x00);
      }
     }
    

     void res_func(){
      digitalWrite(PIN_RST, 0);
      delay(1);
      digitalWrite(PIN_RST, 1);
      }


      

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int(*TickFct)(int);
  } task;

const unsigned short tasksNum = 6;
task tasks[tasksNum];


enum nokia_states {N_INIT, N_WAIT, N_ON};
int NOKIA_Tick(int nState){
  switch(nState){
    case N_INIT:

        nState = N_WAIT;
      break;

    case N_WAIT:

        if(pwr == 1){
          nState = N_ON;
          }

          else {
            nState = N_WAIT;
            }
      break;
    case N_ON:

        if(pwr == 0){
          nState = N_WAIT;
          }

          else {
            nState = N_ON;
            }
      break;
    }

    switch(nState){
    case N_INIT:
      break;

      case N_WAIT:
      lcd_clear();
      break;

    case N_ON:
        
        
        lcd_clear();
        lcd_xy(8,0);
        lcd_write("WALLY SCORES");
        lcd_xy(0,1);
        lcd_write("1. ");
        lcd_write(dtostrf(EEPROM.read(0), 4, 0, string1));
        lcd_xy(0,2);
        lcd_write("2. ");
        lcd_write(dtostrf(EEPROM.read(1), 4, 0, string1));
        lcd_xy(0,3);
        lcd_write("3. ");
        lcd_write(dtostrf(EEPROM.read(2), 4, 0, string1));
        lcd_xy(0,4);
        lcd_write("4. ");
        lcd_write(dtostrf(EEPROM.read(3), 4, 0, string1));
        lcd_xy(0,5);
        lcd_write("5. ");
        lcd_write(dtostrf(EEPROM.read(4), 4, 0, string1));
      break;
    }
    return nState;
  }

enum game_states {GAME_INIT, GAME_WAIT, GAME1,GAME2, GAME3, GAME4, GAME5, GAME_END};
int GAME_Tick(int gState){
  switch(gState){
    case GAME_INIT:   //TRANSITIONS

        gState = GAME_WAIT;
    
      break;
      
    case GAME_WAIT:
        
        
        if(pwr == 1){
          gameLvl++;
          seconds = 0;
          gState = GAME1;
          
          }

          
      break;

    case GAME1:
    
      if(pwr == 1){
        rngDist = cat;
      if(distance == cat){
        EEPROM.write(0, seconds);
        gameLvl++;
        seconds = 0;
        properRandom(rngDist1);
        gState = GAME2;
        }

      }
      break;


      case GAME2:

      if(pwr == 1){
        rngDist = rngDist1;
      if(distance == rngDist1){
        EEPROM.write(1, seconds);
        gameLvl++;
        seconds = 0;
        gState = GAME3;
        }

      }

        break;


      case  GAME3:
        if(pwr == 1){
        rngDist = rngDist2;
      if(distance == rngDist){
        EEPROM.write(2, seconds);
        gameLvl++;
        seconds = 0;
        gState = GAME4;
        }

      }
      
        break;

      case GAME4:

      if(pwr == 1){
        rngDist = rngDist3;
      if(distance == rngDist){
        EEPROM.write(3, seconds);
        gameLvl++;
        seconds = 0;
        gState = GAME5;
        }

      }
        break;

      case GAME5:

         if(pwr == 1){
        rngDist = grape;
      if(distance == rngDist){
        EEPROM.write(4, seconds);
        gameLvl++;
        seconds = 0;
        gState = GAME_END;
        }

      }
        break;

        
      case GAME_END:

      if (digitalRead(rst_btn) == 0){
        
        gState = GAME_WAIT ;
        }

      

      break;
      
    }


    switch(gState){  // ACTIONS
    case GAME_INIT:
      break;
      
    case GAME_WAIT:
        gameLvl =0;
        EEPROM.write(0, 0);
        EEPROM.write(1, 0);
        EEPROM.write(2, 0);
        EEPROM.write(3, 0);
        EEPROM.write(4, 0);
    
      break;

    case GAME1:
        seconds++;
        Serial.print("random1: ");
        Serial.println(cat);
      break;

    case GAME2:
        seconds++;

        Serial.print("random2: ");
        Serial.println(rngDist1);
      break;


    case  GAME3:
        seconds++;
        Serial.print("random3: ");
        Serial.println(rngDist2);
        break;
      case GAME4:
          seconds++;
          Serial.print("random4: ");
          Serial.println(rngDist3);
        break;

      case GAME5:
          seconds++;
          Serial.print("random5: ");
          Serial.println(grape);
        break;

     case GAME_END:
      Serial.print(analogRead(rst_btn));
     
        
      break;
      
    }

    return gState;
  }

enum lit_states {LIT_INIT, LIT_WAIT, LIT_ON};
int LIT_Tick(int lState){
  switch(lState){
    case LIT_INIT:
        lState = LIT_WAIT;
      break;
    case LIT_WAIT:
        if(pwr == 1){
          lState = LIT_ON;
          }

          else{
            lState = LIT_WAIT;
            }
      break;

    case LIT_ON:
          if(pwr == 0){
          lState = LIT_WAIT;
          }

          else{
            lState = LIT_ON;
            }
      break;
    }

    switch(lState){
    case LIT_INIT:
      break;
    case LIT_WAIT:
          digitalWrite(red,0);
          digitalWrite(green,0);
          digitalWrite(blue, 0);
    
      break;

    case LIT_ON:

    
      if(gameLvl == 6){
                digitalWrite(red,1);
               digitalWrite(green,1);
               digitalWrite(blue, 1);
                }

        else if(distance < rngDist){
          digitalWrite(red,1);
          digitalWrite(green,0);
          digitalWrite(blue, 0);
          }

          else if(distance > rngDist){
            digitalWrite(red,0);
            digitalWrite(green,0);
            digitalWrite(blue, 1);
            }

            else if(distance == rngDist){
               digitalWrite(red,0);
               digitalWrite(green,1);
               digitalWrite(blue, 0);
              }

              if(gameLvl == 6){
                digitalWrite(red,1);
               digitalWrite(green,1);
               digitalWrite(blue, 1);
                }
      break;
    }
    return lState;
  }

enum mea_states { MEA_INIT, MEA_WAIT, MEA_ON};
int MEA_Tick(int mState){
  switch(mState){
    case MEA_INIT:
        mState = MEA_WAIT;
     break;

    case MEA_WAIT:

      if(pwr == 1){
        mState = MEA_ON;
        }

        else {
          mState = MEA_WAIT;
          }
    
     break;

    case MEA_ON:
      if(pwr == 0){
        mState = MEA_WAIT;
        }

        else {
          mState = MEA_ON;
          }
     break;
    }
  
  switch(mState){
    case MEA_INIT:
     break;

    case MEA_WAIT:
     break;

    case MEA_ON:
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds


  
        while (digitalRead(echoPin) == 0) {
        }
        time1 = micros();
        while (digitalRead(echoPin) == 1) {
        }
        time2 = micros();
        
        duration = time2 - time1;
  // Calculating the distance
      distance = duration * 0.034 / 2; 
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
     break;
    }
  return mState;
  }


 enum res_states {RST_INIT, RST_WAIT, RST_ON};
 int RST_Tick(int rstState){
  switch(rstState){   //TRANSITIONS ACTIONS
    case RST_INIT:
       rstState = RST_WAIT;
      break;

    case RST_WAIT:   
           if(rst_val == 1){
            rstState = RST_ON;
            }
      break;

    case RST_ON:
      rst = 0;
      break;
    }
  switch(rstState){ // STATE ACTIONS
    case RST_INIT:
      break;

    case RST_WAIT:
      rst_check = digitalRead(rst_btn);
      if(rst_check == 0){
        rst_val = 1;
        }  
      break;

    case RST_ON:
      rst = 1;
      rst_val = 0;
      
      break;
    }
  return rstState ;
  }

 enum POWER_States {PWR_INIT, PWR_BEGIN, PWR_ON, PWR_OFF};
 int POWER_Tick(int pwrState){
  
  switch(pwrState){
    case PWR_INIT:
      pwrState = PWR_BEGIN;
      break;

   case PWR_BEGIN:
      if(pb_val == 1){
        pwrState = PWR_ON;
      }

      else{
        pwrState = PWR_BEGIN;
        }
     break;

    case PWR_ON:
      if(pb_val == 1){
        pwrState = PWR_OFF;
      }

      else if(pb_val == 0){
        pwrState = PWR_ON;
        }
      break;

    case PWR_OFF:
      if(pb_val == 1){
        pwrState = PWR_ON;
      }

      else if(pb_val == 0){
        pwrState = PWR_OFF;
        }
      break;
    }
  switch(pwrState){

    case PWR_INIT:
      break;

    case PWR_BEGIN:
      pb_check = digitalRead(pwr_btn);
     
       if(pb_check == 1){
        pb_val = 1;
        }

        
        break;
        
    case PWR_ON:
      pb_val = 0;
       pb_check = digitalRead(pwr_btn);
       
       if(pb_check == 1){
        pb_val = 1;
        } 
      pwr = 1;
      
      break;

      case PWR_OFF:
      pb_val = 0;
      pb_check = digitalRead(pwr_btn);
      
       if(pb_check == 1){
        pb_val = 1;
        }
        pwr = 0;
       
       break;
    
    }
    return pwrState;
  }

void setup() {
  // put your setup code here, to run once
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(pwr_btn, INPUT_PULLUP);
  pinMode(rst_btn, INPUT_PULLUP);

  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_DN, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_RST, OUTPUT);
  pinMode(PIN_SCE, OUTPUT);


  //sonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);

  digitalWrite(PIN_RST, 1);
  digitalWrite(PIN_SCE, 1);

  initial();



  send_cmd(EXTENDED_INSTR); // using the extended instruction set
  send_cmd(MUX_48); // SENDING MUX TO 1:48
  send_cmd(SET_VOP | 0x25);
  send_cmd(BASIC_INSTR);
  send_cmd(NORMAL_MODE);

  unsigned char i = 0;
  tasks[i].state = PWR_INIT;
  tasks[i].period = 300;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &POWER_Tick;
  i++;
  tasks[i].state = RST_INIT;
  tasks[i].period = 200;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &RST_Tick;
  i++;
  tasks[i].state = MEA_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &MEA_Tick;
  i++;
  tasks[i].state = LIT_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &LIT_Tick;
  i++;
  tasks[i].state = GAME_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &GAME_Tick;
  i++;
  tasks[i].state = N_INIT;
  tasks[i].period = 2000;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &NOKIA_Tick;
  
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}
