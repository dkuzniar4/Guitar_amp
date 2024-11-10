/*
  ==============================================================================

    Engine.cpp
    Created: 7 Feb 2021 12:08:42pm
    Author:  Dominik Kuzniar / dkuzniar4

  ==============================================================================
*/

#include "Engine.h"
#include "math.h"
#include <cstring>
#include "kernels.h"

IIR_filter::IIR_filter()
{
    //todo
}

float IIR_filter::processing(float input, float* IN_coeffs, float* OUT_coeffs)
{
    float output = 0.0f;

    IN_buffer[4] = IN_buffer[3];
    IN_buffer[3] = IN_buffer[2];
    IN_buffer[2] = IN_buffer[1];
    IN_buffer[1] = IN_buffer[0];
    IN_buffer[0] = input;

    output = IN_buffer[0] * IN_coeffs[0];
    output += IN_buffer[1] * IN_coeffs[1];
    output += IN_buffer[2] * IN_coeffs[2];
    output += IN_buffer[3] * IN_coeffs[3];
    output += IN_buffer[4] * IN_coeffs[4];

    output += -OUT_buffer[0] * OUT_coeffs[1];
    output += -OUT_buffer[1] * OUT_coeffs[2];
    output += -OUT_buffer[2] * OUT_coeffs[3];
    output += -OUT_buffer[3] * OUT_coeffs[4];


    OUT_buffer[4] = OUT_buffer[3];
    OUT_buffer[3] = OUT_buffer[2];
    OUT_buffer[2] = OUT_buffer[1];
    OUT_buffer[1] = OUT_buffer[0];
    OUT_buffer[0] = output;

    return output * volume;
}

void IIR_filter::setVolume(float value)
{
    volume = value;
}

float IIR_filter::getVolume(void)
{
    return volume;
}

RingBuffer::RingBuffer()
{
    this->bufferIdx = 0;
    this->bufferSize = RB_SIZE;
    memset(this->buffer, 0, sizeof(this->buffer));
}

RingBuffer::~RingBuffer()
{

}

void RingBuffer::putDataToBuffer(float data)
{
    buffer[bufferIdx] = data;
    bufferIdx++;
    if (bufferIdx >= bufferSize)
    {
        bufferIdx = 0;
    }
}

float RingBuffer::getDataFromBuffer(int n_samples)
{
    int delay = bufferIdx - n_samples - 1;

    if (delay >= 0)
    {
        return buffer[delay];
    }
    else
    {
        return buffer[bufferSize + delay];
    }
}

FIR::FIR()
{

}

float FIR::processing(float input, float* IR, unsigned int IR_len)
{
    rbuff.putDataToBuffer(input);

    float sum = 0.0;
    for (auto i = 0; i < IR_len; i++)
    {
        sum += IR[i] * rbuff.getDataFromBuffer(i);
    }

    return sum;
}

Nonlinear::Nonlinear()
{
    //todo
}

void Nonlinear::init(float(*characteristic)[2U], unsigned int set_size)
{
    size = set_size;
    Input_min = characteristic[0][0];
    Input_max = characteristic[size - 1][0];
    step = -characteristic[1][0] - (-characteristic[0][0]);

    // calculating gain tab
    for (unsigned int i = 0U; i < size; i++)
    {
        gain_tab[i] = (characteristic[i][1]) / -characteristic[i][0];
    }

    // looking for the absolute maximum
    float max = ABS(gain_tab[0]);
    for (unsigned int i = 1; i < size; i++)
    {
        if (ABS(gain_tab[i]) > max)
        {
            max = ABS(gain_tab[i]);
        }
    }

    // normalisation to 1
    for (unsigned int i = 0; i < size; i++)
    {
        gain_tab[i] /= max;
    }
}

void Nonlinear::setBias(float value)
{
    bias = value;
}

void Nonlinear::setAmpli(float value)
{
    amp = value;
}

float Nonlinear::getBias(void)
{
    return bias;
}

float Nonlinear::getAmpli(void)
{
    return amp;
}

float Nonlinear::processing(float input)
{
    float address;
    float prop;
    float gain;
    float in;
    unsigned int index;

    in = input;

    in *= amp;
    in += bias;

    address = (in / step) - 1U;
    index = floor(address);
    prop = address - index;
    if (index >= (size - 1U))
    {
        gain = gain_tab[size - 1U];
    }
    else if (index < 0)
    {
        index = 0;
    }
    else
    {
        gain = (prop * (gain_tab[index + 1U] - gain_tab[index])) + gain_tab[index];
    }
    return input * gain;
}

Amp::Amp()
{
    setInputVolume(0.5);
    setMasterVolume(4.0);

    setBassVolume(10.0);
    setMidVolume(10.0);
    setTrebleVolume(10.0);

    tube.init(_12AX7_transfer, 9);
    tube.setBias(1.2);
    tube.setAmpli(0.1);

    setAmpState(1);
    setCabState(1);
    setFilterState(1);
    setTubeState(1);
}

float Amp::processing(float input)
{
    float signal = input;
    float signal_bass;
    float signal_mid;
    float signal_treble;

    signal *= inputVolume;

    if (amp_state == 1)
    {
        if (filter_state == 1)
        {
            signal_bass = bass_filter.processing(signal, IN_bass, OUT_bass);
            signal_mid = mid_filter.processing(signal, IN_mid, OUT_mid);
            signal_treble = treble_filter.processing(signal, IN_treble, OUT_treble);
            signal = signal_bass + signal_mid + signal_treble;
        }

        if (tube_state == 1)
        {
            signal = tube.processing(signal);
        }

        if (cab_state == 1)
        {
            signal = cabinet.processing(signal, cab_IR, 427);
        }
    }

    signal *= masterVolume;

    return signal;
}

void Amp::setBassVolume(float value)
{
    bass_filter.setVolume(value);
}

void Amp::setMidVolume(float value)
{
    mid_filter.setVolume(value);
}

void Amp::setTrebleVolume(float value)
{
    treble_filter.setVolume(value);
}

void Amp::setAmp(float value)
{
    tube.setAmpli(value);
}

void Amp::setBias(float value)
{
    tube.setBias(value);
}

void Amp::setInputVolume(float value)
{
    inputVolume = value;
}

void Amp::setMasterVolume(float value)
{
    masterVolume = value;
}

float Amp::getInputVolume(void)
{
    return inputVolume;
}

float Amp::getMasterVolume(void)
{
    return masterVolume;
}

float Amp::getBassVolume(void)
{
    return bass_filter.getVolume();
}

float Amp::getMidVolume(void)
{
    return mid_filter.getVolume();
}

float Amp::getTrebleVolume(void)
{
    return treble_filter.getVolume();
}

float Amp::getAmp(void)
{
    return tube.getAmpli();
}

float Amp::getBias(void)
{
    return tube.getBias();
}

int Amp::getAmpState(void)
{
    return amp_state;
}

int Amp::getCabState(void)
{
    return cab_state;
}

int Amp::getFilterState(void)
{
    return filter_state;
}

int Amp::getTubeState(void)
{
    return tube_state;
}

void Amp::setAmpState(int value)
{
    amp_state = value;
}

void Amp::setCabState(int value)
{
    cab_state = value;
}

void Amp::setFilterState(int value)
{
    filter_state = value;
}

void Amp::setTubeState(int value)
{
    tube_state = value;
}
