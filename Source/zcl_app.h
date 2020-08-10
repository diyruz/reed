#ifndef ZCL_APP_H
#define ZCL_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */
#include "version.h"
#include "zcl.h"


/*********************************************************************
 * CONSTANTS
 */
#define HAL_UNKNOWN_BUTTON HAL_KEY_CODE_NOKEY
// Application Events

#define APP_CONST_ONE_MINUTE_IN_MS ((uint32) 60 * (uint32) 1000)



#define APP_REPORT_DELAY (30 * APP_CONST_ONE_MINUTE_IN_MS)


/*********************************************************************
 * MACROS
 */

#define R               ACCESS_CONTROL_READ
#define RR              (R | ACCESS_REPORTABLE)

#define BASIC           ZCL_CLUSTER_ID_GEN_BASIC
#define POWER_CFG       ZCL_CLUSTER_ID_GEN_POWER_CFG
#define TEMP            ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT
#define HUMIDITY        ZCL_CLUSTER_ID_MS_RELATIVE_HUMIDITY
#define PRESSURE        ZCL_CLUSTER_ID_MS_PRESSURE_MEASUREMENT
#define ILLUMINANCE     ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT
#define IAS_ZONE        ZCL_CLUSTER_ID_SS_IAS_ZONE

#define ZCL_UINT8       ZCL_DATATYPE_UINT8
#define ZCL_UINT16      ZCL_DATATYPE_UINT16
#define ZCL_UINT32      ZCL_DATATYPE_UINT32
#define ZCL_INT16       ZCL_DATATYPE_INT16


#define ATTRID_MS_PRESSURE_MEASUREMENT_MEASURED_VALUE_HPA       0x0200
#define ATTRID_POWER_CFG_BATTERY_VOLTAGE_RAW_ADC                0x0200
#define ATTRID_MS_RELATIVE_HUMIDITY_MEASURED_VALUE_RAW_ADC      0x0200



/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * VARIABLES
 */

extern SimpleDescriptionFormat_t zclApp_FirstEP;
extern SimpleDescriptionFormat_t zclApp_SecondEP;
extern SimpleDescriptionFormat_t zclApp_ThirdEP;

extern uint8 zclApp_BatteryVoltage;
extern uint8 zclApp_BatteryPercentageRemainig;


// attribute list
extern CONST zclAttrRec_t zclApp_AttrsFirstEP[];
extern CONST uint8 zclApp_AttrsFirstEPCount;


extern const uint8 zclApp_ManufacturerName[];
extern const uint8 zclApp_ModelId[];
extern const uint8 zclApp_PowerSource;

// APP_TODO: Declare application specific attributes here

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Initialization for the task
 */
extern void zclApp_Init(byte task_id);


/*
 *  Event Process for the task
 */
extern UINT16 zclApp_event_loop(byte task_id, UINT16 events);

void user_delay_ms(uint32_t period);

#ifdef __cplusplus
}
#endif

#endif /* ZCL_APP_H */
