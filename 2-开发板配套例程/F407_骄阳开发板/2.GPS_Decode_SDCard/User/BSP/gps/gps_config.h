#ifndef __GPS_CONFIG_H
#define	__GPS_CONFIG_H

#include "stm32f4xx.h"
#include "nmea/nmea.h"


/* 配置 */

//#define __GPS_DEBUG     //定义这个宏，在nmea解码时会输出调试信息

#define __GPS_LOG_FILE   1 //定义这个宏，对SD卡上的gpslog.txt文件进行解码；不定义的话使用串口接收GPS信息解码


/* GPS接口配置 使用不同的串口时，要修改对应的接口 */

#define GPS_DR_Base            (USART2_BASE+0x04)		  // 串口的数据寄存器地址


#define GPS_DATA_ADDR             GPS_DR_Base        //GPS使用的串口的数据寄存器地址
#define GPS_RBUFF_SIZE            512                   //串口接收缓冲区大小
#define HALF_GPS_RBUFF_SIZE       (GPS_RBUFF_SIZE/2)    //串口接收缓冲区一半  

/* 外设 */
/*******************************************************/
//GPS串口波特率
#define GPS_USART_BAUDRATE                    9600

#define GPS_USART                             USART2
#define GPS_USART_CLK                         RCC_APB1Periph_USART2
#define GPS_RCC_PeriphClockCmd_Fun            RCC_APB1PeriphClockCmd

#define GPS_USART_RX_GPIO_PORT                GPIOD
#define GPS_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define GPS_USART_RX_PIN                      GPIO_Pin_6
#define GPS_USART_RX_AF                       GPIO_AF_USART2
#define GPS_USART_RX_SOURCE                   GPIO_PinSource6

#define GPS_USART_TX_GPIO_PORT                GPIOD
#define GPS_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define GPS_USART_TX_PIN                      GPIO_Pin_5
#define GPS_USART_TX_AF                       GPIO_AF_USART2
#define GPS_USART_TX_SOURCE                   GPIO_PinSource5
/************************************************************/

//DMA
#define GPS_USART_DMA_STREAM            DMA1_Stream5
#define GPS_DMA_IRQn                     DMA1_Stream5_IRQn         //GPS中断源
#define GPS_USART_DMA_CLK                RCC_AHB1Periph_DMA1
#define GPS_USART_DMA_CHANNEL            DMA_Channel_4

/* 外设标志 */
#define GPS_DMA_IT_HT                DMA_IT_HTIF5
#define GPS_DMA_IT_TC                DMA_IT_TCIF5


/* 中断函数 */
#define GPS_DMA_IRQHANDLER           DMA1_Stream5_IRQHandler   //GPS使用的DMA中断服务函数


extern uint8_t gps_rbuff[GPS_RBUFF_SIZE];
extern __IO uint8_t GPS_TransferEnd ;
extern __IO uint8_t GPS_HalfTransferEnd;


void GPS_ProcessDMAIRQ(void);
void GPS_Config(void);

void trace(const char *str, int str_size);
void error(const char *str, int str_size);
void gps_info(const char *str, int str_size);
void GMTconvert(nmeaTIME *SourceTime, nmeaTIME *ConvertTime, uint8_t GMT,uint8_t AREA) ;




#endif 
