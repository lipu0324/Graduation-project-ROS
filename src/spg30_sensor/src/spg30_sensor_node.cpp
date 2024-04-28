#include <ros/ros.h>
#include <wiringPi.h>
#include "spg30_sensor.h"
#include <std_msgs/String.h>
#include <unistd.h>
#include <jsoncpp/json/json.h>
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "spg30_sensor_node");
    wiringPiSetup();
    //初始化IIC链接
    SGP30_Init();
    sleep(1);
    // if(SGP30_I2C_CheckDevice(SGP30_ADDR))
    // {
    //     ROS_INFO("SGP30 Sensor is not connected");
    //     //退出ROS节点
    //     return 0;
    // }
    // else
    // {
    //     ROS_ERROR("SGP30 Sensor is connected");
    // }
    //初始化SGP30
    //初始化消息发布器 
    ros::NodeHandle nh;
    ros::Publisher spg30_sensor_pub = nh.advertise<std_msgs::String>("spg30_sensor", 2);
    ros::Rate loop_rate(1);
    spg30_sensor_data data;
    uint32_t CO2_TVOC = 0;
    sleep(1);
    // while (ros::ok())
    // {
    //     uint32_t CO2_TVOC = SGP30_I2C_Read_CO2_TVOC(0x58);
    //     SGP30_DATA_CALC(&data);
    //     Json::Value json_data;
    //     json_data["CO2"] = data.CO2;
    //     json_data["TVOC"] = data.TVOC;
    //     Json::StreamWriterBuilder builder;
    //     builder["indentation"] = "";
    //     std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    //     std::ostringstream oss;
    //     writer->write(json_data, &oss);
    //     std_msgs::String msg;
    //     msg.data = oss.str();
    //     ROS_INFO("%s", msg.data.c_str());
    //     spg30_sensor_pub.publish(msg);
    //     loop_rate.sleep();
    // }
    while(ros::ok())
    {
        CO2_TVOC=SGP30_I2C_Read_CO2_TVOC(0x58);
        printf("CO2_TVOC:%d\n",CO2_TVOC);
        sleep(1);
    }

    return 0;
}



// /**********************手动iic编写***********************************/

// void SGP30_DATA_OUT_Cfg(void)
// {
//     pinMode(SDA, OUTPUT);
//     pinMode(SCL, OUTPUT);
// }

// void SGP30_DATA_IN_Cfg(void)
// {
//     pinMode(SDA, INPUT);
//     pinMode(SCL, OUTPUT);
// }

// void SGP30_I2C_Start(void) // 起始信号
// {
//     SGP30_DATA_OUT_Cfg();
//     I2C_SDA_1();
//     I2C_SCL_1();
//     usleep(4);
//     I2C_SDA_0();
//     usleep(4);
//     I2C_SCL_0();
//     usleep(4);
// }


// void SGP30_I2C_Stop(void) // 停止信号
// {
//     SGP30_DATA_OUT_Cfg();
//     I2C_SDA_0();
//     I2C_SCL_1();
//     usleep(4);
//     I2C_SDA_1();
// }

// void SGP30_I2C_NAck(void) // 应答信号
// {
//     SGP30_DATA_OUT_Cfg();
//     I2C_SDA_1();
//     usleep(4);
//     I2C_SCL_1();
//     usleep(4);
//     I2C_SCL_0();
//     usleep(4);
// }

// void SGP30_I2C_Ack(void) // 非应答信号
// {
//     SGP30_DATA_OUT_Cfg();
//     I2C_SDA_0();
//     usleep(4);
//     I2C_SCL_1();
//     usleep(4);
//     I2C_SCL_0();
//     usleep(4);
//     I2C_SDA_1();
// }

// void SGP30_I2C_SendByte(u_int8_t data) // 发送一个字节
// {
//     u_int8_t i;
//     SGP30_DATA_OUT_Cfg();
//     for (i = 0; i < 8; i++)
//     {
//         if (data & 0x80)
//         {
//             I2C_SDA_1();
//         }
//         else
//         {
//             I2C_SDA_0();
//         }
//         usleep(4);
//         I2C_SCL_1();
//         usleep(4);
//         I2C_SCL_0();
//         if (i == 7)
//         {
//             I2C_SDA_1(); // 释放总线
//         }
//         data <<= 1;
//         usleep(4);
//     }
// }

// uint8_t SGP30_I2C_ReadByte(uint8_t ack) // 接收一个字节
// {
//     u_int8_t i;
//     u_int8_t data = 0;
//     SGP30_DATA_IN_Cfg();
//     for (i = 0; i < 8; i++)
//     {
//         data <<= 1;
//         I2C_SCL_1();
//         usleep(4);
//         if (I2C_SDA_READ())
//         {
//             data++;
//         }
//         I2C_SCL_0();
//         usleep(4);
//     }
//     if (ack == 0)
//     {
//         SGP30_I2C_NAck();
//     }
//     else
//     {
//         SGP30_I2C_Ack();
//     }
//     return data;
// }

// /*
// ************************************************************************************************************
// *		函数名：SGP30_I2C_WaitAck
// *		功能说明：CPU产生一个时钟，并读取器件的ACK应答信号
// *		形参：无
// *		返回值：返回0表示正确应答，1表示无器件相应
// ***********************************************************************************************************************
// */
// uint8_t SGP30_I2C_WaitAck(void)
// {
//     uint8_t try_time = 100; // 等待时间
//     SGP30_DATA_IN_Cfg();
//     I2C_SDA_1();
//     usleep(4);
//     I2C_SCL_1();
//     usleep(4);
//     while (I2C_SDA_READ())
//     {
//         try_time--;
//         usleep(4);
//         if (try_time == 0)
//         {
//             I2C_SCL_0();
//             usleep(4);
//             return 1;
//         }
//     }
//     I2C_SCL_0();
//     usleep(4);
//     return 0;
// }

// uint8_t SGP30_I2C_CheckDevice(uint8_t _Address) // 检测设备是否存在
// {
//     uint8_t ucAck;
//     SGP30_I2C_Start();
//     SGP30_I2C_SendByte(_Address | I2C_WR);
//     ucAck = SGP30_I2C_WaitAck();
//     SGP30_I2C_Stop();
//     return ucAck;
// }

// uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address)
// {
//     uint32_t Read_CO2_TVOC=0;
//     uint8_t CRC_Check;
//     SGP30_I2C_Start(); // 启动I2C总线
//     SGP30_I2C_SendByte(_Address<<1 | I2C_WR); // 发送写命令
//     SGP30_I2C_WaitAck(); // 等待应答
//     SGP30_I2C_SendByte(0x20); // 发送读地址
//     SGP30_I2C_WaitAck(); // 等待应答
//     SGP30_I2C_SendByte(0x08); // 发送读地址 
//     SGP30_I2C_WaitAck(); // 等待应答
//     SGP30_I2C_Stop(); // 发送停止信号
//     sleep(1);
//     SGP30_I2C_Start(); // 启动I2C总线
//     SGP30_I2C_SendByte(_Address<<1 | I2C_RD); // 读取设备的特征集
//     SGP30_I2C_WaitAck(); // 等待应答
//     Read_CO2_TVOC |= (uint16_t)(SGP30_I2C_ReadByte(1)<<8);
//     Read_CO2_TVOC |= (uint16_t)(SGP30_I2C_ReadByte(1));
//     CRC_Check=SGP30_I2C_ReadByte(1);
//     Read_CO2_TVOC |= (uint32_t)(SGP30_I2C_ReadByte(1)<<24);
//     Read_CO2_TVOC |= (uint32_t)(SGP30_I2C_ReadByte(1)<<16);
//     CRC_Check=SGP30_I2C_ReadByte(0);
//     SGP30_I2C_Stop(); // 停止I2C总线
//     return Read_CO2_TVOC;

// }



// void SGP30_Init(void)
// {
//     SGP30_I2C_Start(); // 启动I2C总线
//     SGP30_I2C_SendByte(0x58<<1 | I2C_WR); // 发送写命令
//     SGP30_I2C_WaitAck(); // 等待应答
//     SGP30_I2C_SendByte(0x20); // 发送读地址
//     SGP30_I2C_WaitAck(); // 等待应答
//     SGP30_I2C_SendByte(0x03); // 发送读地址
//     SGP30_I2C_WaitAck(); // 等待应答
//     SGP30_I2C_Stop(); // 停止I2C总线
//     sleep(1);
// }


void SGP30_DATA_CALC(spg30_sensor_data *data)
{
    data->CO2 = (uint16_t)(data->CO2 >> 8) | (uint16_t)(data->CO2 << 8);
    data->TVOC = (uint16_t)(data->TVOC >> 8) | (uint16_t)(data->TVOC << 8);
}



//************************************旧代码如上************************

/*
*********************************************************************************************************
*		函数名：			SGP30_I2C_Start
*		功能说明：		I2C开始指令
*		形参：				无
*		返回值：			无
*********************************************************************************************************
*/
void SGP30_I2C_Start(void)
{
	
		SGP30_DATA_OUT_Cfg();
		//当SCL高电平时，SDA出现一个下跳沿表示I2C总线信号开始
		I2C_SDA_1();
		I2C_SCL_1();
		usleep(4);
		I2C_SDA_0();
		usleep(4);
		I2C_SCL_0();
		usleep(4);

}

/*
*********************************************************************************************************
*		函数名：			SGP30_I2C_Stop
*		功能说明：		I2C停止指令
*		形参：				无
*		返回值：			无
*********************************************************************************************************
*/
void SGP30_I2C_Stop(void)
{
		SGP30_DATA_OUT_Cfg();
		//当SCL高电平时，SDA出现一个上升沿
		I2C_SDA_0();
		I2C_SCL_1();
		usleep(4);
		I2C_SDA_1();
	
}	

/*
*********************************************************************************************************
*		函数名：SGP30_I2C_SendByte
*		功能说明：CPU向I2C总线设备发送8bit数据
*		形参：_ucbyte ：等待发送的字节
*		返回值：无
**********************************************************************************************************
*/

void SGP30_I2C_SendByte(uint8_t _ucByte)
{
		uint8_t i;
		SGP30_DATA_OUT_Cfg();
		/*先发送字节的高位bit7*/
		for(i =0;i<8;i++)
		{
				if(_ucByte & 0x80)				//每次判断最高位
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
				if(i==7)
				{
						I2C_SDA_1();	//释放总线
				}
				_ucByte <<= 1;		//左移一个bit
				usleep(4);
				
		}

}

/*
************************************************************************************************************
*		函数名：SGP30_I2C_ReadByte
*		功能说明：CPU从I2C总线设备读取8bit数据
*		形参：ack 是否应答
*		返回值：读到的数据
************************************************************************************************************
*/
uint8_t SGP30_I2C_ReadByte(uint8_t ack)
{
		uint8_t i;
		uint8_t value;
		SGP30_DATA_IN_Cfg();
		/*	读到第1个bit为数据的bit7 */
		value = 0;
		
		for(i=0;i<8;i++)
		{
				value <<= 1;
				I2C_SCL_1();
				usleep(4);
				if(I2C_SDA_READ())
				{
						value++;
				}
				I2C_SCL_0();
				usleep(4);
		}
		if(ack == 0)
			SGP30_I2C_NAck();
		else 
			SGP30_I2C_Ack();

		return value;
		

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
		uint8_t try_time = 100;							//连接超时次数
		SGP30_DATA_IN_Cfg();
		I2C_SDA_1();											//CPU释放SDA总线
		usleep(4);
		I2C_SCL_1();											//CPU驱动SCL = 1,此时器件会返回ACK应答
		usleep(4);		
		while(I2C_SDA_READ())							//等待SGP3030应答
		{
				try_time--;
				usleep(4);
				if(try_time==0)									//超时，无响应
				{
						I2C_SCL_0();
						usleep(4);
						return 1;
				
				}
		}
		I2C_SCL_0();
		usleep(4);
		return 0;
}



/*
****************************************************************************************************************
*		函数名：SGP30_I2C_Ack
*		功能说明：CPU产生一个ACK信号
*		形参：无
*		返回值：无
****************************************************************************************************************
*/
void SGP30_I2C_Ack(void)
{
		SGP30_DATA_OUT_Cfg();
		I2C_SDA_0();			//CPU驱动SDA = 0
		usleep(4);
		I2C_SCL_1();			//CPU产生一个时钟
		usleep(4);
		I2C_SCL_0();
		usleep(4);
		I2C_SDA_1();			//CPU释放SDA总线
}



/*
*****************************************************************************************************************
*		函数名：SGP30_I2C_NAck
*		功能说明：CPU产生1个NACK信号
*		形参：无
*		返回值：无
*****************************************************************************************************************
*/
void SGP30_I2C_NAck(void)
{
		SGP30_DATA_OUT_Cfg();
		I2C_SDA_1();		//CPU驱动SDA=1
		usleep(4);
		I2C_SCL_1();		//CPU产生一个时钟
		usleep(4);
		I2C_SCL_0();
		usleep(4);	
}


/*
*****************************************************************************************************************
*		函数名：SGP30_I2C_GPIO_Config(void)
*		功能说明：配置I2C总线GPIO，采用模拟IO的方式实现
*		形参：无
*		返回值：无
*******************************************************************************************************************
*/
void SGP30_I2C_GPIO_Config(void)
{
		//库函数初始化通俗易懂
    pinMode(IIC_SDA_PIN, OUTPUT);
    pinMode(IIC_SCL_PIN, OUTPUT);
}

/*********************************************************************************************************
** 函数名称: SGP_DAT_OUT_Cfg
** 功能描述: 配置SHT的DATA引脚输出
** 输　  入: 无
** 输　  出: 无
********************************************************************************************************/
void SGP30_DATA_OUT_Cfg(void)
{
    pinMode(IIC_SDA_PIN, OUTPUT);
    pinMode(IIC_SCL_PIN, OUTPUT);			
}
/*********************************************************************************************************
** 函数名称: SGP30_DAT_IN_Cfg
** 功能描述: 配置SHT的DATA引脚输入
** 输　  入: 无
** 输　  出: 无
********************************************************************************************************/
void SGP30_DATA_IN_Cfg(void)
{
    pinMode(IIC_SDA_PIN, INPUT);
    pinMode(IIC_SCL_PIN, OUTPUT);			
}

/*
*****************************************************************************************************************
*		函数名：SGP30_I2C_CheckDevice
*		功能说明：检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断设备是否存在
*		形参：_Address:设备的I2C总线地址
*		返回值：返回值0表示正确，返回1表示未探测到
*******************************************************************************************************************
*/
uint8_t SGP30_I2C_CheckDevice(uint8_t _Address)
{
		uint8_t ucAck;
		SGP30_I2C_GPIO_Config();				//配置GPIO
		SGP30_I2C_Start();							//发送启动信号
	
		/* 发送设备地址+读写控制bit(0 = w, 1 = r)bit7 先传*/
		SGP30_I2C_SendByte(_Address|I2C_WR);
		ucAck = SGP30_I2C_WaitAck();		//检测设备的ACK应答
		SGP30_I2C_Stop();								//发送停止信号
		return ucAck;
}

/*
*****************************************************************************************************************
*		函数名：SGP30_I2C_Read_CO2_TVOC
*		功能说明：读取数据
*		形参：_Address:设备的I2C总线地址
*		返回值：返回值0表示正确，返回1表示未探测到
*******************************************************************************************************************
*/
uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address)
{
		uint32_t Read_CO2_TVOC=0;
		uint8_t  CRC_Check;
		SGP30_I2C_Start();							//发送启动信号	
		/* 发送设备地址+读写控制bit(0 = w, 1 = r)bit7 先传*/
		SGP30_I2C_SendByte(_Address<<1|I2C_WR);
		SGP30_I2C_WaitAck();		//检测设备的ACK应答
		SGP30_I2C_SendByte(0x20);
		SGP30_I2C_WaitAck();		//检测设备的ACK应答
		SGP30_I2C_SendByte(0x08);
		SGP30_I2C_WaitAck();		//检测设备的ACK应答
		SGP30_I2C_Stop();								//发送停止信号	
		sleep(1);
		SGP30_I2C_Start();							//发送启动信号
		SGP30_I2C_SendByte(_Address<<1|I2C_RD);   //读取设备的特征集	
		SGP30_I2C_WaitAck();		//检测设备的ACK应答
		Read_CO2_TVOC |= (uint16_t)(SGP30_I2C_ReadByte(1)<<8);
		Read_CO2_TVOC |= (uint16_t)(SGP30_I2C_ReadByte(1));
		CRC_Check = SGP30_I2C_ReadByte(1);
		Read_CO2_TVOC |= (uint32_t)(SGP30_I2C_ReadByte(1)<<24);
		Read_CO2_TVOC |= (uint32_t)(SGP30_I2C_ReadByte(1)<<16);
		CRC_Check = SGP30_I2C_ReadByte(0);
		SGP30_I2C_Stop();								//发送停止信号
		return Read_CO2_TVOC;
}

/*
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
*/
//CRC校验-8位
static uint8_t CRC_Check(uint8_t *check_data,uint8_t num,uint8_t check_crc)
{
		uint8_t bit;										//bit mask
		uint8_t crc = 0xFF;							//caculated checksum
		uint8_t byteCtr;								//byte counter
	
	
		//calculates 8Bit checksum with given polynomial x8+x5+x4+1
		for(byteCtr = 0; byteCtr < num; byteCtr++)
		{
				crc ^= (*(check_data+byteCtr));
				//CRC校验，最高为是1就^0x31
				for(bit = 8; bit > 0;--bit)
				{
						if(crc & 0x80)
							crc = (crc << 1)^0x31;
						else
							crc = (crc << 1);
				
				}
		}
		
		if(crc == check_crc)
			return 1;
		else
			return 0;
	
}


/*
			SGP30   初始化

*/
void  SGP30_Init(void)
{
		SGP30_I2C_GPIO_Config();				//配置GPIO
		SGP30_I2C_Start();							//发送启动信号
		/* 发送设备地址+读写控制bit(0 = w, 1 = r)bit7 先传*/
		SGP30_I2C_SendByte(SGP30_ADDR<<1);
		SGP30_I2C_WaitAck();		//检测设备的ACK应答
		SGP30_I2C_SendByte(0x20);
		SGP30_I2C_WaitAck();		//检测设备的ACK应答
		SGP30_I2C_SendByte(0x03);
		SGP30_I2C_WaitAck();		//检测设备的ACK应答	
		SGP30_I2C_Stop();								//发送停止信号		
		sleep(1);

	
}
