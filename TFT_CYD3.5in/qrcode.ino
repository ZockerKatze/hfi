
/*
QR Code generator for CYD 3.5in that uses TFT_eSPI and qrcode_espi!
The config is also in the repo!
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <qrcode_espi.h>

TFT_eSPI display = TFT_eSPI();
QRcode_eSPI qrcode(&display);

void setup() {
    // init display
    display.init();
    display.setRotation(3); // set rotation to horizontally (1 is upright)
    display.fillScreen(TFT_WHITE); // clear screen

    // init the qrcode!
    qrcode.init();

    // create / display

    String qrData = "https://github.com/ZockerKatze"; // my github, but you can use anything
    qrcode.create(qrData);
}

void loop() {
    // Do nothing !
}
