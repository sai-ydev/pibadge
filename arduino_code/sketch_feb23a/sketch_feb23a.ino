#include <Wire.h>
#include "IS31FL3737RES.h"
#define ADDR 0x50
#define SDB 18
#define SDA 0
#define SCL 1

uint8_t data[64];
uint8_t G_Demo_NO, Key_Bit;
uint8_t IS3737_Pwm[192];

void I2C_WriteByte(uint8_t Dev_Add, uint8_t Reg_Add, uint8_t Reg_Dat);
uint8_t I2C_BufferWrite(uint8_t* pBuffer, int length, int WriteAddress, int DeviceAddress);
void IS31FL3737_Init(void);
void Play_IS31FL3737_Demo_mode(void);
void IS31FL3737_PWM_ALL_OFF(void);

void setup() {
  // put your setup code here, to run once:
  pinMode(SDB, OUTPUT);
  digitalWrite(SDB, HIGH);
  Wire.setSDA(SDA);
  Wire.setSCL(SCL);
  Wire.setClock(400000);
  Wire.begin();
  Wire.begin();
  Serial.begin(115200);
  
  
  
  
  
  G_Demo_NO = 3;
  IS31FL3737_Init();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Play_IS31FL3737_Demo_mode();
  
  
  
}

void I2C_WriteByte(uint8_t Dev_Add, uint8_t Reg_Add, uint8_t Reg_Dat)
{
  Wire.beginTransmission(Dev_Add);
  Wire.write(Reg_Add); // sends regaddress
  Wire.write(Reg_Dat); // sends regaddress
  Wire.endTransmission(); // stop transmitting
}

void IS31FL3737_Init(void)
{
  uint8_t i;
  I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
  I2C_WriteByte(ADDR, 0xFD, 0x00); //write page 0
  for (i = 0; i < 24; i++) {
    I2C_WriteByte(ADDR, i, 0xff); //open all led
  }


  I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
  I2C_WriteByte(ADDR, 0xFD, 0x03); //write page 3
  I2C_WriteByte(ADDR, 0x00, 0x01); //normal operation
  I2C_WriteByte(ADDR, 0x01, 0xFF); //set  global current
}

void Play_IS31FL3737_Demo_mode(void)
{
  uint16_t i, g_money_NO = 0, g_hudie_NO = 0, g_shadow_NO = 0;
  while ((0x01 == G_Demo_NO)) //play fengsan
  {
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x00); //write page 0
    for (i = 0; i < 24; i++) {
      I2C_WriteByte(ADDR, i, 0xff); //open all  led
    }

    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x01); //write page 1
    for (i = 0; i < 192; i++) {
      I2C_WriteByte(ADDR, i, (uint8_t)fengsan[g_shadow_NO][i]);
    }

    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x03); //write page 3

    I2C_WriteByte(ADDR, 0x00, 0x01); //normal operation

    I2C_WriteByte(ADDR, 0x01, 0xFF); //set current
    g_shadow_NO++;
    delayMicroseconds(1500);//20ms
    if (g_shadow_NO == 301)
    {
      g_shadow_NO = 0;
    }
  }
  while ((0x02 == G_Demo_NO)) //play money
  {
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x00); //write page 0
    for (i = 0; i < 24; i++) {
      I2C_WriteByte(ADDR, i, 0xff); //open all led
    }

    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x03); //write page 3

    I2C_WriteByte(ADDR, 0x00, 0x01); //normal operation

    I2C_WriteByte(ADDR, 0x01, 0xFF); //set current
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x01); //write page 1
    for (i = 0; i < 192; i++) {
      I2C_WriteByte(ADDR, i, (uint8_t)money[g_money_NO][i]);
    }
    g_money_NO++;
    delay(12);//20ms
    if (g_money_NO == 8)
    {
      g_money_NO = 0;
    }
  }
  while ((0x03 == G_Demo_NO)) //play hudie
  {
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x00); //write page 0
    for (i = 0; i < 24; i++) {
      I2C_WriteByte(ADDR, i, 0xff); //open all led
    }
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x01); //write page 1
    for (i = 0; i < 192; i++) {
      I2C_WriteByte(ADDR, i, (uint8_t)hudie[g_hudie_NO][i]);
    }

    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x03); //write page 3

    I2C_WriteByte(ADDR, 0x00, 0x01); //normal operation

    I2C_WriteByte(ADDR, 0x01, 0xFF); //set current
    g_hudie_NO++;
    delay(20);//20ms
    if (g_hudie_NO == 8)
    {
      g_hudie_NO = 0;
    }
  }
  while ((0x04 == G_Demo_NO)) //play all led on
  {
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x00); //write page 0
    for (i = 0; i < 24; i+=3) {
      I2C_WriteByte(ADDR, i, 0xff); //open all led
    }
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x01); //write page 1
    for (i = 0; i < 192; i+=12) {
      I2C_WriteByte(ADDR, i, (uint8_t)all_pwm_on_IS31FL3737[i]);
    }
    
    I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
    I2C_WriteByte(ADDR, 0xFD, 0x03); //write page 3

    I2C_WriteByte(ADDR, 0x00, 0x01); //normal operation
    I2C_WriteByte(ADDR, 0x01, 0xFF); //set current
  }
  if (0 == G_Demo_NO)
  {
    IS31FL3737_PWM_ALL_OFF();
  }
}

void IS31FL3737_PWM_ALL_OFF(void)
{
  I2C_WriteByte(ADDR, 0xFE, 0xc5); //unlock FDh
  I2C_WriteByte(ADDR, 0xFD, 0x01); //write page 1
  for (int i = 0; i < 192; i++) {
    I2C_WriteByte(ADDR, i, (uint8_t)all_pwm_off_IS31FL3737[i]);
  }

}
