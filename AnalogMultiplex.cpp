//#define DEBUG 0

#include "AnalogMultiplex.h"


AnalogMultiplex::AnalogMultiplex(int s0_pin, int s1_pin,
                                 int s2_pin, int z_pin):
    _s0_pin(s0_pin), _s1_pin(s1_pin), _s2_pin(s2_pin), _z_pin(z_pin)
{
#ifdef DEBUG
    Serial.println("beginig multiplexer");
#endif
    for(int i = 0; i < CONTROL_PINS_NUM; i++)
    {
        pinMode(control_pins[i], OUTPUT);
        digitalWrite(control_pins[i], LOW);
    }
}

AnalogMultiplex::AnalogMultiplex(int s0_pin, int s1_pin,
                                 int s2_pin):
    _s0_pin(s0_pin), _s1_pin(s1_pin), _s2_pin(s2_pin)
{
    _z_pin = 0;
    #ifdef DEBUG
    Serial.println("beginig multiplexer");
    #endif
}

void AnalogMultiplex::preparePins()
{
    #ifdef DEBUG
    Serial.println("beginig multiplexer");
    #endif
    for(int i = 0; i < CONTROL_PINS_NUM; i++)
    {
        pinMode(control_pins[i], OUTPUT);
        digitalWrite(control_pins[i], LOW);
    }
}


int AnalogMultiplex::readChannel(int channel)
{
#ifdef DEBUG
    Serial.println("Reading: " + String(channel));
#endif
    for(int i = 0; i < CONTROL_PINS_NUM; i++)
    {
        digitalWrite(control_pins[i], multiplexer_channels[channel][i]);
        #ifdef DEBUG
        Serial.print(multiplexer_channels[channel][i]);
        Serial.print(digitalRead(control_pins[i]));
       #endif
    }
    int channel_val = analogRead(_z_pin);
    #ifdef DEBUG
    Serial.println("channel val is: " + String(channel_val));
    #endif
    return channel_val;
}


void AnalogMultiplex::readAllChannels(int *destArray)
{
    int channels_val[8];
    for(int channel = 0; channel < 8; channel++)
    {
        for(int maxVal = 0; maxVal < 3; maxVal++)
        {
            digitalWrite(control_pins[maxVal], multiplexer_channels[channel][maxVal]);
        }
        int channelVal = analogRead(_z_pin);
        *(destArray + channel) = channelVal;
    }
}

float AnalogMultiplex::convertToVolts(int analog_value)
{
    float voltage = (analog_value * 5.0) / 1024.0;
    return voltage;
}
