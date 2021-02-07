/*
  ==============================================================================

    Engine.h
    Created: 7 Feb 2021 12:08:55pm
    Author:  Dominik

  ==============================================================================
*/

#pragma once

#define ABS(input) (float)(input > 0.0f ? input : -input)
#define PI (3.141592f)
#define FIR_MAX_LEN 1000

class IIR_filter
{
public:
    IIR_filter();
    float processing(float input, float* IN_coeffs, float* OUT_coeffs);
    void setVolume(float value);
    float getVolume(void);

    float volume = 1.0;

private:
    float IN_buffer[5] = { 0 };
    float OUT_buffer[5] = { 0 };
};

class FIR
{
public:
    FIR::FIR();
    float processing(float input, float* IR, unsigned int IR_len);

private:
    float buffer[FIR_MAX_LEN * 2] = { 0 };
    unsigned int buffIndex = 0;
};

class Nonlinear
{
public:
    Nonlinear();
    float processing(float input);

    void init(float(*characteristic)[2U], unsigned int set_size);
    void recalc(void);
    void setAmpli(float ampli);
    void setBias(float bias);
    float getBias(void);
    float getAmpli(void);

    unsigned int size;
    float amp;
    float bias;

    float step;
    float gain_tab[100];
    float norm;

    float Input_min;
    float Input_max;

    unsigned int GainLimit_alert;
    unsigned int BiasLimit_alert;
    unsigned int AmpliLimit_alert;
};
