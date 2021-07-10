#include <Wire.h>                 //I2C通信のライブラリ  
 
#define TEMP_ADRS 0x48           //温度センサのアドレス
#define LCD_ADRS  0x3E           //LSDモニターのアドレス
 
void setup(void) {               // 初期化
  Serial.begin(9600);            //シリアル通信開始
  Wire.begin();                  //I2C通信開始
  init_LCD();
}
 
void loop(void) {
  uint16_t uiVal; //2バイト(16ビット)の領域,uint16_t:16ビットの非負整数
  float fVal;
  int iVal;
  
  Wire.requestFrom(TEMP_ADRS, 2);   //2バイト要求
 
  uiVal = (uint8_t)Wire.read() << 8;   // 1バイト読み出しで上位にシフト
  uiVal |= Wire.read();                 // 1バイト読み出して下位にセット
 
  uiVal >>= 3;                          // シフトで13bit化
 
  if (uiVal & 0x1000) {                // 13ビットで符号判定
    iVal = uiVal - 0x2000;             // マイナスの時 (10進数で8192)
  }
  else {
    iVal = uiVal;                      //プラスの時
  }
 
 
  fVal = (float)iVal / 16.0;           // 温度換算(摂氏)
  Serial.println(fVal, 3);             // シリアル送信　小数点以下3桁表示
  String temp = String(fVal);
  //Serial.print(temp);
  char Buf[8];
  temp.toCharArray(Buf,8);//fVal;
  //writeData(fVal);
  for(int i=0;i<5;i++)
  {
    writeData(temp[i]);
  }
  writeCommand(0x40+0x80);
  delay(1000);                         //1秒待つ
}

void writeData(byte t_data)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x40);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(1);
}

void writeCommand(byte t_command)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
  delay(10);
}

void init_LCD()
{
  delay(100);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x39);
  delay(20);
  writeCommand(0x14); 
  delay(20);
  writeCommand(0x73);
  delay(20);
  //writeCommand(0x52);  // 5V動作用
  writeCommand(0x56);  // 3V動作用
  delay(20);
  writeCommand(0x6C);
  delay(20);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x01);
  delay(20);
  writeCommand(0x0C);
  delay(20);
}
