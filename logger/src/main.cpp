#include <Arduino.h>
#include <SHT2x.h>

#include "config.h"
#include "supa_sense.h"

SHT2x sht;

bool setupSensors() {
    // Replace the following code with code for setting up your sensors.

    sht.begin();
    return true;
}

bool readSensors() {
    // Replace the following code with code for reading from your sensors.

    if (!sht.isConnected()) return false;

    bool isReadSuccessful = sht.read();
    if (isReadSuccessful == false) return false;

    float temperature = sht.getTemperature();
    float humidity = sht.getHumidity();

    temperature += TEMPERATURE_OFFSET;
    humidity += HUMIDITY_OFFSET;

    supaSense.json["temperature"] = temperature;
    supaSense.json["humidity"] = humidity;

    return true;
}
