#include "SignalSender.h"
#include <esp_wifi.h>

uint8_t SignalSender::getStrength(){
	wifi_ap_record_t info;
	uint8_t percentage = 0;

	if(esp_wifi_sta_get_ap_info(&info) == ESP_OK){
		auto con = constrain(info.rssi, minSS, maxSS);
		percentage = map(con, minSS, maxSS, 0, 100);
	}
	return percentage;
}
