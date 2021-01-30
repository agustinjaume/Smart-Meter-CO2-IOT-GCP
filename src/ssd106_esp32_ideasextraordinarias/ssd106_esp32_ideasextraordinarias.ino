#include <U8g2lib.h>
#include <Wire.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
void setup(void) {
    u8g2.begin(); //Inicializamos el dispositivo
}
void loop(void) {
    u8g2.clearBuffer();                    // Vaciamos el buffer del dispositivo
    u8g2.setFont(u8g2_font_logisoso16_tr);    // Seleccionamos la fuente
    u8g2.drawStr(5,35,"ideasss");    // Escribimos en el buffer el texto con la posición (X,Y) en la pantalla
    u8g2.sendBuffer();                    // Enviamos el buffer a nuestra pantalla
    delay(1000);  
}
