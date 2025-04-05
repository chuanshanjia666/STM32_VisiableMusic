#pragma once
#include "arm_math.h"
typedef struct MYFFT_HandleTypeDef
{
    arm_rfft_fast_instance_f32 hfft;
    uint32_t fft_size;
    float32_t *input_signal;
    float32_t *ouput_signal_complex;
    float32_t *result;
} MYFFT_HandleTypeDef;

void MYFFT_Init(MYFFT_HandleTypeDef *hmyfft, uint32_t size);
void MYFFT_GetResult(MYFFT_HandleTypeDef *hmyfft);
void MYFFT_DeInit(MYFFT_HandleTypeDef *hmyfft);