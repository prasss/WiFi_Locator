#ifndef _LINUX_WIFI_H
#define _LINUX_WIFI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>


typedef enum
{
	WIFI_ERROR,
  WIFI_STATION_DISCONNECTED,
	WIFI_STATION_CONNECTED
}wifi_state_e;

json_object * wifi_get_essid();

#endif
