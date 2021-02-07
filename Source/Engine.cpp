/*
  ==============================================================================

    Engine.cpp
    Created: 7 Feb 2021 12:08:42pm
    Author:  Dominik

  ==============================================================================
*/

#include "Engine.h"
#include "math.h"

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

FIR::FIR()
{
    buffIndex = 0;
}

float FIR::processing(float input, float* IR, unsigned int IR_len)
{
    buffer[buffIndex] = input;
    buffer[buffIndex + IR_len] = input;

    float sum = 0.0;
    for (auto i = 0; i < IR_len; i++)
    {
        sum += IR[i] * buffer[buffIndex + IR_len - i];
    }

    buffIndex++;
    if (buffIndex >= IR_len)
    {
        buffIndex = 0;
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
    step = characteristic[1][0] - characteristic[0][0];

    for (unsigned int i = 0U; i < size; i++)
    {
        gain_tab[i] = (characteristic[i][1] * 0.001f * 8) / characteristic[i][0];
    }
}

void Nonlinear::setBias(float value)
{
    if (value < Input_min)
    {
        BiasLimit_alert = 1;
        bias = Input_min + 0.05f;
    }
    else if (value > Input_max)
    {
        BiasLimit_alert = 1;
        bias = Input_max - 0.05f;
    }
    else
    {
        BiasLimit_alert = 0;
        bias = value;
    }

    if ((bias - amp) < Input_min)
    {
        AmpliLimit_alert = 1;
        amp = bias - Input_min;
    }
    else if ((bias + amp) > Input_max)
    {
        AmpliLimit_alert = 1;
        amp = Input_max - bias;
    }
}

void Nonlinear::setAmpli(float value)
{
    if (value > (bias - Input_min))
    {
        AmpliLimit_alert = 1;
        amp = bias - Input_min;
    }
    else if (value > (Input_max - bias))
    {
        AmpliLimit_alert = 1;
        amp = Input_max - bias;
    }
    else
    {
        AmpliLimit_alert = 0;
        amp = value;
    }
}

void Nonlinear::recalc(void)
{
    float f_low, f_high;
    unsigned int i_low, i_high;

    f_low = ((bias - amp) / step) - 1U;
    i_low = floor(f_low);

    f_high = ((bias + amp) / step) - 1U;
    i_high = floor(f_high);

    float max = gain_tab[i_low];

    for (unsigned int i = (i_low + 1); i < i_high; i++)
    {
        if (gain_tab[i] > max)
        {
            max = gain_tab[i];
        }
    }

    norm = 1.0f / max;
}

float Nonlinear::processing(float input)
{
    float address;
    float prop;
    float gain;
    float in;
    unsigned int index;

    in = input;

    in *= this->amp;
    in += this->bias;

    address = (in / step) - 1U;
    index = floor(address);
    prop = address - index;
    if (index >= (size - 1U))
    {
        gain = gain_tab[size - 1U];
        GainLimit_alert = 1;
    }
    else if (index < 0)
    {
        index = 0;
        GainLimit_alert = 1;
    }
    else
    {
        gain = (prop * (gain_tab[index + 1U] - gain_tab[index])) + gain_tab[index];
        GainLimit_alert = 0;
    }
    return input * gain * norm;
}

float Nonlinear::getBias(void)
{
    return bias;
}

float Nonlinear::getAmpli(void)
{
    return amp;
}