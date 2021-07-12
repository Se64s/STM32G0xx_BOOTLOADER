/**
 * @file    bsp_serial.c
 * @author  Sebastián Del Moral (sebmorgal@gmail.com)
 * @brief   Low level layer to handle serial interface.
 * @version 0.1
 * @date    2020-09-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/* Private includes --------------------------------------------------------*/

#include "bsp_serial.h"

#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

/* Private defines ---------------------------------------------------------*/

#define SERIAL_RX_MAX_BUFF_LEN  128U        /*!< Size of serial 0 buffer reception */

/* Control structure for serial rx data */
typedef struct SerialRxBuff
{
    uint8_t pu8Serial0RxBuff[SERIAL_RX_MAX_BUFF_LEN];
    uint32_t u32RxCount;
} SerialRxBuff_t;

/* Private variable --------------------------------------------------------*/

SerialRxBuff_t xBSP_Serial0RxBuff = { 0U };

/* Private macro -----------------------------------------------------------*/
/* Private functions prototypes --------------------------------------------*/
/* Private functions definition --------------------------------------------*/
/* Public function definition ----------------------------------------------*/

void BSP_Serial0Init(void)
{
    LL_USART_InitTypeDef USART_InitStruct = {0U};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0U};

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART4);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

    /**USART4 GPIO Configuration  
    PA0   ------> USART4_TX
    PA1   ------> USART4_RX 
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Setup Rx irq */
    NVIC_SetPriority(USART3_4_IRQn, 0);
    NVIC_EnableIRQ(USART3_4_IRQn);

    /* Setup peripheral */
    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = 115200U;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(USART4, &USART_InitStruct);

    LL_USART_SetTXFIFOThreshold(USART4, LL_USART_FIFOTHRESHOLD_1_8);
    LL_USART_SetRXFIFOThreshold(USART4, LL_USART_FIFOTHRESHOLD_1_8);

    LL_USART_DisableFIFO(USART4);

    LL_USART_ConfigAsyncMode(USART4);

    LL_USART_Enable(USART4);

    /* Polling USART4 initialisation */
    while( ( !( LL_USART_IsActiveFlag_TEACK(USART4) ) ) || ( !( LL_USART_IsActiveFlag_REACK(USART4) ) ) )
    {
    }

    /* Enable RXNE and Error interrupts */
    LL_USART_EnableIT_RXNE(USART4);
    LL_USART_EnableIT_ERROR(USART4);
}

void BSP_Serial0DeInit(void)
{
    LL_USART_DisableIT_RXNE(USART4);
    LL_USART_DisableIT_ERROR(USART4);

    NVIC_DisableIRQ(USART3_4_IRQn);

    (void)LL_USART_DeInit(USART4);
}

uint32_t BSP_Serial0Write(uint8_t* pu8buff, uint32_t u32DataLen)
{
    uint32_t l = 0U;

    while (l < u32DataLen)
    {
        /* Wait for TXE flag to be raised */
        while (!LL_USART_IsActiveFlag_TXE(USART4))
        {
        }

        /* If last char to be sent, clear TC flag */
        if (l == (u32DataLen - 1U))
        {
            LL_USART_ClearFlag_TC(USART4);
        }

        /* Write character in Transmit Data register.
        TXE flag is cleared by writing data in TDR register */
        LL_USART_TransmitData8(USART4, pu8buff[l]);

        l++;
    }

    /* Wait for TC flag to be raised for last char */
    while (!LL_USART_IsActiveFlag_TC(USART4))
    {
    }

    return l;
}

uint32_t BSP_Serial0Read(uint8_t* pu8buff, uint32_t u32DataMaxLen)
{
    NVIC_DisableIRQ(USART3_4_IRQn);

    uint32_t u32RxCount = xBSP_Serial0RxBuff.u32RxCount;

    if (u32RxCount > u32DataMaxLen)
    {
        u32RxCount = u32DataMaxLen;
    }

    for (uint32_t iData = 0; iData < u32RxCount; iData++)
    {
        pu8buff[iData] = xBSP_Serial0RxBuff.pu8Serial0RxBuff[iData];
        xBSP_Serial0RxBuff.u32RxCount--;
    }

    NVIC_EnableIRQ(USART3_4_IRQn);

    return u32RxCount;
}

uint32_t BSP_Serial0GetRxCount(void)
{
    return xBSP_Serial0RxBuff.u32RxCount;
}

void BSP_Serial0IrqHandler(void)
{
    if ( LL_USART_IsActiveFlag_RXNE(USART4) && LL_USART_IsEnabledIT_RXNE(USART4) )
    {
        __IO uint8_t u8RxChar;

        /* Read Received character. RXNE flag is cleared by reading of RDR register */
        u8RxChar = LL_USART_ReceiveData8(USART4);

        /* Feed Rx buff */
        if ( xBSP_Serial0RxBuff.u32RxCount < ( SERIAL_RX_MAX_BUFF_LEN - 1U ) )
        {
            xBSP_Serial0RxBuff.pu8Serial0RxBuff[xBSP_Serial0RxBuff.u32RxCount++] = u8RxChar;
        }
    }
    else
    {
        /* Handle error */
    }
}

/* EOF */