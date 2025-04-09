#include "main.h"
#include "st7735s.h"
#include "st7735s_cmdlist.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include "cmsis_os2.h"
#include "font.h"
void ST7735S_Init(ST7735S_HandleTypeDef *hst7735s,
                  SPI_HandleTypeDef *spi,
                  GPIO_TypeDef *dc_port,
                  uint16_t dc_pin,
                  GPIO_TypeDef *rst_port,
                  uint16_t rst_pin,
                  GPIO_TypeDef *blk_port,
                  uint16_t blk_pin,
                  uint16_t total_x_pixel,
                  uint16_t total_y_pixel)
{
    hst7735s->spi = spi;
    hst7735s->dc_port = dc_port;
    hst7735s->dc_pin = dc_pin;
    hst7735s->rst_port = rst_port;
    hst7735s->rst_pin = rst_pin;
    hst7735s->blk_port = blk_port;
    hst7735s->blk_pin = blk_pin;
    hst7735s->dc_mode = DC_MODE_UNKOWN;
    hst7735s->total_x_pixel = total_x_pixel;
    hst7735s->total_y_pixel = total_y_pixel;
    hst7735s->buff = (uint16_t *)malloc(2 * total_x_pixel * total_y_pixel);
}

void ST7735S_Reset(ST7735S_HandleTypeDef *hst7735s)
{
    HAL_GPIO_WritePin(hst7735s->rst_port, hst7735s->rst_pin, GPIO_PIN_RESET);
    osDelay(50);
    HAL_GPIO_WritePin(hst7735s->rst_port, hst7735s->rst_pin, GPIO_PIN_SET);
    osDelay(50);
}
void ST7735S_BlacklightOn(ST7735S_HandleTypeDef *hst7735s)
{
    HAL_GPIO_WritePin(hst7735s->blk_port, hst7735s->blk_pin, GPIO_PIN_SET);
}

void ST7735S_BlacklightOff(ST7735S_HandleTypeDef *hst7735s)
{
    HAL_GPIO_WritePin(hst7735s->blk_port, hst7735s->blk_pin, GPIO_PIN_RESET);
}

void ST7735S_SendData(ST7735S_HandleTypeDef *hst7735s, uint8_t *data, uint16_t size)
{
    if (hst7735s->dc_mode != DC_MODE_DATA)
        HAL_GPIO_WritePin(hst7735s->dc_port, hst7735s->dc_pin, GPIO_PIN_SET); // DC = 1 for data
    HAL_SPI_Transmit(hst7735s->spi, data, size, HAL_MAX_DELAY);
}

void ST7735S_SendCommand(ST7735S_HandleTypeDef *hst7735s, uint8_t cmd)
{
    if (hst7735s->dc_mode != DC_MODE_CMMAND)
        HAL_GPIO_WritePin(hst7735s->dc_port, hst7735s->dc_pin, GPIO_PIN_RESET); // DC = 0 for command
    HAL_SPI_Transmit(hst7735s->spi, &cmd, 1, HAL_MAX_DELAY);
}

void ST7735S_SendDataDMA(ST7735S_HandleTypeDef *hst7735s, uint8_t *data, uint16_t size)
{
    if (hst7735s->dc_mode != DC_MODE_DATA)
        HAL_GPIO_WritePin(hst7735s->dc_port, hst7735s->dc_pin, GPIO_PIN_SET);
    while ((HAL_DMA_GetState(hst7735s->spi->hdmatx) != HAL_DMA_STATE_READY))
        ;
    HAL_SPI_Transmit_DMA(hst7735s->spi, data, size);
}

void ST7735S_LCD_Init(ST7735S_HandleTypeDef *hst7735s)
{

    // ST7735S_Reset(hst7735s);
    // ST7735S_SendCommand(hst7735s, LCD_SLPOUT);
    // osDelay(120);

    // //===============frame set========================
    // // Frame rate = fosc / ((RTNA x 2 + 40) x (LINE + FPA + BPA +2))
    // //	lcd_write(TFT_CMD, LCD_FRMCTR1);
    // //	lcd_write(TFT_DATA, 0x02);
    // //	lcd_write(TFT_DATA, 0x35);
    // //	lcd_write(TFT_DATA, 0x36);
    // //
    // //	lcd_write(TFT_CMD, LCD_FRMCTR2);
    // //	lcd_write(TFT_DATA, 0x02);
    // //	lcd_write(TFT_DATA, 0x35);
    // //	lcd_write(TFT_DATA, 0x36);
    // //
    // //	lcd_write(TFT_CMD, LCD_FRMCTR3);
    // //	lcd_write(TFT_DATA, 0x02);
    // //	lcd_write(TFT_DATA, 0x35);
    // //	lcd_write(TFT_DATA, 0x36);
    // //	lcd_write(TFT_DATA, 0x02);
    // //	lcd_write(TFT_DATA, 0x35);
    // //	lcd_write(TFT_DATA, 0x36);

    // ST7735S_SendCommand(hst7735s, LCD_FRMCTR1);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x01, 0x2C, 0x2D}, 3);

    // ST7735S_SendCommand(hst7735s, LCD_FRMCTR2);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x01, 0x2C, 0x2D}, 3);

    // ST7735S_SendCommand(hst7735s, LCD_FRMCTR3);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D}, 6);

    // //===============inversion of control=============
    // ST7735S_SendCommand(hst7735s, LCD_INVCRT);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x03}, 1);

    // //===============power set========================

    // ST7735S_SendCommand(hst7735s, LCD_PWCTR1);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0xA2, 0x02, 0x84}, 3);

    // ST7735S_SendCommand(hst7735s, LCD_PWCTR2);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0xC5}, 1);

    // ST7735S_SendCommand(hst7735s, LCD_PWCTR3);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x0D, 0x00}, 2);

    // ST7735S_SendCommand(hst7735s, LCD_PWCTR4);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x8D, 0x2A}, 2);

    // ST7735S_SendCommand(hst7735s, LCD_PWCTR5);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x8D, 0xEE}, 2);

    // //===============vcom set=========================
    // ST7735S_SendCommand(hst7735s, LCD_VMCTR1);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x03}, 1);

    // //===============color format set=================
    // ST7735S_SendCommand(hst7735s, LCD_COLMOD);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x05}, 1);

    // //===============scanning direction set===========
    // ST7735S_SendCommand(hst7735s, LCD_MADCTL);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x08}, 1); // 0x08 = 0b00001000, RGB order, bottom to top, left to right
    // // 0xC8 = 0b11001000, RGB order, top to bottom, left to right

    // //===============gamma sequence set===============
    // ST7735S_SendCommand(hst7735s, LCD_GMCTRP1);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x12, 0x1C, 0x10, 0x18, 0x33, 0x2C, 0x25, 0x28, 0x28, 0x27, 0x2F, 0x3C, 0x00, 0x03, 0x03, 0x10}, 16);

    // ST7735S_SendCommand(hst7735s, LCD_GMCTRN1);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x12, 0x1C, 0x10, 0x18, 0x2D, 0x28, 0x23, 0x28, 0x28, 0x26, 0x2F, 0x3B, 0x00, 0x03, 0x03, 0x10}, 16);

    // //===============partial area set=================

    // ST7735S_SendCommand(hst7735s, LCD_PTLAR);
    // ST7735S_SendData(hst7735s, (uint8_t[]){0x00, 0x00, 0x00, 0x80}, 4);

    // //===============partial mode on==================
    // ST7735S_SendCommand(hst7735s, LCD_PTLON);

    // //===============display on=======================
    // ST7735S_SendCommand(hst7735s, LCD_DISPON);

    // 硬件复位
    ST7735S_Reset(hst7735s);

    // 退出睡眠模式
    ST7735S_SendCommand(hst7735s, 0x11);
    osDelay(240);

    // 帧率控制
    ST7735S_SendCommand(hst7735s, 0xB1);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x01, 0x2C, 0x2D}, 3);

    ST7735S_SendCommand(hst7735s, 0xB2);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x01, 0x2C, 0x2D}, 3);

    ST7735S_SendCommand(hst7735s, 0xB3);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D}, 6);

    // 列反转控制
    ST7735S_SendCommand(hst7735s, 0xB4);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x07}, 1);

    // 电源控制序列
    ST7735S_SendCommand(hst7735s, 0xC0);
    ST7735S_SendData(hst7735s, (uint8_t[]){0xA2, 0x02, 0x84}, 3);

    ST7735S_SendCommand(hst7735s, 0xC1);
    ST7735S_SendData(hst7735s, (uint8_t[]){0xC5}, 1);

    ST7735S_SendCommand(hst7735s, 0xC2);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x0A, 0x00}, 2);

    ST7735S_SendCommand(hst7735s, 0xC3);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x8A, 0x2A}, 2);

    ST7735S_SendCommand(hst7735s, 0xC4);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x8A, 0xEE}, 2);

    // VCOM 控制
    ST7735S_SendCommand(hst7735s, 0xC5);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x0E}, 1);

    // 扫描方向设置 (MX, MY, RGB)
    ST7735S_SendCommand(hst7735s, 0x36);
    ST7735S_SendData(hst7735s, (uint8_t[]){0xC0}, 1);

    // Gamma 校正正极性
    ST7735S_SendCommand(hst7735s, 0xE0);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x0F, 0x1A, 0x0F, 0x18, 0x2F, 0x28, 0x20, 0x22, 0x1F, 0x1B, 0x23, 0x37, 0x00, 0x07, 0x02, 0x10}, 16);

    // Gamma 校正负极性
    ST7735S_SendCommand(hst7735s, 0xE1);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x0F, 0x1B, 0x0F, 0x17, 0x33, 0x2C, 0x29, 0x2E, 0x30, 0x30, 0x39, 0x3F, 0x00, 0x07, 0x03, 0x10}, 16);

    // 列地址设置 (0-127)
    ST7735S_SendCommand(hst7735s, 0x2A);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, 0x00, 0x00, 0x7F}, 4);

    // 行地址设置 (0-159)
    ST7735S_SendCommand(hst7735s, 0x2B);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, 0x00, 0x00, 0x9F}, 4);

    // 使能测试命令
    ST7735S_SendCommand(hst7735s, 0xF0);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x01}, 1);

    // 关闭 RAM 节电模式
    ST7735S_SendCommand(hst7735s, 0xF6);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00}, 1);

    // 设置颜色模式 (16-bit/pixel)
    ST7735S_SendCommand(hst7735s, 0x3A);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x05}, 1);

    // 打开显示
    ST7735S_SendCommand(hst7735s, 0x29);

    // 开启背光
    ST7735S_BlacklightOn(hst7735s);
}

void ST7735S_ShowPointNoBuff(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, ST7735S_ColorTypeDef color)
{
    ST7735S_SendCommand(hst7735s, LCD_CASET);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, x, 0x00, x + 1}, 4);
    ST7735S_SendCommand(hst7735s, LCD_RASET);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, y, 0x00, y + 1}, 4);
    ST7735S_SendCommand(hst7735s, LCD_RAMWR);
    ST7735S_SendData(hst7735s, (uint8_t *)&color, 2);
}

uint16_t uint16L_To_uint16H(uint16_t num)
{
    return (num & 0xFF00) >> 8 | (num & 0x00FF) << 8;
}

void ST7735S_WriteBlock(ST7735S_HandleTypeDef *hst7735s, ST7735S_ColorTypeDef color)
{
    // 大小端问题：！！！
    size_t size = hst7735s->total_x_pixel * hst7735s->total_y_pixel;
    uint16_t *buff = hst7735s->buff;
    __asm volatile(
        "mov r0, %[buff]          \n" // 加载缓冲区地址到r0
        "mov r1, %[size]          \n" // 加载像素数量到r1
        "mov r2, %[color]         \n" // 加载颜色值到r2
        "lsr r3, r2, #8           \n" // 提取高八位到r3 (color >> 8)
        "ST7735_ShowBlockloop:    \n"
        "strb r3, [r0], #1        \n" // 存储高八位并指针+1
        "strb r2, [r0], #1        \n" // 存储低八位并指针+1
        "subs r1, r1, #1          \n" // 计数器减1
        "bne ST7735_ShowBlockloop \n" // 循环直到计数器为0
        :
        : [buff] "r"(buff), [size] "r"(size), [color] "r"(color)
        : "r0", "r1", "r2", "r3", "memory");
}

void ST7735S_FlushBuffDMA(ST7735S_HandleTypeDef *hst7735s)
{
    ST7735S_SendCommand(hst7735s, LCD_CASET);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, 0x00, 0x00, 127}, 4);
    ST7735S_SendCommand(hst7735s, LCD_RASET);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, 0x00, 0x00, 159}, 4);
    ST7735S_SendCommand(hst7735s, LCD_RAMWR);
    if (hst7735s->dc_mode != DC_MODE_DATA)
        HAL_GPIO_WritePin(hst7735s->dc_port, hst7735s->dc_pin, GPIO_PIN_SET);
    while ((HAL_DMA_GetState(hst7735s->spi->hdmatx) != HAL_DMA_STATE_READY))
        ;
    HAL_SPI_Transmit_DMA(hst7735s->spi, (uint8_t *)hst7735s->buff, 2 * hst7735s->total_x_pixel * hst7735s->total_y_pixel);
}

void ST7735S_WriteBuffPoint(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, ST7735S_ColorTypeDef color)
{
    if (x >= hst7735s->total_x_pixel || y >= hst7735s->total_y_pixel)
        return;

    hst7735s->buff[y * hst7735s->total_x_pixel + x] = uint16L_To_uint16H(color);
}

void ST7735S_ShowChar(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, char c, ST7735S_ColorTypeDef color)
{
    if (x >= hst7735s->total_x_pixel || y >= hst7735s->total_y_pixel)
        return;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((g_f8X16[16 * (c - 0x20) + i] >> j) & 0x01)
                ST7735S_WriteBuffPoint(hst7735s, x + j, y + i, color);
        }
    }
}

void ST7735S_ShowString(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, char *str, ST7735S_ColorTypeDef color)
{
    while (*str != '\0')
    {
        ST7735S_ShowChar(hst7735s, x, y, *str, color);
        str++;
        x += 8;
    }
}

uint16_t ST7735S_RGB565Map(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (0x1F & b);
}

uint16_t ST7735S_RGB888ToRGB565(uint32_t rgb888)
{
    uint8_t r = (rgb888 >> 16) & 0xFF;
    uint8_t g = (rgb888 >> 8) & 0xFF;
    uint8_t b = rgb888 & 0xFF;
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void ST7735S_Printf(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, ST7735S_ColorTypeDef color, const char *__format, ...)
{
    va_list args;
    va_start(args, __format);
    char buffer[128];
    vsnprintf(buffer, sizeof(buffer), __format, args);
    va_end(args);
    ST7735S_ShowString(hst7735s, x, y, buffer, color);
}

void ST7735S_DrawLine(ST7735S_HandleTypeDef *hst7735s, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, ST7735S_ColorTypeDef color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        ST7735S_WriteBuffPoint(hst7735s, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int err2 = err * 2;
        if (err2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void ST7735S_DrawLineRight(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, uint8_t length, ST7735S_ColorTypeDef color)
{
    if (y >= hst7735s->total_y_pixel || x >= hst7735s->total_x_pixel)
        return;

    for (uint8_t i = 0; i < length; i++)
    {
        if (x + i >= hst7735s->total_x_pixel)
            break;
        ST7735S_WriteBuffPoint(hst7735s, x + i, y, color);
    }
}

void ST7735S_DrawLineDown(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, uint8_t length, ST7735S_ColorTypeDef color)
{
    if (x >= hst7735s->total_x_pixel || y >= hst7735s->total_y_pixel)
        return;

    for (uint8_t i = 0; i < length; i++)
    {
        if (y + i >= hst7735s->total_y_pixel)
            break;
        ST7735S_WriteBuffPoint(hst7735s, x, y + i, color);
    }
}

void ST7735S_DrawLineUp(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, uint8_t length, ST7735S_ColorTypeDef color)
{
    if (x >= hst7735s->total_x_pixel || y >= hst7735s->total_y_pixel)
        return;

    for (uint8_t i = 0; i < length; i++)
    {
        if (y < i)
            break;
        ST7735S_WriteBuffPoint(hst7735s, x, y - i, color);
    }
}

void ST7735S_DrawLineLeft(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, uint8_t length, ST7735S_ColorTypeDef color)
{
    if (y >= hst7735s->total_y_pixel || x >= hst7735s->total_x_pixel)
        return;

    for (uint8_t i = 0; i < length; i++)
    {
        if (x < i)
            break;
        ST7735S_WriteBuffPoint(hst7735s, x - i, y, color);
    }
}