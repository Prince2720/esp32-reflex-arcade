#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Updated Pin Mapping
const int PIN_TOUCH  = 4;
const int PIN_IR     = 14;
const int PIN_PIR    = 25;
const int PIN_BUZZER = 26;
const int PIN_LDR    = 34;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- HARDWARE DIAGNOSTIC TEST STARTED ---");

  pinMode(PIN_TOUCH, INPUT);
  pinMode(PIN_IR, INPUT);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LDR, INPUT);

  // 1. OLED Check
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("❌ OLED: Initialization FAILED (check SDA=21, SCL=22 or address 0x3C/0x3D)");
  } else {
    Serial.println("✅ OLED: Detected & Initialized");
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(10, 25);
    display.println("TEST BENCH READY");
    display.display();
  }

  // 2. Initial Buzzer Test (Quick 2-beep chirp)
  Serial.println("🔊 Testing Buzzer on GPIO 26...");
  tone(PIN_BUZZER, 1000, 150);
  delay(200);
  tone(PIN_BUZZER, 1500, 150);
  delay(300);
}

void loop() {
  int touchVal = digitalRead(PIN_TOUCH);
  int irVal    = digitalRead(PIN_IR);
  int pirVal   = digitalRead(PIN_PIR);
  int ldrVal   = analogRead(PIN_LDR);

  // Print values to Serial Monitor
  Serial.print("Touch: ");
  Serial.print(touchVal ? "TOUCHED (1)" : "IDLE (0)");
  Serial.print(" | IR: ");
  Serial.print(irVal == HIGH ? "OBJECT DETECTED (0)" : "CLEAR (1)");
  Serial.print(" | PIR: ");
  Serial.print(pirVal ? "MOTION (1)" : "STILL (0)");
  Serial.print(" | LDR (Raw): ");
  Serial.println(ldrVal);

  // Real-time OLED Diagnostic Display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("--- LIVE STATUS ---");
  
  display.setCursor(0, 16);
  display.print("Touch: ");
  display.println(touchVal ? "PRESSED" : "RELEASED");

  display.setCursor(0, 28);
  display.print("IR: ");
  display.println(irVal == HIGH ? "TRIGGERED" : "OPEN");

  display.setCursor(0, 40);
  display.print("PIR: ");
  display.println(pirVal ? "MOTION" : "IDLE");

  display.setCursor(0, 52);
  display.print("LDR: ");
  display.println(ldrVal);
  display.display();

  // Chirp buzzer whenever touch sensor is pressed
  if (touchVal == HIGH) {
    tone(PIN_BUZZER, 800, 50);
  }

  delay(200);
}