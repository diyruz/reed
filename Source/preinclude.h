#define TC_LINKKEY_JOIN
#define NV_INIT
#define NV_RESTORE


#define TP2_LEGACY_ZC
//patch sdk
// #define ZDSECMGR_TC_ATTEMPT_DEFAULT_KEY TRUE

#define NWK_AUTO_POLL
#define MULTICAST_ENABLED FALSE

#define ZCL_READ
#define ZCL_BASIC
#define ZCL_IDENTIFY
#define ZCL_ZONE

#define ZSTACK_DEVICE_BUILD (DEVICE_BUILD_ENDDEVICE)

#define DISABLE_GREENPOWER_BASIC_PROXY
#define BDB_FINDING_BINDING_CAPABILITY_ENABLED 1

#define ZCL_REPORTING_DEVICE

#define ISR_KEYINTERRUPT
#define HAL_BUZZER FALSE

#define HAL_LED TRUE
#define HAL_I2C TRUE
#define BLINK_LEDS TRUE


//one of this boards
// #define HAL_BOARD_TARGET
// #define HAL_BOARD_CHDTECH_DEV

#if !defined(HAL_BOARD_TARGET) && !defined(HAL_BOARD_CHDTECH_DEV)
#error "Board type must be defined"
#endif

#define BDB_MAX_CLUSTERENDPOINTS_REPORTING 10

#if defined(HAL_BOARD_TARGET)
#define POWER_SAVING
#define DO_DEBUG_UART
#elif defined(HAL_BOARD_CHDTECH_DEV)
#define DO_DEBUG_UART
// #define DO_DEBUG_MT
#endif



#ifdef DO_DEBUG_UART
#define HAL_UART TRUE
#define HAL_UART_DMA 1
#define INT_HEAP_LEN (2685 - 0x4B - 0xBB)
#endif

#ifdef DO_DEBUG_MT
#define HAL_UART TRUE
#define HAL_UART_DMA 1
#define HAL_UART_ISR 2
#define INT_HEAP_LEN (2688-0xC4-0x15-0x44-0x20-0x1E)

#define MT_TASK

#define MT_UTIL_FUNC
#define MT_UART_DEFAULT_BAUDRATE HAL_UART_BR_115200
#define MT_UART_DEFAULT_OVERFLOW FALSE

#define ZTOOL_P1

#define MT_APP_FUNC
#define MT_APP_CNF_FUNC
#define MT_SYS_FUNC
#define MT_ZDO_FUNC
#define MT_ZDO_MGMT
#define MT_DEBUG_FUNC

#endif



#if defined(HAL_BOARD_TARGET)
#define FACTORY_RESET_BY_LONG_PRESS_PORT 0x04 //port2

#define HAL_KEY_P0_INPUT_PINS BV(5)
#define HAL_KEY_P0_INPUT_PINS_EDGE HAL_KEY_RISING_EDGE

#define HAL_KEY_P2_INPUT_PINS BV(0)

#elif defined(HAL_BOARD_CHDTECH_DEV)
#define FACTORY_RESET_BY_LONG_PRESS_PORT 0x01

#define HAL_KEY_P0_INPUT_PINS BV(1)
// #define HAL_KEY_P0_INPUT_PINS_EDGE HAL_KEY_RISING_EDGE

#define HAL_KEY_P1_INPUT_PINS BV(1)

#define HAL_KEY_P2_INPUT_PINS BV(0)
#endif

#include "hal_board_cfg.h"

#include "stdint.h"
#include "stddef.h"
