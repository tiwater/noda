#define NODA_HEARTBEAT_MILLIS 1000

#include <noda.h>
#include <noda_device_center.h>
#include <noda_ntc_sensor.h>
#include <noda_log.h>

NODA_DEVICE_LIST {
    NODA_DEVICE_ADD(noda_ntc_sensor, .name="ntc", .pin=3, .chn=3, .vref=3300)
//    NODA_DEVICE_ADD(silan_sc7a20, .name="accel", .sda=7, .scl=6, .addr=25, .freq=100)
//    NODA_DEVICE_ADD(hx711, .name="weigh", .pwr=5, .sck=20, .dout=21, .gain=1)
//    NODA_DEVICE_ADD(ws2812rmt, .name="led", .pin=10, .chn=0, .nums=6)
};

int noda_startup(int argc, const char** argv) {
    for (int i = 0; i < argc; ++i) {
        noda_print("%s ", argv[i]);
    }
    noda_print("\n");
    noda_device_center_startup();
    return NODA_OK;
}

int noda_cleanup(void) {
    noda_device_center_cleanup();
    noda_logd("noda_cleanup");
    return NODA_OK;
}

int noda_onloop(void) {
    static int counter = 0;
    noda_logd("noda_loop %d", counter++);
    int adc = noda_getval(noda_ntc_sensor, "ntc", adc);
    noda_logd("noda_ntc_sensor adc = %d", adc);
    return counter > 10 ? NODA_FAIL : NODA_OK;
}
