/* ['Common headers' begin (DON'T REMOVE THIS LINE!)] */
#include "IoT_CI.h"
/* ['Common headers' end (DON'T REMOVE THIS LINE!)] */

/* ['IoTMng' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_IOTMNG_INITIAL 27
#define ID_IOTMNG_DISCONNECTING 28
#define ID_IOTMNG_CONNECTING 29
#define ID_IOTMNG_WORKINGONLINE 30
#define ID_IOTMNG_WORKINGOFFLINE 31

void IoTMng(  );
/* ['IoTMng' end (DON'T REMOVE THIS LINE!)] */

/* ['FuncMngr' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_FUNCMNGR_INITIAL 24
#define ID_FUNCMNGR_INIT 25
#define ID_FUNCMNGR_WORKING 26

void FuncMngr(  );
/* ['FuncMngr' end (DON'T REMOVE THIS LINE!)] */

/* ['Emergency' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_EMERGENCY_INITIAL 19
#define ID_EMERGENCY_NORMAL 20
#define ID_EMERGENCY_WARNINGFILTER 21
#define ID_EMERGENCY_EMERGENCY 22
#define ID_EMERGENCY_HEALING 23

void Emergency(  );
/* ['Emergency' end (DON'T REMOVE THIS LINE!)] */

/* ['PulsingCmd' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_PULSINGCMD_INITIAL 8
#define ID_PULSINGCMD_WAITING 9
#define ID_PULSINGCMD_SENDPULSEUP 10
#define ID_PULSINGCMD_SENDPULSEEND 11
#define ID_PULSINGCMD_SENDPULSEDOWN 12

void PulsingCmd(  );
/* ['PulsingCmd' end (DON'T REMOVE THIS LINE!)] */

/* ['ReceiveSysCmd' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_RECEIVESYSCMD_INITIAL 5
#define ID_RECEIVESYSCMD_WAITING 6
#define ID_RECEIVESYSCMD_READCHAR 7

void ReceiveSysCmd(  );
/* ['ReceiveSysCmd' end (DON'T REMOVE THIS LINE!)] */

/* ['DispatchSysCmd' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_DISPATCHSYSCMD_INITIAL 0
#define ID_DISPATCHSYSCMD_WAITING 1
#define ID_DISPATCHSYSCMD_PULSECMD 2
#define ID_DISPATCHSYSCMD_DECODECMD 3
#define ID_DISPATCHSYSCMD_EMGCYCMD 4

void DispatchSysCmd(  );
/* ['DispatchSysCmd' end (DON'T REMOVE THIS LINE!)] */
