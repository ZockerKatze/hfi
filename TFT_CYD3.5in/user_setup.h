// Define the driver for your display
#define ST7796_DRIVER

// Display dimensions
#define TFT_WIDTH  320
#define TFT_HEIGHT 480

// Pin definitions for your ESP32
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS    15
#define TFT_DC    2
#define TFT_RST   -1 // If not connected, set to -1
#define TFT_BL    27

// LED backlight control
#define TFT_BACKLIGHT_ON HIGH

// Touch screen chip select (if touch is used)
#define TOUCH_CS 33

// SPI settings
#define SPI_FREQUENCY        65000000
#define SPI_READ_FREQUENCY   20000000
#define SPI_TOUCH_FREQUENCY   2500000

// Fonts to load
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT
