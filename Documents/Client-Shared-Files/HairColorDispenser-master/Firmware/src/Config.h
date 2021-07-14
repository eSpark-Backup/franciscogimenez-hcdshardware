#ifndef CONFIG_H
#define CONFIG_H

// LOADCELL configuration
#define LOADCELL_CALIBRATION_NUMBER     2280.f
#define LOADCELL_NUMBER_OF_READS        10
#define LOADCELL_EEPROM_ADDRESS         0


#define EEPROM_SIZE 64

// Servo configuration
#define SERVO_FIRE_PIN_MAX              180
#define SERVO_FIRE_PIN_MIN              0

// Optical sensor
#define OPTICAL_SENSOR_TRESHOLD         1245

// NeoPixel WS2812B configuration
#define NEOPIXEL_NUMBER_OF_RGBS         16


// uncomment to send debug info to serial monitor
#define SHOW_DEBUG
#ifdef SHOW_DEBUG
    #define THINGSPEAK_DEBUG
    #define PH_SENSOR_DEBUG
    #define WATER_TEMPERATURE_DEBUG
    #define TDS_SENSOR_DEBUG
    #define AIR_HUMIDITY_TEMP_DEBUG
#endif

#endif // CONFIG_H