/* ['Common headers' begin (DON'T REMOVE THIS LINE!)] */
#include "IoT_CI.h"
/* ['Common headers' end (DON'T REMOVE THIS LINE!)] */

/* ['IoTMng' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_IOTMNG_INITIAL 26
#define ID_IOTMNG_DISCONNECTING 27
#define ID_IOTMNG_CONNECTING 28
#define ID_IOTMNG_WORKINGONLINE 29
#define ID_IOTMNG_WORKINGOFFLINE 30

void IoTMng(  );
/* ['IoTMng' end (DON'T REMOVE THIS LINE!)] */

/* ['FuncMngr' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_FUNCMNGR_INITIAL 23
#define ID_FUNCMNGR_INIT 24
#define ID_FUNCMNGR_WORKING 25

void FuncMngr(  );
/* ['FuncMngr' end (DON'T REMOVE THIS LINE!)] */

/* ['Emergency' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_EMERGENCY_INITIAL 18
#define ID_EMERGENCY_NORMAL 19
#define ID_EMERGENCY_WARNINGFILTER 20
#define ID_EMERGENCY_EMERGENCY 21
#define ID_EMERGENCY_HEALING 22

void Emergency(  );
/* ['Emergency' end (DON'T REMOVE THIS LINE!)] */

/* ['PulsingCmd' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_PULSINGCMD_INITIAL 7
#define ID_PULSINGCMD_WAITING 8
#define ID_PULSINGCMD_SENDPULSEUP 9
#define ID_PULSINGCMD_SENDPULSEEND 10
#define ID_PULSINGCMD_SENDPULSEDOWN 11

void PulsingCmd(  );
/* ['PulsingCmd' end (DON'T REMOVE THIS LINE!)] */

/* ['ReceiveSysCmd' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_RECEIVESYSCMD_INITIAL 4
#define ID_RECEIVESYSCMD_WAITING 5
#define ID_RECEIVESYSCMD_READCHAR 6

void ReceiveSysCmd(  );
/* ['ReceiveSysCmd' end (DON'T REMOVE THIS LINE!)] */

/* ['DispatchSysCmd' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_DISPATCHSYSCMD_INITIAL 0
#define ID_DISPATCHSYSCMD_WAITING 1
#define ID_DISPATCHSYSCMD_DECODECMD 2
#define ID_DISPATCHSYSCMD_PULSECMD 3

void DispatchSysCmd(  );
/* ['DispatchSysCmd' end (DON'T REMOVE THIS LINE!)] */
