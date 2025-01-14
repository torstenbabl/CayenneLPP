// Adapted from https://developer.mbed.org/teams/myDevicesIoT/code/Cayenne-LPP/

// Copyright © 2017 The Things Network
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef CAYENNE_LPP_H
#define CAYENNE_LPP_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define LPP_DIGITAL_INPUT 0         // 1 byte
#define LPP_DIGITAL_OUTPUT 1        // 1 byte
#define LPP_ANALOG_INPUT 2          // 2 bytes, 0.01 signed
#define LPP_ANALOG_OUTPUT 3         // 2 bytes, 0.01 signed
#define LPP_GENERIC_SENSOR 100      // 4 bytes, unsigned
#define LPP_LUMINOSITY 101          // 2 bytes, 1 lux unsigned
#define LPP_PRESENCE 102            // 1 byte, bool
#define LPP_TEMPERATURE 103         // 2 bytes, 0.1°C signed
#define LPP_RELATIVE_HUMIDITY 104   // 1 byte, 0.5% unsigned
#define LPP_ACCELEROMETER 113       // 2 bytes per axis, 0.001G
#define LPP_BAROMETRIC_PRESSURE 115 // 2 bytes 0.1hPa unsigned
#define LPP_VOLTAGE 116             // 2 bytes 0.01V unsigned
#define LPP_CURRENT 117             // 2 bytes 0.001A unsigned
#define LPP_FREQUENCY 118           // 4 bytes 1Hz unsigned
#define LPP_PERCENTAGE 120          // 1 byte 1-100% unsigned
#define LPP_ALTITUDE 121            // 2 byte 1m signed
#define LPP_CONCENTRATION 125       // 2 bytes, 1 ppm unsigned
#define LPP_POWER 128               // 2 byte, 1W, unsigned
#define LPP_DISTANCE 130            // 4 byte, 0.001m, unsigned
#define LPP_ENERGY 131              // 4 byte, 0.001kWh, unsigned
#define LPP_DIRECTION 132           // 2 bytes, 1deg, unsigned
#define LPP_UNIXTIME 133            // 4 bytes, unsigned
#define LPP_GYROMETER 134           // 2 bytes per axis, 0.01 °/s
#define LPP_COLOUR 135              // 1 byte per RGB Color
#define LPP_GPS 136    // 3 byte lon/lat 0.0001 °, 3 bytes alt 0.01 meter
#define LPP_SWITCH 142 // 1 byte, 0/1

// Custom for ATLAS Types
#define LPP_ATLAS_PH                  90  // 4 bytes 0.001 signed
#define LPP_ATLAS_RTD                 91  // 4 bytes 0.001°C signed
#define LPP_ATLAS_DO                  92  // 2 bytes 0.01 mg/l unsigned
#define LPP_ATLAS_EC                  93  // 4 bytes 0.01 uS/cm signed

// Only Data Size
#define LPP_DIGITAL_INPUT_SIZE 1
#define LPP_DIGITAL_OUTPUT_SIZE 1
#define LPP_ANALOG_INPUT_SIZE 2
#define LPP_ANALOG_OUTPUT_SIZE 2
#define LPP_GENERIC_SENSOR_SIZE 4
#define LPP_LUMINOSITY_SIZE 2
#define LPP_PRESENCE_SIZE 1
#define LPP_TEMPERATURE_SIZE 2
#define LPP_RELATIVE_HUMIDITY_SIZE 1
#define LPP_ACCELEROMETER_SIZE 6
#define LPP_BAROMETRIC_PRESSURE_SIZE 2
#define LPP_VOLTAGE_SIZE 2
#define LPP_CURRENT_SIZE 2
#define LPP_FREQUENCY_SIZE 4
#define LPP_PERCENTAGE_SIZE 1
#define LPP_ALTITUDE_SIZE 2
#define LPP_POWER_SIZE 2
#define LPP_DISTANCE_SIZE 4
#define LPP_ENERGY_SIZE 4
#define LPP_DIRECTION_SIZE 2
#define LPP_UNIXTIME_SIZE 4
#define LPP_GYROMETER_SIZE 6
#define LPP_GPS_SIZE 9
#define LPP_SWITCH_SIZE 1
#define LPP_CONCENTRATION_SIZE 2
#define LPP_COLOUR_SIZE 3

// Custom for ATLAS
#define LPP_ATLAS_PH_SIZE               4
#define LPP_ATLAS_RTD_SIZE              4
#define LPP_ATLAS_DO_SIZE               2
#define LPP_ATLAS_EC_SIZE               4

// Multipliers
#define LPP_DIGITAL_INPUT_MULT 1
#define LPP_DIGITAL_OUTPUT_MULT 1
#define LPP_ANALOG_INPUT_MULT 100
#define LPP_ANALOG_OUTPUT_MULT 100
#define LPP_GENERIC_SENSOR_MULT 1
#define LPP_LUMINOSITY_MULT 1
#define LPP_PRESENCE_MULT 1
#define LPP_TEMPERATURE_MULT 10
#define LPP_RELATIVE_HUMIDITY_MULT 2
#define LPP_ACCELEROMETER_MULT 1000
#define LPP_BAROMETRIC_PRESSURE_MULT 10
#define LPP_VOLTAGE_MULT 100
#define LPP_CURRENT_MULT 1000
#define LPP_FREQUENCY_MULT 1
#define LPP_PERCENTAGE_MULT 1
#define LPP_ALTITUDE_MULT 1
#define LPP_POWER_MULT 1
#define LPP_DISTANCE_MULT 1000
#define LPP_ENERGY_MULT 1000
#define LPP_DIRECTION_MULT 1
#define LPP_UNIXTIME_MULT 1
#define LPP_GYROMETER_MULT 100
#define LPP_GPS_LAT_LON_MULT 10000
#define LPP_GPS_ALT_MULT 100
#define LPP_SWITCH_MULT 1
#define LPP_CONCENTRATION_MULT 1
#define LPP_COLOUR_MULT 1

// Cusstom for Atlas
#define LPP_ATLAS_PH_MULT               1000
#define LPP_ATLAS_RTD_MULT              1000
#define LPP_ATLAS_DO_MULT               100
#define LPP_ATLAS_EC_MULT               100

#define LPP_ERROR_OK 0
#define LPP_ERROR_OVERFLOW 1
#define LPP_ERROR_UNKOWN_TYPE 2

class CayenneLPP {

public:
  CayenneLPP(uint8_t size);
  ~CayenneLPP();

  void reset(void);
  uint8_t getSize(void);
  uint8_t *getBuffer(void);
  uint8_t copy(uint8_t *buffer);
  uint8_t getError();

  // Decoder methods
  const char *getTypeName(uint8_t type);
  uint8_t decode(uint8_t *buffer, uint8_t size, JsonArray &root);
  uint8_t decodeTTN(uint8_t *buffer, uint8_t size, JsonObject &root);

  // Original LPPv1 data types
#ifndef CAYENNE_DISABLE_DIGITAL_INPUT
  uint8_t addDigitalInput(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_DIGITAL_OUTPUT
  uint8_t addDigitalOutput(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_ANALOG_INPUT
  uint8_t addAnalogInput(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_ANALOG_OUTPUT
  uint8_t addAnalogOutput(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_LUMINOSITY
  uint8_t addLuminosity(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_PRESENCE
  uint8_t addPresence(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_TEMPERATURE
  uint8_t addTemperature(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_RELATIVE_HUMIDITY
  uint8_t addRelativeHumidity(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_ACCELEROMETER
  uint8_t addAccelerometer(uint8_t channel, float x, float y, float z);
#endif
#ifndef CAYENNE_DISABLE_BAROMETRIC_PRESSUE
  uint8_t addBarometricPressure(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_GYROMETER
  uint8_t addGyrometer(uint8_t channel, float x, float y, float z);
#endif
#ifndef CAYENNE_DISABLE_GPS
  uint8_t addGPS(uint8_t channel, float latitude, float longitude,
                 float altitude);
#endif

  // Additional data types
#ifndef CAYENNE_DISABLE_UNIX_TIME
  uint8_t addUnixTime(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_GENERIC_SENSOR
  uint8_t addGenericSensor(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_VOLTAGE
  uint8_t addVoltage(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_CURRENT
  uint8_t addCurrent(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_FREQUENCY
  uint8_t addFrequency(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_PERCENTAGE
  uint8_t addPercentage(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_ALTITUDE
  uint8_t addAltitude(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_POWER
  uint8_t addPower(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_DISTANCE
  uint8_t addDistance(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_ENERGY
  uint8_t addEnergy(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_DIRECTION
  uint8_t addDirection(uint8_t channel, float value);
#endif
#ifndef CAYENNE_DISABLE_SWITCH
  uint8_t addSwitch(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_CONCENTRATION
  uint8_t addConcentration(uint8_t channel, uint32_t value);
#endif
#ifndef CAYENNE_DISABLE_COLOUR
  uint8_t addColour(uint8_t channel, uint8_t r, uint8_t g, uint8_t b);
#endif

protected:
  bool isType(uint8_t type);
  uint8_t getTypeSize(uint8_t type);
  uint32_t getTypeMultiplier(uint8_t type);
  bool getTypeSigned(uint8_t type);

  float getValue(uint8_t *buffer, uint8_t size, uint32_t multiplier,
                 bool is_signed);
  uint32_t getValue32(uint8_t *buffer, uint8_t size);
  template <typename T>
  uint8_t addField(uint8_t type, uint8_t channel, T value);

  uint8_t *_buffer;
  uint8_t _maxsize;
  uint8_t _cursor;
  uint8_t _error = LPP_ERROR_OK;
};

#endif
