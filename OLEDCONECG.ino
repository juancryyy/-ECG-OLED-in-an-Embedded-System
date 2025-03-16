#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int LO1 = 26; // Pin para el tercer LED LO+
const int LO2 = 15; // Pin para el cuarto LED LO-
const int entradaAD = 4; // Pin de entrada analógica para la señal cardíaca

void setup() {
  Serial.begin(9600);
  pinMode(LO1, INPUT);
  pinMode(LO2, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("No se ha encontrado la pantalla OLED"));
    for(;;);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  if((digitalRead(LO2) == 1) || (digitalRead(LO1) == 1)) {
    Serial.println("Revisa tu código compañero%");
  } else {
    int signal = analogRead(entradaAD);
    Serial.println(signal);

    // Graficar la señal en la pantalla OLED
    static int xPos = 0; // Posición x actual en la pantalla
    static int prevY = SCREEN_HEIGHT / 2; // Valor previo de y para graficar la línea

    // Mapear la señal analógica a la altura de la pantalla OLED
    int yPos = map(signal, 0, 4095, 0, SCREEN_HEIGHT); // Ajuste según la resolución del ADC del ESP32

    // Dibujar una línea desde la posición previa hasta la actual
    display.drawLine(xPos, prevY, xPos + 1, yPos, SSD1306_WHITE);
    prevY = yPos;
    xPos++;

    // Si llegamos al final de la pantalla, limpiamos y comenzamos de nuevo
    if (xPos >= SCREEN_WIDTH) {
      xPos = 0;
      display.clearDisplay();
    }

    display.display();
  }
  delay(5); // Ajustar el tiempo de espera entre cada paso
}
