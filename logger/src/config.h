#ifndef _CONFIG_H_
#define _CONFIG_H_

// Configure this file to your own liking.

const byte SENSOR_ID = 3;
const String SUPABASE_TABLE = "readings";

const byte JSON_SIZE = 9;

const int SERIAL_TIMEOUT = 2000;       // in milliseconds
const int WIFI_TIMEOUT = 60000;        // in milliseconds
const double SLEEP_DURATION = 1.8e+9;  // in microseconds -> 30min

const float TEMPERATURE_OFFSET = 0.0;  // in degrees celcius
const float HUMIDITY_OFFSET = 0.0;     // in %

#endif