#include <i2clcd.h>
#include <Wire.h>                 //I2C通信のライブラリ 
 
#define TEMP_ADRS 0x48           //温度センサのアドレス
#define LCD_ADRS  0x3E           //LSDモニターのアドレス

i2clcd lcd(LCD_ADRS,8,2);
 
void setup(void) {               // 初期化
  Serial.begin(9600);            //シリアル通信開始
  Wire.begin();                  //I2C通信開始
  lcd.init_lcd();
}
 
void loop(void) {
  lcd.lcdclear();
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
  lcd.i2cprint(String(fVal));
  delay(2000);                         //2秒待つ
}
