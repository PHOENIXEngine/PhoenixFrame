// PhoenixFrame

#include <LedControl.h>

// Move
int pinL0=4;
int pinL1=5;
int pinR0=7;
int pinR1=8;
int pinLSpeed = 3;
int pinRSpeed = 9;

void leftGo(int val)
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

void leftSpeed(int val)
{
    analogWrite(pinLSpeed, val); 
}

void rightGo(int val)
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

void rightSpeed(int val)
{
    analogWrite(pinRSpeed, val); 
}

// LCD
int DIN = 12;  
int CS =  11;  
int CLK = 10;  
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

LedControl lc=LedControl(DIN,CLK,CS,4);
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
void lightOn(bool isOn)
{
  if (isOn)
    digitalWrite(PinLight, HIGH);
  else
    digitalWrite(PinLight, LOW);
}

void setup() 
{
  // Moto
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

  // LCD
  lc.shutdown(0,false); //启动时，MAX72XX处于省电模式  
  lc.setIntensity(0,8); //将亮度设置为最大值  
  lc.clearDisplay(0);   //清除显示 
  
  printByte(neutral);

  // Light
  pinMode(PinLight, OUTPUT); 

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
      if (String("m") == cmds[0])
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
      else if (String("fe") == cmds[0])
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
      else if (String("lt") == cmds[0])
      {
          if (String("on") == cmds[1])
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
   }
}

String serStr;

void loop()
{ 
  while(Serial.available())
  {
    char c = Serial.read();
    
    if ('\n' == c)
    { 
      Serial.println(serStr);
      
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
}