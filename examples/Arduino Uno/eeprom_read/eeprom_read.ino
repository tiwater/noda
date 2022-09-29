#include "noda.h"

uint32_t chipId = 0;

void setup() {
	noda_startup();
}

void loop() {
	noda_onloop();
}