
#include "AF.h"
#include "OSAL.h"
#include "OSAL_Clock.h"

#include "ZComDef.h"
#include "ZDApp.h"
#include "ZDNwkMgr.h"
#include "ZDObject.h"
#include "math.h"

#include "nwk_util.h"
#include "zcl.h"
#include "zcl_app.h"
#include "zcl_diagnostic.h"
#include "zcl_general.h"
#include "zcl_ss.h"

#include "bdb.h"
#include "bdb_interface.h"
#include "gp_interface.h"

#include "Debug.h"
#include "battery.h"

#include "OnBoard.h"

/* HAL */

#include "hal_drivers.h"
#include "hal_i2c.h"
#include "hal_key.h"
#include "hal_led.h"

#include "battery.h"
#include "commissioning.h"
#include "factory_reset.h"
#include "utils.h"
#include "version.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

extern bool requestNewTrustCenterLinkKey;
byte zclApp_TaskID;

/*********************************************************************
 * GLOBAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
afAddrType_t inderect_DstAddr = {.addrMode = (afAddrMode_t)AddrNotPresent, .endPoint = 0, .addr.shortAddr = 0};
/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void zclApp_HandleKeys(byte shift, byte keys);

/*********************************************************************
 * ZCL General Profile Callback table
 */
static zclGeneral_AppCallbacks_t zclApp_CmdCallbacks = {
    NULL, // Basic Cluster Reset command
    NULL, // Identify Trigger Effect command
    NULL, // On/Off cluster commands
    NULL, // On/Off cluster enhanced command Off with Effect
    NULL, // On/Off cluster enhanced command On with Recall Global Scene
    NULL, // On/Off cluster enhanced command On with Timed Off
    NULL, // RSSI Location command
    NULL  // RSSI Location Response command
};

void zclApp_Init(byte task_id) {
    // this is important to allow connects throught routers
    // to make this work, coordinator should be compiled with this flag #define TP2_LEGACY_ZC
    requestNewTrustCenterLinkKey = FALSE;

    zclApp_TaskID = task_id;

    zclGeneral_RegisterCmdCallbacks(1, &zclApp_CmdCallbacks);
    zcl_registerAttrList(zclApp_FirstEP.EndPoint, zclApp_AttrsFirstEPCount, zclApp_AttrsFirstEP);
    bdb_RegisterSimpleDescriptor(&zclApp_FirstEP);
    bdb_RegisterSimpleDescriptor(&zclApp_SecondEP);
    bdb_RegisterSimpleDescriptor(&zclApp_ThirdEP);

    zcl_registerForMsg(zclApp_TaskID);

    // Register for all key events - This app will handle all key events
    RegisterForKeys(zclApp_TaskID);
    LREP("Started build %s \r\n", zclApp_DateCodeNT);
    ZMacSetTransmitPower(TX_PWR_PLUS_4); // set 4dBm
}

uint16 zclApp_event_loop(uint8 task_id, uint16 events) {
    afIncomingMSGPacket_t *MSGpkt;

    (void)task_id; // Intentionally unreferenced parameter
    if (events & SYS_EVENT_MSG) {
        while ((MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive(zclApp_TaskID))) {
            switch (MSGpkt->hdr.event) {
            case KEY_CHANGE:
                zclApp_HandleKeys(((keyChange_t *)MSGpkt)->state, ((keyChange_t *)MSGpkt)->keys);
                break;

            case ZCL_INCOMING_MSG:
                if (((zclIncomingMsg_t *)MSGpkt)->attrCmd) {
                    osal_mem_free(((zclIncomingMsg_t *)MSGpkt)->attrCmd);
                }
            break;

            default:
                break;
            }
            // Release the memory
            osal_msg_deallocate((uint8 *)MSGpkt);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    // Discard unknown events
    return 0;
}

static void zclApp_HandleKeys(byte portAndAction, byte keyCode) {
    LREP("zclApp_HandleKeys portAndAction=0x%X keyCode=0x%X\r\n", portAndAction, keyCode);
    HalLedSet(HAL_LED_1, HAL_LED_MODE_BLINK);
    zclFactoryResetter_HandleKeys(portAndAction, keyCode);
    zclCommissioning_HandleKeys(portAndAction, keyCode);
    zclBattery_HandleKeys(portAndAction, keyCode);
    bool contact = portAndAction & HAL_KEY_PRESS ? TRUE : FALSE;
    uint8 endPoint = 0;
    if (portAndAction & HAL_KEY_PORT0) {
        endPoint = zclApp_FirstEP.EndPoint;
    } else if (portAndAction & HAL_KEY_PORT1) {
        endPoint = zclApp_SecondEP.EndPoint;
    } else if (portAndAction & HAL_KEY_PORT2) {
        endPoint = zclApp_ThirdEP.EndPoint;
    }

    LREP("contact=%d endpoint=%d\r\n", contact, endPoint);
    uint16 alarmStatus = 0;
    if (!contact) {
        alarmStatus |= BV(0);
    }

    zclSS_IAS_Send_ZoneStatusChangeNotificationCmd(endPoint, &inderect_DstAddr, alarmStatus, 0, 0, 0, true, bdb_getZCLFrameCounter());
}

/****************************************************************************
****************************************************************************/
