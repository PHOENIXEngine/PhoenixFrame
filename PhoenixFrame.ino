// PhoenixFrame

#include <LedControl.h>
#include <Servo.h> 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <IRremote.h>    

// Move
int pinL0=4;
int pinL1=5;
int pinLSpeed = 3;
int pinR0=7;
int pinR1=8;
int pinRSpeed = 9;

bool IsSmiple = false;
void vehicleSet(int pL0, int pL1, int sL,
  int pR0, int pR1, int sR)
{
  IsSmiple = false;
  pinL0 = pL0;
  pinL1 = pL1;
  pinLSpeed = sL;
  pinR0 = pR0;
  pinR1 = pR1;
  pinRSpeed = sR;
  
  pinMode(pinL0, OUTPUT);
  pinMode(pinL1, OUTPUT);
  
  pinMode(pinR0, OUTPUT);
  pinMode(pinR1, OUTPUT);

  pinMode(pinLSpeed, OUTPUT);
  pinMode(pinRSpeed, OUTPUT);
    
  leftGo(0);
  rightGo(0);
  leftSpeed(0);
  rightSpeed(0);  
}
void vehicleSetSimple()
{
  IsSmiple = true;
  pinL0 = 12;
  pinL1 = 12;
  pinLSpeed = 10;
  pinR0 = 13;
  pinR1 = 13;
  pinRSpeed = 11;

  pinMode(pinL0, OUTPUT);  
  pinMode(pinR0, OUTPUT);
  pinMode(pinLSpeed, OUTPUT);
  pinMode(pinRSpeed, OUTPUT);
}
void leftGo(int val)
{
  if (!IsSmiple)
  {
      if (1 == val)
      {
        digitalWrite(pinL0, LOW); 
        digitalWrite(pinL1, HIGH); 
       }
       else if (2 == val)
       {
          digitalWrite(pinL0, HIGH); 
          digitalWrite(pinL1, LOW); 
       }
       else if (0 == val)
       {
          digitalWrite(pinL0, LOW); 
          digitalWrite(pinL1, LOW); 
       }
  }
  else
  {
    if (1 == val)
      digitalWrite(pinL0,HIGH);
    else
      digitalWrite(pinL0,LOW);
  }
}
void leftSpeed(int val)
{
     analogWrite(pinLSpeed, val);
}
void rightGo(int val)
{
  if (!IsSmiple)
  {
    if (1 == val)
    {
      digitalWrite(pinR0, HIGH); 
      digitalWrite(pinR1, LOW); 
     }
     else if (2 == val)
     {
      digitalWrite(pinR0, LOW); 
      digitalWrite(pinR1, HIGH); 
     }
     else if (0 == val)
     {
        digitalWrite(pinR0, LOW); 
        digitalWrite(pinR0, LOW); 
     }
  }
  else
  {
      if (1 == val)
        digitalWrite(pinR0,HIGH);
      else
        digitalWrite(pinR0,LOW);
  }
}
void rightSpeed(int val)
{
    analogWrite(pinRSpeed, val); 
}

// LCD
int pinDIN = 12;  
int pinCS =  11;  
int pinCLK = 10;  
byte e[8]=     {0x7C,0x7C,0x60,0x7C,0x7C,0x60,0x7C,0x7C};  //E  
byte d[8]=     {0x78,0x7C,0x66,0x66,0x66,0x66,0x7C,0x78};  //D  
byte u[8]=     {0x66,0x66,0x66,0x66,0x66,0x66,0x7E,0x7E};  //U  
byte c[8]=     {0x7E,0x7E,0x60,0x60,0x60,0x60,0x7E,0x7E};  //C  
byte eight[8]= {0x7E,0x7E,0x66,0x7E,0x7E,0x66,0x7E,0x7E};  //8  
byte s[8]=     {0x7E,0x7C,0x60,0x7C,0x3E,0x06,0x3E,0x7E};  //S  
byte dot[8]=   {0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18};  //.  
byte o[8]=     {0x7E,0x7E,0x66,0x66,0x66,0x66,0x7E,0x7E};  //O  
byte m[8]=     {0xE7,0xFF,0xFF,0xDB,0xDB,0xDB,0xC3,0xC3};  //M
byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};//笑脸  
byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};//标准脸  

LedControl lc = LedControl(0, 0, 0, 4);
void lcdSet(int pDIN, int pCS, int pCLK)
{
  pinDIN = pDIN;
  pinCS = pCS;
  pinCLK = pCLK;

  lc = LedControl(pinDIN, pinCS, pinCLK, 4);

    // LCD
  lc.shutdown(0,false); //启动时，MAX72XX处于省电模式  
  lc.setIntensity(0,8); //将亮度设置为最大值  
  lc.clearDisplay(0);   //清除显示 
  
  printByte(neutral);
}
void printByte(byte character [])  
{  
  int i = 0;
  for(i=0;i<8;i++)  
  {  
    lc.setRow(0, i, character[i]);  
  }  
} 

// Light
int PinLight = 6;
void lightSet(int pin, bool isA)
{
  if (isA)
  {
    PinLight = A0 + pin;
  }
  else
  {
    PinLight = pin;
  }
  
  pinMode(PinLight, OUTPUT); 
}
void lightOn(bool isOn)
{
  if (isOn)
    digitalWrite(PinLight, HIGH);
  else
    digitalWrite(PinLight, LOW);
}

// colorLight
int cPinR = A2;
int cPinG = A3;
int cPinB = A4;
void cLightSet(int pinR, int pinG, int pinB, bool isA)
{
  if (isA)
  {
    cPinR = A0 + pinR;
    cPinG = A0 + pinG;
    cPinB = A0 + pinB;
  }
  else
  {
    cPinR = pinR;
    cPinG = pinG;
    cPinB = pinB;
  }

    pinMode(cPinR, OUTPUT);
    pinMode(cPinG, OUTPUT);
    pinMode(cPinB, OUTPUT);
}
void cLight(int r, int g, int b)
{
    digitalWrite(cPinR, r>0?LOW:HIGH); 
    digitalWrite(cPinG, g>0?LOW:HIGH);  
    digitalWrite(cPinB, b>0?LOW:HIGH);  
}

// trigger
int PinTrig = A0;
int PinEcho = A1;
void distInit(int pinTrig, int pinEcho)
{
    PinTrig = pinTrig;
    PinEcho = pinEcho;
    pinMode(PinTrig, OUTPUT); 
    pinMode(PinEcho, INPUT); 
}
int distTest()   // 量出前方距离 
{
  digitalWrite(PinTrig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(PinTrig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(20);
  digitalWrite(PinTrig, LOW);    // 持续给触发脚低电
  float fdistance = pulseIn(PinEcho, HIGH);  // 读取高电平时间(单位：微秒)
  fdistance= fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
                                 // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  return (int)fdistance;
}

// server
Servo servo;
Servo servo1;
Servo servo2;

// mp3
SoftwareSerial *mp3Serial = 0;

// IRremote
int IRemote_Recv = 0;
IRrecv *irrecv = 0;
int IRemove_Snd = 0;
IRsend irsend;

void setup() 
{
  cLightSet(2, 3, 4, true);
  
  // Serial
  Serial.begin(9600);
}

int pIGourp = 0;
char *pGroup = NULL;
String cmdGroups[6];

void OnCmdGroup(String cmdGroup)
{
  cmdGroups[0]="";
  cmdGroups[1]="";
  cmdGroups[2]="";
  cmdGroups[3]="";
  cmdGroups[4]="";
  cmdGroups[5]="";
  
  pIGourp = 0;
  pGroup=strtok((char*)cmdGroup.c_str(), ";");
  while(pGroup)
  {
      cmdGroups[pIGourp]=String(pGroup);
      pIGourp++;
      pGroup=strtok(NULL, ";");
  } 

  int i=0;
  for (; i<pIGourp; i++)
  {
    if (cmdGroups[i].length() > 0)
      OnCmd(cmdGroups[i]);
  }
}

int pI = 0;
char *p=NULL;
String cmds[5];

void OnCmd(String cmdStr)
{
  cmds[0] = "";
  cmds[1] = "";
  cmds[2] = "";
  cmds[3] = "";
  cmds[4] = "";

  String strs = cmdStr;
   
   pI = 0;
   p=strtok((char*)cmdStr.c_str()," ");
   while(p)
   {
      cmds[pI]=String(p);
      pI++;
      p=strtok(NULL," ");
   }   
   if (pI > 0)
   {  
      if (String("v") == cmds[0])
      {
        if (String("s") == cmds[1])
        {
          int pL0 = atoi(cmds[2].c_str());
          int pL1 = atoi(cmds[3].c_str());
          int sL = atoi(cmds[4].c_str());
          int pR0 = atoi(cmds[5].c_str());
          int pR1 = atoi(cmds[6].c_str());
          int sR = atoi(cmds[7].c_str());
          vehicleSet(pL0, pL1, sL, pR0, pR1, sR);
        }
        else if (String("ss") == cmds[1])
        {
          vehicleSetSimple();
        }
      }
      else if (String("m") == cmds[0])
      {
        if (String("l") == cmds[1])
        {
          if (String("g") == cmds[2])
          {
            leftGo(1);
          }
          else if (String("b") == cmds[2])
          {
            leftGo(2);
          }
          else if (String("s") == cmds[2])
          {
            leftGo(0);
          }
        }
        else if (String("r") == cmds[1])
        {
          if (String("g") == cmds[2])
          {
            rightGo(1);
          }
          else if (String("b") == cmds[2])
          {
            rightGo(2);
          }
          else if (String("s") == cmds[2])
          {
            rightGo(0);
          }
        }
      }
      else if (String("s") == cmds[0])
      {
        if (String("l") == cmds[1])
        {
          int spdVal = atoi(cmds[2].c_str());
          leftSpeed(spdVal);
        }
        else if (String("r") == cmds[1])
        {
          int spdVal = atoi(cmds[2].c_str());
          rightSpeed(spdVal);
        }
      }
      else if (String("lcdset") ==  cmds[0])
      {
        int din = atoi(cmds[1].c_str());
        int cs = atoi(cmds[2].c_str());
        int clk = atoi(cmds[3].c_str());
        lcdSet(din, cs, clk);
      }
      else if (String("lcd") == cmds[0])
      {
          if (String("normal") == cmds[1])
          {
            printByte(neutral);
          } 
          else if (String("smile") == cmds[1])
          {
             printByte(smile);
          }
          else if (String("e") == cmds[1])
          {
             printByte(e); 
          }
          else if (String("d") == cmds[1])
          {
             printByte(d); 
          }
          else if (String("u") == cmds[1])
          {
             printByte(u); 
          }
          else if (String("c") == cmds[1])
          {
             printByte(c); 
          }
          else if (String("s") == cmds[1])
          {
             printByte(s); 
          }
          else if (String("m") == cmds[1])
          {
             printByte(m); 
          }
      }
      else if (String("cl") == cmds[0])
      {
          if (String("s") == cmds[1])
          {
            if (String("d") == cmds[2])
            {
              int pR = atoi(cmds[3].c_str());
              int pG = atoi(cmds[4].c_str());
              int pB = atoi(cmds[5].c_str());
              cLightSet(pR, pG, pB, false);
            }
            else if (String("a") == cmds[2])
            {
              int pR = atoi(cmds[3].c_str());
              int pG = atoi(cmds[4].c_str());
              int pB = atoi(cmds[5].c_str());
              cLightSet(pR, pG, pB, true);
            }
          }
      }
      else if (String("clc") == cmds[0])
      {
          int r = atoi(cmds[1].c_str());
          int g = atoi(cmds[2].c_str());
          int b = atoi(cmds[3].c_str());
          cLight(r, g, b);
      }
      else if (String("lt") == cmds[0])
      {
          if (String("s") == cmds[1])
          {
            if (String("d") == cmds[2])
            {
              int pinVal = atoi(cmds[3].c_str());              
              lightSet(pinVal, false);
            }
            else if (String("a") == cmds[2])
            {
              int pinVal = atoi(cmds[3].c_str());   
              lightSet(pinVal, true);
            }
          }
          else if (String("on") == cmds[1])
          {
            lightOn(true);
          } 
          else if (String("off") == cmds[1])
          {
            lightOn(false);
          }
      }
      else if (String("pM") == cmds[0])
      { 
          // pinVal val
          int pinVal = 0;
          if (cmds[1].length() > 0)
           {
              char charVal = cmds[1][0];
              if ('A' == charVal)
              {
                String cntStr = cmds[1].substring(1);
                 pinVal = A0 + atoi(cmds[1].c_str());
              }
              else
              {
                 pinVal = atoi(cmds[1].c_str());
              }
           }
  
          // pinMode val
          int pinM = atoi(cmds[2].c_str());
  
          if (0 == pinM)
            pinMode(pinVal, INPUT);
          else if (1 == pinM)
            pinMode(pinVal, OUTPUT);
      }
      else if (String("dW") == cmds[0])
      {
        // pinVal val
        int pinVal = 0;
         if (!cmds[1].equals(""))
         {
              char charVal = cmds[1][0];
              if ('A' == charVal)
              {
               String cntStr = cmds[1].substring(1);
                pinVal = A0 + atoi(cntStr.c_str());
              }
              else
              {
               pinVal = atoi(cmds[1].c_str());
              }
         }

        // pinMode val
        int writeVal = atoi(cmds[2].c_str());

        if (0 == writeVal)
           digitalWrite(pinVal, LOW);
        else if (1 == writeVal)
           digitalWrite(pinVal, HIGH);
      }
      else if (String("aW") == cmds[0])
      {
        // pinVal val
        int pinVal = 0;
        if (!cmds[1].equals(""))
        {
            char charVal = cmds[1][0];
            if ('A' == charVal)
            {
              String cntStr = cmds[1].substring(1);
               pinVal = A0 + atoi(cntStr.c_str());
            }
            else
            {
               pinVal = atoi(cmds[1].c_str());
            }
        }

        // pinMode val
        int writeVal = atoi(cmds[2].c_str());

        analogWrite(pinVal, writeVal); 
      }
      else if (String("aR") == cmds[0])
      {
        // pinVal val
        int pinVal = 0;
        if (!cmds[1].equals(""))
        {
            char charVal = cmds[1][0];
            if ('A' == charVal)
            {
              String cntStr = cmds[1].substring(1);
              pinVal = A0 + atoi(cntStr.c_str());

              int analogVal = analogRead(pinVal);
              String sendStr = String("aR ") + String(analogVal);
              Serial.println(sendStr);
            } 
        }
      }
      else if (String("distSet") == cmds[0])
      {
        if (String("d") == cmds[1] )
        {
          int pinTrig = atoi(cmds[2].c_str());
          int pinEcho = atoi(cmds[3].c_str());      
          distInit(pinTrig, pinEcho);
        }
        else if (String("a") == cmds[1])
        {
          int pinTrig = atoi(cmds[2].c_str());
          int pinEcho = atoi(cmds[3].c_str());      
          distInit(A0+pinTrig, A0+pinEcho);
        }
      }
      else if (String("distTest") == cmds[0])
      {
          float dist = distTest();
          String sendStr = String("dist ") + String(dist);
          Serial.println(sendStr);
      }
      else if (String("svrA") == cmds[0])
      {
        int val = atoi(cmds[1].c_str());
        servo.attach(val);        
      }
      else if (String("svr1A") == cmds[0])
      {
        int val = atoi(cmds[1].c_str());
        servo1.attach(val);        
      }
      else if (String("svr2A") == cmds[0])
      {
        int val = atoi(cmds[1].c_str());
        servo2.attach(val);
      }
      else if (String("svr") == cmds[0])
      {
        int val = atoi(cmds[1].c_str());
        servo.write(val);        
      }
      else if (String("svr1") == cmds[0])
      {
        int val = atoi(cmds[1].c_str());
        servo1.write(val);        
      }
      else if (String("svr2") == cmds[0])
      {
        int val = atoi(cmds[1].c_str());
        servo2.write(val);        
      }
      else if (String("mp3") == cmds[0])
      {
        int pin0 = atoi(cmds[1].c_str());
        int pin1 = atoi(cmds[2].c_str());
        mp3Serial = new SoftwareSerial(pin0, pin1);
        mp3Serial->begin (9600);
        mp3_set_serial (*mp3Serial);
        delay(100);  //wait 1ms for mp3 module to set volume
        mp3_set_volume (25);
        delay(100);
        mp3_stop();
        delay(100);
        mp3_play (1);
        delay(100);
      }
      else if (String("mp3s") == cmds[0])
      {
        mp3_stop ();
        delay(100);
      }
      else if (String("mp3vo") == cmds[0])
      {
        int val = atoi(cmds[1].c_str());
        mp3_set_volume (val);
        delay(100);
      }
      else if (String("mp3i") == cmds[0])
      {
        int index = atoi(cmds[1].c_str());
        mp3_play (index);
        delay(100);
      }
      else if (String("IRR") == cmds[0])
      {
         int pin = atoi(cmds[1].c_str());
         irrecv = new IRrecv(pin);
         irrecv->enableIRIn();
      }
      else if (String("IRR_S") == cmds[0])
      {
          irsend.sendSony(0xa90, 12);
          delay(40);
      }
   }
}

String serStr;
decode_results irResultes;

void loop()
{   
  while(Serial.available())
  {
    char c = Serial.read();
    
    if ('\n' == c)
    {  
      if (serStr.length() > 0)
      {
           OnCmdGroup(serStr);
      }
      serStr = "";
    }
    else
    {
       serStr += c; 
    }
  }

  if (irrecv && irrecv->decode(&irResultes))
  {
    _IRProtocol(&irResultes);
  }
}

void _IRProtocol(decode_results *results) 
{
  switch(results->decode_type) {
   case NEC:
     break;
   case SONY:
     break;
   case RC5:
     break;
   case RC6:
     break;
   default:
     Serial.print("Unknown encoding");  
  }  
       
  //Serial.print(results->value, HEX);    // 红外线编码  
}
