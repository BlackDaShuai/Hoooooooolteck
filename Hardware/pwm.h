#ifndef __PWM_H
#define __PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32_board_config.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#define HTCFG_PWM_TM_PRESCALER                    (1)         // 1 ~ 65535
#define HTCFG_PWM_FREQ_HZ                         (50000)
#define HTCFG_PWM_IDLE_STATE                      (0)         // 0: 0 duty, 1: 100 duty

#define HTCFG_PWM_TM_RELOAD                       (HTCFG_PWM_TM_PCLK / HTCFG_PWM_TM_PRESCALER / HTCFG_PWM_FREQ_HZ)
#if (HTCFG_PWM_TM_RELOAD > 65536)
#error "HTCFG_PWM_TM_RELOAD out of range! Should be less than or equal to 65536."
#endif

#define HTCFG_PWM0_EN                             (1)
#define HTCFG_PWM1_EN                             (1)

#if (HTCFG_PWM_2CHANNEL)
#define HTCFG_PWM2_EN                             (0)
#define HTCFG_PWM3_EN                             (0)
#else
#define HTCFG_PWM2_EN                             (1)
#define HTCFG_PWM3_EN                             (1)
#endif

/* Exported constants --------------------------------------------------------------------------------------*/
#define HTCFG_PWM_TM_PORT                         STRCAT2(HT_,       HTCFG_PWM_TM_IPN)
#if (HTCFG_PWM0_EN == 1)
#define PWM_CH0                                   STRCAT2(TM_CH_,    HTCFG_PWM0_CHN)
#endif

#if (HTCFG_PWM1_EN == 1)
#define PWM_CH1                                   STRCAT2(TM_CH_,    HTCFG_PWM1_CHN)
#endif

#if (HTCFG_PWM2_EN == 1)
#define PWM_CH2                                   STRCAT2(TM_CH_,    HTCFG_PWM2_CHN)
#endif

#if (HTCFG_PWM3_EN == 1)
#define PWM_CH3                                   STRCAT2(TM_CH_,    HTCFG_PWM3_CHN)
#endif

#define PWM_DUTY_0       (0)
#define PWM_DUTY_25      (HTCFG_PWM_TM_RELOAD * 0.25)
#define PWM_DUTY_50      (HTCFG_PWM_TM_RELOAD * 0.5)
#define PWM_DUTY_75      (HTCFG_PWM_TM_RELOAD * 0.75)
#define PWM_DUTY_100     (0xFFFF)

#define PWM_FREQ_50K     (HTCFG_PWM_TM_PCLK / HTCFG_PWM_TM_PRESCALER / 50000)
#define PWM_FREQ_40K     (HTCFG_PWM_TM_PCLK / HTCFG_PWM_TM_PRESCALER / 40000)
#define PWM_FREQ_12K     (HTCFG_PWM_TM_PCLK / HTCFG_PWM_TM_PRESCALER / 12000)

/* Exported functions --------------------------------------------------------------------------------------*/
void PWM_Init(void);
void PWM_Cmd(ControlStatus NewState);

#if 1
#define PWM_SetFreq(uReload)     TM_SetCounterReload(HTCFG_PWM_TM_PORT, uReload)
#define PWM_UpdateDuty(CH, CMP)  TM_SetCaptureCompare(HTCFG_PWM_TM_PORT, CH, CMP)
#else
void PWM_SetFreq(u32 uReload);
void PWM_UpdateDuty(TM_CH_Enum TM_CH_n, u32 uCompare);
#endif

#ifdef __cplusplus
}
#endif

#endif
