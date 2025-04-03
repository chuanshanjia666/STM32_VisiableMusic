#include "main.h"
#include "spi.h"
#include "st7735s.h"
#include "gpio.h"
#include "st7735s_cmdlist.h"

void ST7735S_Init(ST7735S_HandleTypeDef *hst7735s,
                  SPI_HandleTypeDef *spi,
                  GPIO_TypeDef *dc_port,
                  uint16_t dc_pin,
                  GPIO_TypeDef *rst_port,
                  uint16_t rst_pin,
                  GPIO_TypeDef *blk_port,
                  uint16_t blk_pin)
{
    hst7735s->spi = spi;
    hst7735s->dc_port = dc_port;
    hst7735s->dc_pin = dc_pin;
    hst7735s->rst_port = rst_port;
    hst7735s->rst_pin = rst_pin;
    hst7735s->blk_port = blk_port;
    hst7735s->blk_pin = blk_pin;
    hst7735s->dc_mode = DC_MODE_UNKOWN;
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

void ST7735_ShowPoint(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, ST7735S_ColorTypeDef color)
{
    ST7735S_SendCommand(hst7735s, LCD_CASET);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, x, 0x00, x + 1}, 4);
    ST7735S_SendCommand(hst7735s, LCD_RASET);
    ST7735S_SendData(hst7735s, (uint8_t[]){0x00, y, 0x00, y + 1}, 4);
    ST7735S_SendCommand(hst7735s, LCD_RAMWR);
    ST7735S_SendData(hst7735s, (uint8_t *)&color, 2);
}

void ST7735S_ShowChar(ST7735S_HandleTypeDef *hst7735s)
{
}