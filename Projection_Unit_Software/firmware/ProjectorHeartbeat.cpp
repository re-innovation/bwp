#include "Config.h"
#ifdef ENABLE_HEARTBEAT
#include "ProjectorHeartbeat.h"
#endif

#ifdef ENABLE_HEARTBEAT
Heartbeat ProjectorHeartbeat(HEARTBEAT_LED_PIN);
#endif

