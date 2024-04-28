// #ifndef SPG30_SENSOR_H
// #define SPG30_SENSOR_H
// #include <stdint.h>

// #include <wiringPi.h>
// #include <wiringPiI2C.h>

// /**********************************************************************************************************************/
// #define I2C_WR 0 /* 写控制bit */
// #define I2C_RD 1 /* 读控制bit */
// #define SGP30_ADDR                     0x58
// #define SGP30_Feature_Set              0x0020
// #define SGP30_Init_air_quality         0x2003
// #define SGP30_Measure_air_quality      0x2008
// #define SGP30_Get_baseline             0x2015
// #define SGP30_Set_baseline             0x201e
// #define SGP30_Set_humidity             0x2061
// #define SGP30_Measure_test             0x2032
// #define SGP30_Get_feature_set_version  0x202f
// #define SGP30_Measure_raw_signals      0x2050
// #define SCL                            1
// #define SDA                            0
// #define I2C_SCL_1()                    digitalWrite(SCL, 1)
// #define I2C_SCL_0()                    digitalWrite(SCL, 0)
// #define I2C_SDA_1()                    digitalWrite(SDA, 1)
// #define I2C_SDA_0()                    digitalWrite(SDA, 0)
// #define I2C_SDA_READ()                 digitalRead(SDA)
// #define  I2C_WR                        0
// #define  I2C_RD                        1

// /**************************结构体********************************/
    
    typedef struct spg30_sensor_data
    {
        uint32_t CO2;
        uint32_t TVOC;
    }spg30_sensor_data;

// /*************************函数声明******************************/
//     void SGP30_DATA_OUT_Cfg(void);
//     void SGP30_DATA_IN_Cfg(void);
//     void SGP30_I2C_Start(void);
//     void SGP30_I2C_Stop(void);
//     void SGP30_I2C_NAck(void);
//     void SGP30_I2C_Ack(void);
//     void SGP30_I2C_SendByte(u_int8_t data);
//     void SGP30_Init(void);
//     void SGP30_DATA_CALC(spg30_sensor_data *data);
//     uint8_t SGP30_i2C_ReadByte(uint8_t ack);
//     uint8_t SGP30_I2C_WaitAck(void);
//     uint8_t SGP30_I2C_CheckDevice(uint8_t _Address);
//     uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address);

// #endif

//------------------------------旧版本代码在上方--------------------------
#ifndef _SGP30_H
#define _SGP30_H
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

//I2C部分

#define IIC_CLOCK           RCC_AHBPeriph_GPIOA
#define IIC_SCL_PIN         1
#define IIC_SDA_PIN         0
/* 定义I2C总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */
#define I2C_SCL_1()     digitalWrite(IIC_SCL_PIN, 1)
#define I2C_SCL_0()     digitalWrite(IIC_SCL_PIN, 0)
#define I2C_SDA_1()		digitalWrite(IIC_SDA_PIN, 1)
#define I2C_SDA_0()     digitalWrite(IIC_SDA_PIN, 0)
#define I2C_SDA_READ()  digitalRead(IIC_SDA_PIN)

#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */

//SGP读取部分
#define SGP30_ADDR      								0x58
#define SGP30_Feature_Set   						0x0020
#define SGP30_Init_air_quality 					0x2003
#define SGP30_Measure_air_quality   		0x2008
#define SGP30_Get_baseline 							0x2015
#define SGP30_Set_baseline 							0x201e
#define SGP30_Set_humidity							0x2061
#define SGP30_Measure_test 							0x2032
#define SGP30_Get_feature_set_version		0x202f
#define SGP30_Measure_raw_signals				0x2050


void SGP30_I2C_Start(void);
void SGP30_I2C_SendByte(uint8_t _ucByte);
uint8_t SGP30_I2C_ReadByte(uint8_t ack);
uint8_t SGP30_I2C_WaitAck(void);
void SGP30_I2C_Ack(void);
void SGP30_I2C_NAck(void);
void SGP30_I2C_GPIO_Config(void);
uint8_t SGP30_I2C_CheckDevice(uint8_t _Address);
static uint8_t CRC_Check(uint8_t *check_data,uint8_t num,uint8_t check_crc);
uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address);
void SGP30_DATA_IN_Cfg(void);
void SGP30_DATA_OUT_Cfg(void);
void  SGP30_Init(void);
#endif