#include "Arduino.h"

#ifndef ANALOGMULTIPLEX_H
#define ANALOGMULTIPLEX_H

const int CONTROL_PINS_NUM = 3;

class AnalogMultiplex
{
public:
    AnalogMultiplex(int s0_pin, int s1_pin, int s2_pin);
    AnalogMultiplex(int s0_pin, int s1_pin, int s2_pin, int z_pin);
    void preparePins();
    void setZPin(int z) { _z_pin = z; }
    int getZPin() { return _z_pin; }
    int readChannel(int channel);
    void readAllChannels(int *destArray);
    float convertToVolts(int analog_value);

private:
    int _s0_pin;
    int _s1_pin;
    int _s2_pin;
    int _z_pin;
    int control_pins[3] = {_s0_pin, _s1_pin, _s2_pin};
    int multiplexer_channels[8][3] = {
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 1},
    };
};

#endif // ANALOGMULTIPLEX_H
