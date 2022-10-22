#include "noda_wifi.h"
#include "WiFi.h"
#include "time.h"

#define NTP_SERVERS "pool.ntp.org", "time.nist.gov"
#define UNIX_TIME_NOV_13_2017 1510592825

#define PST_TIME_ZONE -8
#define PST_TIME_ZONE_DAYLIGHT_SAVINGS_DIFF   1

#define GMT_OFFSET_SECS (PST_TIME_ZONE * 3600)
#define GMT_OFFSET_SECS_DST ((PST_TIME_ZONE + PST_TIME_ZONE_DAYLIGHT_SAVINGS_DIFF) * 3600)

static void sync_sntp(void) {
    configTime(GMT_OFFSET_SECS, GMT_OFFSET_SECS_DST, NTP_SERVERS);
    time_t now = time(NULL);
    while (now < UNIX_TIME_NOV_13_2017) {
        delay(500);
        now = time(nullptr);
    }
}

void wifi_start_as_sta(const char* ssid, const char* pswd) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pswd);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    sync_sntp();
}

void wifi_stop(void) {
    WiFi.disconnect(true);
}
