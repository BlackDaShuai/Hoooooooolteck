#include "ht32.h"
#include "ht32_board_config.h"
#include "pwm.h"



#define HTCFG_PWM_TM_AFIO_FUN                     STRCAT2(AFIO_FUN_, HTCFG_PWM_TM_IPN)
#define HTCFG_PWM_TM_IRQn                         STRCAT2(HTCFG_PWM_TM_IPN,  _IRQn)
#define HTCFG_PWM_TM_IRQHandler                   STRCAT2(HTCFG_PWM_TM_IPN,  _IRQHandler)






#if (HTCFG_PWM_IDLE_STATE == 0)
#define HTCFG_PWM_IDLE_DUTY PWM_DUTY_0
#else
#define HTCFG_PWM_IDLE_DUTY PWM_DUTY_100
#endif

#if (HTCFG_PWM0_EN == 1)
#define HTCFG_PWM0_GPIO_ID                        STRCAT2(GPIO_P,    HTCFG_PWM0_GPIOX)
#define HTCFG_PWM0_AFIO_PIN                       STRCAT2(AFIO_PIN_, HTCFG_PWM0_GPION)
#endif

#if (HTCFG_PWM1_EN == 1)
#define HTCFG_PWM1_GPIO_ID                        STRCAT2(GPIO_P,    HTCFG_PWM1_GPIOX)
#define HTCFG_PWM1_AFIO_PIN                       STRCAT2(AFIO_PIN_, HTCFG_PWM1_GPION)
#endif

#if (HTCFG_PWM2_EN == 1)
#define HTCFG_PWM2_GPIO_ID                        STRCAT2(GPIO_P,    HTCFG_PWM2_GPIOX)
#define HTCFG_PWM2_AFIO_PIN                       STRCAT2(AFIO_PIN_, HTCFG_PWM2_GPION)
#endif

#if (HTCFG_PWM3_EN == 1)
#define HTCFG_PWM3_GPIO_ID                        STRCAT2(GPIO_P,    HTCFG_PWM3_GPIOX)
#define HTCFG_PWM3_AFIO_PIN                       STRCAT2(AFIO_PIN_, HTCFG_PWM3_GPION)
#endif






void _PWM_CH_Init(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, TM_OutputInitTypeDef *OutInit);


s32 gIsTMStop = 0;




//PWM初始化
void PWM_Init(void)
{
  { 
    //使能时钟
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.HTCFG_PWM_TM_IPN = 1;
    CKCUClock.Bit.AFIO             = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  //复用引脚
  #if (HTCFG_PWM0_EN == 1)
  AFIO_GPxConfig(HTCFG_PWM0_GPIO_ID, HTCFG_PWM0_AFIO_PIN, HTCFG_PWM_TM_AFIO_FUN);
  #endif
  #if (HTCFG_PWM1_EN == 1)
  AFIO_GPxConfig(HTCFG_PWM1_GPIO_ID, HTCFG_PWM1_AFIO_PIN, HTCFG_PWM_TM_AFIO_FUN);
  #endif
  #if (HTCFG_PWM2_EN == 1)
  AFIO_GPxConfig(HTCFG_PWM2_GPIO_ID, HTCFG_PWM2_AFIO_PIN, HTCFG_PWM_TM_AFIO_FUN);
  #endif
  #if (HTCFG_PWM3_EN == 1)
  AFIO_GPxConfig(HTCFG_PWM3_GPIO_ID, HTCFG_PWM3_AFIO_PIN, HTCFG_PWM_TM_AFIO_FUN);
  #endif


  { 
    //时基配置
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = HTCFG_PWM_TM_PRESCALER - 1;            // Timer clock = CK_AHB / HTCFG_PWM_TM_PRESCALER
    TimeBaseInit.CounterReload = HTCFG_PWM_TM_RELOAD - 1;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_PWM_TM_PORT, &TimeBaseInit);
    TM_CRRPreloadCmd(HTCFG_PWM_TM_PORT, ENABLE);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    TM_ClearFlag(HTCFG_PWM_TM_PORT, TM_FLAG_UEV);
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below this function.
    */
    TM_OutputInitTypeDef OutInit;
    #if 0
    OutInit.Channel = TM_CH_0; // Changed by "_PWM_CH_Init()"
    #endif
    OutInit.OutputMode = TM_OM_PWM1;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = HTCFG_PWM_IDLE_DUTY;
    OutInit.AsymmetricCompare = 0;

    #if (HTCFG_PWM0_EN == 1)
    _PWM_CH_Init(HTCFG_PWM_TM_PORT, PWM_CH0, &OutInit);
    #endif

    #if (HTCFG_PWM1_EN == 1)
    _PWM_CH_Init(HTCFG_PWM_TM_PORT, PWM_CH1, &OutInit);
    #endif

    #if (HTCFG_PWM2_EN == 1)
    _PWM_CH_Init(HTCFG_PWM_TM_PORT, PWM_CH2, &OutInit);
    #endif

    #if (HTCFG_PWM3_EN == 1)
    _PWM_CH_Init(HTCFG_PWM_TM_PORT, PWM_CH3, &OutInit);
    #endif
  }

  #if (IS_IPN_MCTM(HTCFG_PWM_TM_IPN))
  {
    // Only MCTM need OE Enable
    MCTM_CHMOECmd(HTCFG_PWM_TM_PORT, ENABLE);

    // Enable MT_CHnN
    //MCTM_ChannelNConfig(HTCFG_PWM_TM_PORT, HTCFG_PWM_TM_CH, TM_CHCTL_ENABLE);
  }
  #endif

  /* Enable Update Event interrupt                                                                          */
  NVIC_EnableIRQ(HTCFG_PWM_TM_IRQn);

  #if 0 // Default enable or disable
  TM_Cmd(HTCFG_PWM_TM_PORT, ENABLE);
  #endif
}

/*********************************************************************************************************//**
  * @brief  This function handles TM interrupt.
  * @retval None
  ***********************************************************************************************************/
void HTCFG_PWM_TM_IRQHandler(void)
{
  TM_ClearFlag(HTCFG_PWM_TM_PORT, TM_INT_UEV);

  if (gIsTMStop == 1)
  {
    gIsTMStop = 2;
  }
  else if (gIsTMStop == 2)
  {
    TM_Cmd(HTCFG_PWM_TM_PORT, DISABLE);

    TM_IntConfig(HTCFG_PWM_TM_PORT, TM_INT_UEV, DISABLE);

    gIsTMStop = 0;
  }
}

/*********************************************************************************************************//**
  * @brief Enable or Disable PWM.
  * @param NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void PWM_Cmd(ControlStatus NewState)
{
  if (NewState == ENABLE)
  {
    TM_Cmd(HTCFG_PWM_TM_PORT, NewState);
  }
  else
  {
    // Set the flag to stop timer after update event.
    gIsTMStop = 1;

    // Set PWM as IDLE duty before stop it
    #if (HTCFG_PWM0_EN == 1)
    PWM_UpdateDuty(PWM_CH0, HTCFG_PWM_IDLE_DUTY);
    #endif
    #if (HTCFG_PWM1_EN == 1)
    PWM_UpdateDuty(PWM_CH1, HTCFG_PWM_IDLE_DUTY);
    #endif
    #if (HTCFG_PWM2_EN == 1)
    PWM_UpdateDuty(PWM_CH2, HTCFG_PWM_IDLE_DUTY);
    #endif
    #if (HTCFG_PWM3_EN == 1)
    PWM_UpdateDuty(PWM_CH3, HTCFG_PWM_IDLE_DUTY);
    #endif

    TM_IntConfig(HTCFG_PWM_TM_PORT, TM_INT_UEV, ENABLE);
  }
}

#if 0
/*********************************************************************************************************//**
  * @brief  Set PWM Frequency
  * @param  uReload: Reload value of timer)
  * @retval None
  ***********************************************************************************************************/
void PWM_SetFreq(u32 uReload)
{
  TM_SetCounterReload(HTCFG_PWM_TM_PORT, uReload);
}

/*********************************************************************************************************//**
  * @brief  Update PWM Duty
  * @param  TM_CH_n: Specify the TM channel.
  * @param  uCompare: PWM duty (Compare value of timer)
  * @retval None
  ***********************************************************************************************************/
void PWM_UpdateDuty(TM_CH_Enum TM_CH_n, u32 uCompare)
{
  TM_SetCaptureCompare(HTCFG_PWM_TM_PORT, TM_CH_n, uCompare);
}
#endif

/*********************************************************************************************************//**
  * @brief  Init PWM Channel
  * @param  TMx: where TMx is the selected TM from the TM peripheral.
  * @param  TM_CH_n: Specify the TM channel.
  * @param  OutInit: Point to a TM_OutputInitTypeDef structure
  * @retval None
  ***********************************************************************************************************/
void _PWM_CH_Init(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, TM_OutputInitTypeDef* OutInit)
{
  OutInit->Channel = TM_CH_n;
  TM_OutputInit(HTCFG_PWM_TM_PORT, OutInit);
  TM_CHCCRPreloadConfig(TMx, TM_CH_n, ENABLE);
}
