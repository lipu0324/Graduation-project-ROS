#ifndef SPG30_SENSOR_H
#define SPG30_SENSOR_H
#include <stdint.h>


/**********************************************************************************************************************/
#define I2C_WR 0 /* 写控制bit */
#define I2C_RD 1 /* 读控制bit */
#define SGP30_ADDR                     0x58
#define SGP30_Feature_Set              0x0020
#define SGP30_Init_air_quality         0x2003
#define SGP30_Measure_air_quality      0x2008
#define SGP30_Get_baseline             0x2015
#define SGP30_Set_baseline             0x201e
#define SGP30_Set_humidity             0x2061
#define SGP30_Measure_test             0x2032
#define SGP30_Get_feature_set_version  0x202f
#define SGP30_Measure_raw_signals      0x2050
#define SCL                            1
#define SDA                            0
#define I2C_SCL_1()                    digitalWrite(SCL, 1)
#define I2C_SCL_0()                    digitalWrite(SCL, 0)
#define I2C_SDA_1()                    digitalWrite(SDA, 1)
#define I2C_SDA_0()                    digitalWrite(SDA, 0)
#define I2C_SDA_READ()                 digitalRead(SDA)
#define  I2C_WR                        0
#define  I2C_RD                        1
/*********************************************************************************************************************/

#include <wiringPi.h>
#include <wiringPiI2C.h>


/*************************函数声明******************************/
    void SGP30_DATA_OUT_Cfg(void);
    void SGP30_DATA_IN_Cfg(void);
    void SGP30_I2C_Start(void);
    void SGP30_I2C_Stop(void);
    void SGP30_I2C_NAck(void);
    void SGP30_I2C_Ack(void);
    void SGP30_I2C_SendByte(u_int8_t data);
    uint8_t SGP30_i2C_ReadByte(uint8_t ack);
    uint8_t SGP30_I2C_WaitAck(void);
    uint8_t SGP30_I2C_CheckDevice(uint8_t _Address);
    uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address);


#endif