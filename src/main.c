/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : ´®¿Ú1ÊÕ·¢ÑÝÊ¾
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH57x_common.h"

uint8_t TxBuff[] = "This is a tx exam\r\n";
uint8_t RxBuff[100];
uint8_t trigB;

/*********************************************************************
 * @fn      main
 *
 * @brief   Ö÷º¯Êý
 *
 * @return  none
 */
int main()
{
    uint8_t len;

    SetSysClock(CLK_SOURCE_PLL_60MHz);

    /* ÅäÖÃ´®¿Ú1£ºÏÈÅäÖÃIO¿ÚÄ£Ê½£¬ÔÙÅäÖÃ´®¿Ú */
    GPIOA_SetBits(GPIO_Pin_9);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);      // RXD-ÅäÖÃÉÏÀ­ÊäÈë
    GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA); // TXD-ÅäÖÃÍÆÍìÊä³ö£¬×¢ÒâÏÈÈÃIO¿ÚÊä³ö¸ßµçÆ½
    UART1_DefInit();

#if 0 // ²âÊÔ´®¿Ú·¢ËÍ×Ö·û´®
    UART1_SendString(TxBuff, sizeof(TxBuff));

#endif

#if 1 // ²éÑ¯·½Ê½£º½ÓÊÕÊý¾Ýºó·¢ËÍ³öÈ¥
    while(1)
    {
        len = UART1_RecvString(RxBuff);
        if(len)
        {
            UART1_SendString(RxBuff, len);
        }
    }

#endif

#if 1 // ÖÐ¶Ï·½Ê½£º½ÓÊÕÊý¾Ýºó·¢ËÍ³öÈ¥
    UART1_ByteTrigCfg(UART_7BYTE_TRIG);
    trigB = 7;
    UART1_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
    PFIC_EnableIRQ(UART1_IRQn);
#endif

    while(1);
}

/*********************************************************************
 * @fn      UART1_IRQHandler
 *
 * @brief   UART1ÖÐ¶Ïº¯Êý
 *
 * @return  none
 */
__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode")))
void UART1_IRQHandler(void)
{
    volatile uint8_t i;

    switch(UART1_GetITFlag())
    {
        case UART_II_LINE_STAT: // ÏßÂ·×´Ì¬´íÎó
        {
            UART1_GetLinSTA();
            break;
        }

        case UART_II_RECV_RDY: // Êý¾Ý´ïµ½ÉèÖÃ´¥·¢µã
            for(i = 0; i != trigB; i++)
            {
                RxBuff[i] = UART1_RecvByte();
                UART1_SendByte(RxBuff[i]);
            }
            break;

        case UART_II_RECV_TOUT: // ½ÓÊÕ³¬Ê±£¬ÔÝÊ±Ò»Ö¡Êý¾Ý½ÓÊÕÍê³É
            i = UART1_RecvString(RxBuff);
            UART1_SendString(RxBuff, i);
            break;

        case UART_II_THR_EMPTY: // ·¢ËÍ»º´æÇø¿Õ£¬¿É¼ÌÐø·¢ËÍ
            break;

        case UART_II_MODEM_CHG: // Ö»Ö§³Ö´®¿Ú0
            break;

        default:
            break;
    }
}
