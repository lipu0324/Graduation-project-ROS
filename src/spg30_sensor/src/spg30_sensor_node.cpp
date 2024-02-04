#include <ros/ros.h>
#include <wiringPi.h>
#include "spg30_sensor.h"
#include <wiringPiI2C.h>
#include <std_msgs/String.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "spg30_sensor_node");
    
    return 0;
}



/**********************手动iic编写***********************************/

void SGP30_DATA_OUT_Cfg(void)
{
    pinMode(SDA, OUTPUT);
    pinMode(SCL, OUTPUT);
}

void SGP30_DATA_IN_Cfg(void)
{
    pinMode(SDA, INPUT);
    pinMode(SCL, OUTPUT);
}

void SGP30_I2C_Start(void) // 起始信号
{
    SGP30_DATA_OUT_Cfg();
    I2C_SDA_1();
    I2C_SCL_1();
    usleep(4);
    I2C_SDA_0();
    usleep(4);
    I2C_SCL_0();
    usleep(4);
}


void SGP30_I2C_Stop(void) // 停止信号
{
    SGP30_DATA_OUT_Cfg();
    I2C_SDA_0();
    I2C_SCL_1();
    usleep(4);
    I2C_SDA_1();
}

void SGP30_I2C_NAck(void) // 应答信号
{
    SGP30_DATA_OUT_Cfg();
    I2C_SDA_1();
    usleep(4);
    I2C_SCL_1();
    usleep(4);
    I2C_SCL_0();
    usleep(4);
}

void SGP30_I2C_Ack(void) // 非应答信号
{
    SGP30_DATA_OUT_Cfg();
    I2C_SDA_0();
    usleep(4);
    I2C_SCL_1();
    usleep(4);
    I2C_SCL_0();
    usleep(4);
    I2C_SDA_1();
}

void SGP30_i2C_SendByte(u_int8_t data) // 发送一个字节
{
    u_int8_t i;
    SGP30_DATA_OUT_Cfg();
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            I2C_SDA_1();
        }
        else
        {
            I2C_SDA_0();
        }
        usleep(4);
        I2C_SCL_1();
        usleep(4);
        I2C_SCL_0();
        if (i == 7)
        {
            I2C_SDA_1(); // 释放总线
        }
        data <<= 1;
        usleep(4);
    }
}

uint8_t SGP30_I2C_ReadByte(uint8_t ack) // 接收一个字节
{
    u_int8_t i;
    u_int8_t data = 0;
    SGP30_DATA_IN_Cfg();
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        I2C_SCL_1();
        usleep(4);
        if (I2C_SDA_READ())
        {
            data++;
        }
        I2C_SCL_0();
        usleep(4);
    }
    if (ack == 0)
    {
        SGP30_I2C_NAck();
    }
    else
    {
        SGP30_I2C_Ack();
    }
    return data;
}

/*
************************************************************************************************************
*		函数名：SGP30_I2C_WaitAck
*		功能说明：CPU产生一个时钟，并读取器件的ACK应答信号
*		形参：无
*		返回值：返回0表示正确应答，1表示无器件相应
***********************************************************************************************************************
*/
uint8_t SGP30_I2C_WaitAck(void)
{
    uint8_t try_time = 100; // 等待时间
    SGP30_DATA_IN_Cfg();
    I2C_SDA_1();
    usleep(4);
    I2C_SCL_1();
    usleep(4);
    while (I2C_SDA_READ())
    {
        try_time--;
        if (try_time == 0)
        {
            SGP30_I2C_Stop();
            return 1;
        }
    }
    I2C_SCL_0();
    usleep(4);
    return 0;
}

uint8_t SGP30_I2C_CheckDevice(uint8_t _Address) // 检测设备是否存在
{
    uint8_t ucAck;
    SGP30_I2C_Start();
    SGP30_i2C_SendByte(_Address | I2C_WR);
    ucAck = SGP30_I2C_WaitAck();
    SGP30_I2C_Stop();
    return ucAck;
}

uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address)
{
    uint32_t Read_CO2_TVOC=0;
    uint8_t CRC_Check;
    SGP30_I2C_Start(); // 启动I2C总线
    SGP30_i2C_SendByte(_Address<<1 | I2C_WR); // 发送写命令
    SGP30_I2C_WaitAck(); // 等待应答
    SGP30_i2C_SendByte(0x20); // 发送读地址
    SGP30_I2C_WaitAck(); // 等待应答
    SGP30_i2C_SendByte(0x08); // 发送读地址
    SGP30_I2C_WaitAck(); // 等待应答
    SGP30_I2C_Stop(); // 启动I2C总线
    sleep(1);
    SGP30_I2C_Start(); // 启动I2C总线
    SGP30_i2C_SendByte(_Address<<1 | I2C_RD); // 读取设备的特征集
    SGP30_I2C_WaitAck(); // 等待应答
    Read_CO2_TVOC |= (uint16_t)(SGP30_I2C_ReadByte(1)<<8);
    Read_CO2_TVOC |= (uint16_t)SGP30_I2C_ReadByte(1);
    CRC_Check=SGP30_I2C_ReadByte(1);
    Read_CO2_TVOC |= (uint32_t)(SGP30_I2C_ReadByte(1)<<24);
    Read_CO2_TVOC |= (uint32_t)(SGP30_I2C_ReadByte(1)<<16);
    CRC_Check=SGP30_I2C_ReadByte(0);
    SGP30_I2C_Stop(); // 停止I2C总线
    return Read_CO2_TVOC;

}
