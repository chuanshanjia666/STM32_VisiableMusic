#pragma once
typedef enum
{
    ST7735S_COLOR_BLACK = 0x0000,
    ST7735S_COLOR_BLUE = 0x001F,
    ST7735S_COLOR_RED = 0xF800,
    ST7735S_COLOR_GREEN = 0x07E0,
    ST7735S_COLOR_CYAN = 0x07FF,
    ST7735S_COLOR_MAGENTA = 0xF81F,
    ST7735S_COLOR_YELLOW = 0xFFE0,
    ST7735S_COLOR_WHITE = 0xFFFF,
} ST7735S_ColorTypeDef;

typedef enum
{
    ST7735S_CMD_NOP = 0x00,
    ST7735S_CMD_SWRESET = 0x01,
    ST7735S_CMD_RDDID = 0x04,
    ST7735S_CMD_RDDST = 0x09,
    ST7735S_CMD_SLPIN = 0x10,
    ST7735S_CMD_SLPOUT = 0x11,
    ST7735S_CMD_PTLON = 0x12,
    ST7735S_CMD_NORON = 0x13,
    ST7735S_CMD_INVOFF = 0x20,
    ST7735S_CMD_INVON = 0x21,
    ST7735S_CMD_DISPOFF = 0x28,
    ST7735S_CMD_DISPON = 0x29,
} ST7735S_CommandTypeDef;

typedef enum DC_Mode
{
    DC_MODE_DATA = 0,
    DC_MODE_CMMAND = 1,
    DC_MODE_UNKOWN = 2,
} DC_Mode;

typedef struct ST7735S_HandleTypeDef
{
    SPI_HandleTypeDef *spi;
    GPIO_TypeDef *dc_port;
    uint16_t dc_pin;
    GPIO_TypeDef *rst_port;
    uint16_t rst_pin;
    GPIO_TypeDef *blk_port;
    uint16_t blk_pin;
    DC_Mode dc_mode;
} ST7735S_HandleTypeDef;

typedef struct
{
    uint8_t x_start;
    uint8_t y_start;
    uint8_t x_end;
    uint8_t y_end;
} ST7735S_WindowTypeDef;

void ST7735S_Init(ST7735S_HandleTypeDef *hst7735s,
                  SPI_HandleTypeDef *spi,
                  GPIO_TypeDef *dc_port,
                  uint16_t dc_pin,
                  GPIO_TypeDef *rst_port,
                  uint16_t rst_pin,
                  GPIO_TypeDef *blk_port,
                  uint16_t blk_pin);
void ST7735S_Reset(ST7735S_HandleTypeDef *hst7735s);
void ST7735S_BlacklightOn(ST7735S_HandleTypeDef *hst7735s);
void ST7735S_BlacklightOff(ST7735S_HandleTypeDef *hst7735s);
// inline void ST7735S_SendData(ST7735S_HandleTypeDef *hst7735s, uint8_t *data, uint16_t size);
// inline void ST7735S_SendCommand(ST7735S_HandleTypeDef *hst7735s, uint8_t cmd);
void ST7735S_LCD_Init(ST7735S_HandleTypeDef *hst7735s);
void ST7735_ShowPoint(ST7735S_HandleTypeDef *hst7735s, uint8_t x, uint8_t y, ST7735S_ColorTypeDef color);

void ST7735_ShowBlock(ST7735S_HandleTypeDef *hst7735s, uint8_t left, uint8_t up, uint8_t right, uint8_t down, ST7735S_ColorTypeDef color);