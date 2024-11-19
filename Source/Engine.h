/*
  ==============================================================================

    Engine.h
    Created: 7 Feb 2021 12:08:55pm
    Author:  Dominik Kuzniar / dkuzniar4

  ==============================================================================
*/

#pragma once

#define ABS(input) (float)(input > 0.0f ? input : -input)
#define PI (3.141592f)
#define RB_SIZE 1000

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

class RingBuffer
{
public:
    RingBuffer();
    ~RingBuffer();
    void putDataToBuffer(float data);
    float getDataFromBuffer(int n_samples);

private:
    float buffer[RB_SIZE];
    int bufferIdx;
    int bufferSize;
};

class FIR
{
public:
    FIR();
    float processing(float input, float* IR, unsigned int IR_len);

private:
    RingBuffer rbuff;
};

class Nonlinear
{
public:
    Nonlinear();
    float processing(float input);

    void init(float(*characteristic)[2U], unsigned int set_size);
    void setAmpli(float ampli);
    void setBias(float bias);
    float getBias(void);
    float getAmpli(void);

private:
    unsigned int size;
    float amp;
    float bias;

    float step;
    float gain_tab[100];
    float norm;

    float Input_min;
    float Input_max;
};

class Amp
{
public:
    Amp();
    float processing(float input);

    void setBassVolume(float value);
    void setMidVolume(float value);
    void setTrebleVolume(float value);
    void setAmp(float value);
    void setBias(float value);
    void setInputVolume(float value);
    void setMasterVolume(float value);

    float getBassVolume(void);
    float getMidVolume(void);
    float getTrebleVolume(void);
    float getAmp(void);
    float getBias(void);
    float getInputVolume(void);
    float getMasterVolume(void);

    void setAmpState(int value);
    void setCabState(int value);
    void setFilterState(int value);
    void setTubeState(int value);

    int getAmpState(void);
    int getCabState(void);
    int getFilterState(void);
    int getTubeState(void);


private:
    IIR_filter bass_filter;
    IIR_filter mid_filter;
    IIR_filter treble_filter;

    FIR cabinet;

    Nonlinear tube;

    float inputVolume = 1.0;
    float masterVolume = 1.0;

    int amp_state;
    int cab_state;
    int filter_state;
    int tube_state;
};
