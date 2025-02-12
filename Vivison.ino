#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>

// Replace with your desired SSID and password
const char* ssid = "ViVision";
const char* password = "VIVIVIVI";

// Create color sensor object
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

struct Color {
  uint16_t r;
  uint16_t g;
  uint16_t b;
  String name;
};

// Define the standard colors
Color colors[] = {
  {255, 0, 0, "Red"},
  {0, 255, 0, "Green"},
  {0, 0, 255, "Blue"},
  {255, 255, 255, "White"},
  {255, 165, 0, "Orange"},
  {255, 255, 0, "Yellow"},
  {0, 255, 0, "Lime"},
  {0, 0, 255, "Blue"},
  {128, 0, 128, "Purple"},
  {128, 0, 0, "Maroon"},
  {255, 215, 0, "Gold"},
  {255, 192, 203, "Pink"},
  {64, 224, 208, "Turquoise"},
  {0, 0, 0, "Black"},
  {128, 128, 128, "Gray"},
  {128, 128, 0, "Olive"},
  {238, 130, 238, "Violet"},
  {0, 100, 0, "Dark Green"},
  {0, 0, 139, "Dark Blue"},
  {192, 192, 192, "Silver"},
  {255, 255, 224, "Light Yellow"},
  {224, 255, 255, "Light Cyan"},
  {165, 42, 42, "Brown"},
  {230, 230, 250, "Lavender"},
  {250, 128, 114, "Salmon"},
  {75, 0, 130, "Indigo"},
  {255, 127, 80, "Coral"},
  {144, 238, 144, "Light Green"},
  {135, 206, 235, "Sky Blue"},
  {245, 245, 220, "Beige"},
  {152, 251, 152, "Pale Green"},
  {240, 230, 140, "Khaki"},
  {230, 230, 250, "Lavender"},
  {255, 228, 181, "Moccasin"},
  {255, 218, 185, "Peach Puff"},
  {205, 133, 63, "Peru"},
  {245, 222, 179, "Wheat"},
  {255, 239, 213, "Papaya Whip"},
  {255, 105, 180, "Hot Pink"},
  {255, 20, 147, "Deep Pink"},
  {255, 160, 122, "Light Salmon"},
  {240, 128, 128, "Light Coral"},
  {233, 150, 122, "Dark Salmon"},
  {188, 143, 143, "Rosy Brown"},
  {255, 228, 225, "Misty Rose"},
  {255, 245, 238, "Seashell"},
  {245, 245, 245, "White Smoke"},
  {112, 128, 144, "Slate Gray"},
  {176, 224, 230, "Powder Blue"},
  {240, 248, 255, "Alice Blue"},
  {240, 255, 255, "Azure"},
  {240, 255, 240, "Honeydew"},
  {255, 250, 240, "Floral White"},
  {253, 245, 230, "Old Lace"},
  {255, 250, 205, "Lemon Chiffon"},
  {250, 250, 210, "Light Goldenrod Yellow"},
  {255, 255, 240, "Ivory"},
  {255, 248, 220, "Cornsilk"},
  {255, 245, 238, "Seashell"},
  {245, 245, 245, "White Smoke"},
  {112, 128, 144, "Slate Gray"},
  {211, 211, 211, "Light Gray"},
  {131, 111, 255, "Light Slate Blue"},
  {72, 209, 204, "Medium Turquoise"},
  {127, 255, 212, "Aquamarine"},
  {127, 255, 0, "Chartreuse"},
  {173, 255, 47, "Green Yellow"},
  {255, 182, 193, "Light Pink"},
  {255, 160, 122, "Light Salmon"},
  {255, 218, 185, "Peach Puff"},
  {205, 133, 63, "Peru"},
  {245, 222, 179, "Wheat"},
  {255, 239, 213, "Papaya Whip"},
  {255, 105, 180, "Hot Pink"},
  {255, 20, 147, "Deep Pink"},
  {255, 160, 122, "Light Salmon"},
  {240, 128, 128, "Light Coral"},
  {233, 150, 122, "Dark Salmon"},
  {188, 143, 143, "Rosy Brown"},
  {255, 228, 225, "Misty Rose"},
  {255, 245, 238, "Seashell"},
  {245, 245, 245, "White Smoke"},
  {112, 128, 144, "Slate Gray"},
  {176, 224, 230, "Powder Blue"},
  {240, 248, 255, "Alice Blue"},
  {240, 255, 255, "Azure"},
  {240, 255, 240, "Honeydew"},
  {255, 250, 240, "Floral White"},
  {253, 245, 230, "Old Lace"},
  {255, 250, 205, "Lemon Chiffon"},
  {250, 250, 210, "Light Goldenrod Yellow"},
  {255, 255, 240, "Ivory"},
  {255, 248, 220, "Cornsilk"},
  {255, 245, 238, "Seashell"},
  {245, 245, 245, "White Smoke"},
  {112, 128, 144, "Slate Gray"},
  {211, 211, 211, "Light Gray"},
  {131, 111, 255, "Light Slate Blue"},
  {72, 209, 204, "Medium Turquoise"},
  {127, 255, 212, "Aquamarine"},
  {127, 255, 0, "Chartreuse"},
  {173, 255, 47, "Green Yellow"},
  {255, 182, 193, "Light Pink"},
  {255, 160, 122, "Light Salmon"},
  {255, 218, 185, "Peach Puff"},
  {205, 133, 63, "Peru"},
  {245, 222, 179, "Wheat"},
  {255, 239, 213, "Papaya Whip"},
  {255, 105, 180, "Hot Pink"},
  {255, 20, 147, "Deep Pink"},
  {255, 160, 122, "Light Salmon"},
  {240, 128, 128, "Light Coral"},
  {233, 150, 122, "Dark Salmon"},
  {188, 143, 143, "Rosy Brown"},
  {255, 228, 225, "Misty Rose"},
  {255, 245, 238, "Seashell"},
  {245, 245, 245, "White Smoke"},
  {112, 128, 144, "Slate Gray"},
  {176, 224, 230, "Powder Blue"},
  {240, 248, 255, "Alice Blue"},
  {240, 255, 255, "Azure"},
  {240, 255, 240, "Honeydew"},
  {255, 250, 240, "Floral White"},
  {253, 245, 230, "Old Lace"},
  {255, 250, 205, "Lemon Chiffon"},
  {250, 250, 210, "Light Goldenrod Yellow"},
  {255, 255, 240, "Ivory"},
  {255, 248, 220, "Cornsilk"},
  {255, 245, 238, "Seashell"},
  {245, 245, 245, "White Smoke"},
  {112, 128, 144, "Slate Gray"},
  {211, 211, 211, "Light Gray"},
  {131, 111, 255, "Light Slate Blue"},
  {72, 209, 204, "Medium Turquoise"},
  {127, 255, 212, "Aquamarine"},
  {127, 255, 0, "Chartreuse"},
  {173, 255, 47, "Green Yellow"},
  {255, 182, 193, "Light Pink"},
  {255, 160, 122, "Light Salmon"},
  {255, 0, 0, "Red"},
  {255, 69, 0, "Red-Orange"},
  {255, 99, 71, "Tomato"},
  {255, 127, 80, "Coral"},
  {255, 140, 0, "Dark Orange"},
  {255, 165, 0, "Orange"},
  {255, 192, 203, "Pink"},
  {255, 218, 185, "Peach Puff"},
  {255, 228, 181, "Moccasin"},
  {255, 239, 213, "Papaya Whip"},
  {255, 240, 245, "Lavender Blush"},
  {255, 245, 238, "Seashell"},
  {255, 248, 220, "Cornsilk"},
  {255, 250, 205, "Lemon Chiffon"},
  {255, 250, 240, "Floral White"},
  {255, 255, 0, "Yellow"},
  {255, 255, 224, "Light Yellow"},
  {255, 255, 240, "Ivory"},
  {255, 255, 255, "White"},
  {0, 0, 255, "Blue"},
  {0, 0, 128, "Navy"},
  {0, 100, 0, "Dark Green"},
  {0, 128, 0, "Green"},
  {0, 128, 128, "Teal"},
  {0, 139, 139, "Dark Cyan"},
  {0, 255, 0, "Lime"},
  {0, 255, 255, "Cyan"},
  {25, 25, 112, "Midnight Blue"},
  {30, 144, 255, "Dodger Blue"},
  {46, 139, 87, "Sea Green"},
  {47, 79, 79, "Dark Slate Gray"},
  {50, 205, 50, "Lime Green"},
  {60, 179, 113, "Medium Sea Green"},
  {64, 224, 208, "Turquoise"},
  {65, 105, 225, "Royal Blue"},
  {70, 130, 180, "Steel Blue"},
  {72, 61, 139, "Dark Slate Blue"},
  {75, 0, 130, "Indigo"},
  {85, 107, 47, "Dark Olive Green"},
  {95, 158, 160, "Cadet Blue"},
  {100, 149, 237, "Cornflower Blue"},
  {106, 90, 205, "Slate Blue"},
  {107, 142, 35, "Olive Drab"},
  {112, 128, 144, "Slate Gray"},
  {119, 136, 153, "Light Slate Gray"},
  {123, 104, 238, "Medium Slate Blue"},
  {124, 252, 0, "Lawn Green"},
  {127, 255, 0, "Chartreuse"},
  {135, 206, 235, "Sky Blue"},
  {138, 43, 226, "Blue Violet"},
  {139, 0, 0, "Dark Red"},
  {139, 0, 139, "Dark Magenta"},
  {143, 188, 143, "Dark Sea Green"},
  {144, 238, 144, "Light Green"},
  {147, 112, 219, "Medium Purple"},
  {148, 0, 211, "Dark Violet"},
  {152, 251, 152, "Pale Green"},
  {153, 50, 204, "Dark Orchid"},
    {154, 205, 50, "Yellow Green"},
    {160, 82, 45, "Sienna"},
    {165, 42, 42, "Brown"},
    {169, 169, 169, "Dark Gray"},
    {173, 255, 47, "Green Yellow"},
    {173, 216, 230, "Light Blue"},
    {175, 238, 238, "Pale Turquoise"},
    {176, 196, 222, "Light Steel Blue"},
    {176, 224, 230, "Powder Blue"},
    {178, 34, 34, "Firebrick"},
    {184, 134, 11, "Dark Goldenrod"},
    {186, 85, 211, "Medium Orchid"},
    {188, 143, 143, "Rosy Brown"},
    {189, 183, 107, "Dark Khaki"},
    {192, 192, 192, "Silver"},
    {199, 21, 133, "Medium Violet Red"},
    {205, 133, 63, "Peru"},
    {210, 105, 30, "Chocolate"},
    {218, 165, 32, "Goldenrod"},
    {219, 112, 147, "Pale Violet Red"},
    {220, 20, 60, "Crimson"},
    {221, 160, 221, "Plum"},
    {222, 184, 135, "Burlywood"},
    {224, 255, 255, "Light Cyan"},
    {230, 230, 250, "Lavender"},
    {233, 150, 122, "Dark Salmon"},
    {238, 130, 238, "Violet"},
    {238, 232, 170, "Pale Goldenrod"},
    {240, 128, 128, "Light Coral"},
    {240, 230, 140, "Khaki"},
    {240, 248, 255, "Alice Blue"},
    {240, 255, 240, "Honeydew"},
    {240, 255, 255, "Azure"},
    {244, 164, 96, "Sandy Brown"},
    {245, 222, 179, "Wheat"},
    {245, 245, 220, "Beige"},
    {245, 245, 245, "White Smoke"},
    {245, 255, 250, "Mint Cream"},
    {248, 248, 255, "Ghost White"},
    {250, 128, 114, "Salmon"},
    {250, 235, 215, "Antique White"},
    {250, 240, 230, "Linen"},
    {253, 245, 230, "Old Lace"},
    {255, 182, 193, "Light Pink"},
    {255, 192, 203, "Pink"},
    {255, 215, 0, "Gold"},
    {255, 218, 185, "Peach Puff"},
    {255, 222, 173, "Navajo White"},
    {255, 228, 181, "Moccasin"},
    {255, 228, 225, "Misty Rose"},
    {255, 235, 205, "Blanched Almond"},
    {255, 239, 213, "Papaya Whip"},
    {255, 240, 245, "Lavender Blush"},
    {255, 245, 238, "Seashell"},
    {255, 248, 220, "Cornsilk"},
    {255, 250, 205, "Lemon Chiffon"},
    {255, 250, 240, "Floral White"},
    {255, 250, 250, "Snow"},
    {255, 255, 0, "Yellow"},
    {255, 255, 224, "Light Yellow"},
    {255, 255, 240, "Ivory"},
    {255, 255, 255, "White"},
    {0, 0, 0, "Black"},
    {47, 79, 79, "Dark Slate Gray"},
    {105, 105, 105, "Dim Gray"},
    {112, 128, 144, "Slate Gray"},
    {169, 169, 169, "Dark Gray"},
    {190, 190, 190, "Gray"},
    {211, 211, 211, "Light Gray"},
    {220, 220, 220, "Gainsboro"},
  
};

String currentColor = "";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", currentColor);
}

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set up the ESP8266 as an access point
  WiFi.softAP(ssid, password);

  // Print the IP address
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  // Initialize the color sensor
  if (tcs.begin()) {
    Serial.println("Color sensor initialized");
  } else {
    Serial.println("Failed to initialize color sensor");
    while (1);
  }

  // Define the handler for the root URL
  server.on("/", handleRoot);

  // Start the server
  server.begin();
}

void loop() {
  // Read the color data from the sensor
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Find the color that is the closest match to the read color
  Color closestColor = colors[0];
  uint32_t minDistance = 0xFFFFFFFF;
  for (Color color : colors) {
    uint32_t distance = sq(color.r - r) + sq(color.g - g) + sq(color.b - b);
    if (distance < minDistance) {
      minDistance = distance;
      closestColor = color;
    }
  }

  // Update the current color
  currentColor = closestColor.name;

  // Print the current color to the serial monitor
  Serial.println(currentColor);

  // Handle client requests
  server.handleClient();

  // Wait for a bit before the next reading
  delay(1000);
}
