#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <SFE_BMP180.h>
//#include <dht.h>


// Connect VCC of the BMP180 sensor to 3.3V
// Connect GND to Ground
// Connect SCL to i2c clock  thats A5
// Connect SDA to i2c data  thats A4

//Adafruit_BMP085 bmp;
//dht DHT; //use DHT11

//DHT nin bagli oldugu pin belirtiliyor.
//#define DHT11_PIN 7

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SH1106 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

double basinc;
double getPressure ();
SFE_BMP180 pressure;
double baseline; // BMP sensor degerlerinin olcumu icin


void setup()   {
  Serial.begin(9600);


  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC);
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  
 // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();

  //text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(basinc);
  baseline = getPressure();
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();


}

void loop() {

   basinc = getPressure();
  display.display();
  delay(2000);
}

// Basinc degerlerini alma islemi
double getPressure() {
  char status;
  double T, P;
  status = pressure.startPressure(3); // Basinc degeri alma islemi baslatiliyor
  if (status != 0) {
    delay(status);
    status = pressure.getPressure(P, T); // Basinc degeri aliniyor
    if (status != 0) {
      return (P); // Basinc degeri fonksiyona donduruluyor.
    }
  }
}

