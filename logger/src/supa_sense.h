#ifndef _SUPA_SENSE_H_
#define _SUPA_SENSE_H_

#include <Arduino.h>
#include <ESP32_Supabase.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "config.h"
#include "secrets.h"

/// @brief The first function called when the ESP boots.
void setup() {
    supaSense.run();
}

/// @brief Theoretically called after `setup`.
void loop() {
    // DO NOT REMOVE THIS FUNCTION!
}

/// @brief Sets up the sensors ready to be read.
/// @return `true` if the sensors were successfully set up.
bool setupSensors();

/// @brief Reads the sensors and saves the readings to the json object.
/// @return `true` if the sensors were successfully read.
bool readSensors();

/// @brief A global instance of SupaSense
SupaSense supaSense;

class SupaSense {
   private:
    /// @brief The Supabase client
    Supabase _supabase;

    /// @brief Puts the ESP into a deep sleep for a set amount of time.
    void _sleep() {
        Serial.print(F("\n[SupaSense] Going to sleep..."));
        ESP.deepSleep(SLEEP_DURATION - micros());
    }

    /// @brief Reboots the ESP.
    void _restart() {
        Serial.print(F("\n[SupaSense] Restarting..."));
        ESP.restart();
    }

    /// @brief Waits for the Serial to start.
    void _startSerial() {
        Serial.begin(115200);
        Serial.setTimeout(SERIAL_TIMEOUT);
        while (!Serial) delay(5);
    }

    /// @brief Tries to connect to the WiFi network before the timeout.
    /// @return `true` if successfully connected to WiFi.
    bool _connectToWiFi() {
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print(F("\n[SupaSense] Connecting to WiFi... "));

        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            delay(10);
            if (millis() - startTime > WIFI_TIMEOUT) {
                Serial.print(F("failed."));
                return false;
            }
        }
        return true;
    }

    /// @brief Sets up the Supabase configuration and starts the client.
    void _startSupabase() {
        _supabase.begin(SUPABASE_URL, SUPABASE_KEY);
    }

    /// @brief Inserts the readings as a new row in the Supabase table.
    /// @return `true` if the readings were successfully uploaded.
    bool _uploadReadingsToSupabase() {
        json["sensor_id"] = SENSOR_ID;

        String jsonAsString = json.as<String>();

        Serial.print(F("\n[SupaSense] Current readings JSON: "));
        Serial.print(jsonAsString);
        Serial.print(F("\n[SupaSense] Uploading readings to Supbase... "));

        int code = _supabase.insert(SUPABASE_TABLE, jsonAsString, false);

        if (code < 200 || code >= 300) {
            Serial.print(F("failed. (error code: "));
            Serial.print(code);
            Serial.print(F(")"));
        };
        return true;
    }

    /// @brief Calls `setupSensors`.
    /// @return `true` if the sensors were successfully set up.
    bool _setupSensors() {
        Serial.print(F("\n[SupaSense] Setting up sensors... "));
        if (setupSensors() == false) {
            Serial.print(F("failed."));
            return false;
        }
        return true;
    }

    /// @brief Calls `readSensors`.
    /// @return `true` if the sensors were successfully read.
    bool _readSensors() {
        Serial.print(F("\n[SupaSense] Reading sensors... "));
        if (readSensors() == false) {
            Serial.print(F("failed."));
            return false;
        }
        return true;
    }

   public:
    /// @brief The JSON object to be uploaded to Supabase.
    StaticJsonDocument<JSON_OBJECT_SIZE(JSON_SIZE)> json;

    /// @brief Performs the lifecycle of the sensor.
    void run() {
        _startSerial();
        Serial.print(F("\n\n!! Did you remember to update the sensor ID? !!\n\n"));

        if (_connectToWiFi() == false) _restart();
        _startSupabase();

        if (_setupSensors() == false) _sleep();
        if (_readSensors() == false) _sleep();

        _uploadReadingsToSupabase();
        _sleep();
    }
};

#endif