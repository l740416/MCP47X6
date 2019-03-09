#include <Wire.h>
#include <MCP47X6.h>


MCP47X6 mcp4716(MCP47X6_IS_MCP4706);

void setup() {
  mcp4716.begin(4,5);
}

void loop() {
  mcp4716.setLevel(512);
  delay(5000);
}
