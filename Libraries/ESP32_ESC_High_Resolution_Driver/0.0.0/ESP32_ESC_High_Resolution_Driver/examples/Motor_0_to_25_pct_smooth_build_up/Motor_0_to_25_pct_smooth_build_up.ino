#include <ESP32_ESC_High_Resolution_Driver.h>

ESP32_ESC_HIGH_RESOLUTION_DRIVER ESC_Control = ESP32_ESC_HIGH_RESOLUTION_DRIVER();
byte ESC_pin = 4;
int ESC_Frequency = 50;

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);
  vTaskDelay(500);

  Serial.println("ESP32_ESC_HIGH_RESOLUTION_DRIVER - Example 0 to 25% Motor RPM \n");

  // Set up MCPWM
  ESC_Control.ESC_attach(ESC_pin, ESC_Frequency);

  // Pause to allow the ESC to activate (MUST BE CALIBRATED !!)
  ESC_Control.ESC_set_us(1000);
  Serial.println("Pause for ESC Activation...");
  vTaskDelay(7000);

  //ESC_Control.ESC_calibrate();
}

void loop() {
  // 0-25% example, limited to 25% because it is not good to spin a motor with zero load at full speed.
  // Alter as necessary, with caution, watch out for flying propellers or motor cans pulling off the main motor body !!
  // Ask me how I know, USE WITH CAUTION !!!
  
  // increment by us for RC ESC for Max Resolution of 1000 steps
  for (uint16_t i = 1000; i < 1250; i++) {
    ESC_Control.ESC_set_us(i);
    float PWM = ESC_Control.convert_us_to_PWM(i);
    uint16_t us = ESC_Control.convert_PWM_to_us(PWM);
    Serial.print("PWM "); Serial.print(PWM); Serial.print("% = "); Serial.print(us); Serial.println("us");
    vTaskDelay(100);
  }
  // decrement by 0.005 PWM % for RC ESC for Max Resolution of 1000 steps
  for (float i = 6.250; i > 5.100; i -= 0.005) {
    ESC_Control.ESC_setPWM(i);
    uint16_t us = ESC_Control.convert_PWM_to_us(i);
    float PWM = ESC_Control.convert_us_to_PWM(us);
    Serial.print("PWM "); Serial.print(PWM); Serial.print("% = "); Serial.print(us); Serial.println("us");
    vTaskDelay(100);
  }
}
