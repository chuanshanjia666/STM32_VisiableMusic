#include "myfft.h"

#include <malloc.h>

void MYFFT_Init(MYFFT_HandleTypeDef *hmyfft, uint32_t size)
{
    hmyfft->fft_size = size;
    hmyfft->input_signal = (float32_t *)malloc(size * sizeof(float32_t));
    hmyfft->ouput_signal_complex = (float32_t *)malloc(size * sizeof(float32_t));
    hmyfft->result = (float32_t *)malloc((size / 2) * sizeof(float32_t));
    arm_rfft_fast_init_f32(&(hmyfft->hfft), 1024);
}

void MYFFT_GetResult(MYFFT_HandleTypeDef *hmyfft)
{
    arm_rfft_fast_f32(&(hmyfft->hfft), hmyfft->input_signal, hmyfft->ouput_signal_complex, 0);
    arm_cmplx_mag_f32(hmyfft->ouput_signal_complex, hmyfft->result, 1024 / 2);
}

void MYFFT_DeInit(MYFFT_HandleTypeDef *hmyfft)
{
    if (hmyfft->input_signal)
    {
        free(hmyfft->input_signal);
        hmyfft->input_signal = NULL;
    }
    if (hmyfft->ouput_signal_complex)
    {
        free(hmyfft->ouput_signal_complex);
        hmyfft->ouput_signal_complex = NULL;
    }
    if (hmyfft->result)
    {
        free(hmyfft->result);
        hmyfft->result = NULL;
    }
    hmyfft->fft_size = 0;
}
