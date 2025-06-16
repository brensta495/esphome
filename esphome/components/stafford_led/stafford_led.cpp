#include "stafford_led.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace stafford_led {

static const char *const TAG = "stafford_led";

StaffordLED *global_stafford_led = nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

StaffordLED::StaffordLED(GPIOPin *pin) : pin_(pin) { global_stafford_led = this; }
void StaffordLED::pre_setup() {
  ESP_LOGCONFIG(TAG, "Running setup");
  this->pin_->setup();
  this->pin_->digital_write(false);
}
void StaffordLED::dump_config() {
  ESP_LOGCONFIG(TAG, "Stafford LED:");
  LOG_PIN("  Pin: ", this->pin_);
}
void StaffordLED::loop() {
  if ((App.get_app_state() & STATUS_LED_ERROR) != 0u) {
    this->pin_->digital_write(millis() % 250u < 150u);
  } else if ((App.get_app_state() & STATUS_LED_WARNING) != 0u) {
    this->pin_->digital_write(millis() % 1500u < 250u);
  } else {
    this->pin_->digital_write(false);
  }
}
float StaffordLED::get_setup_priority() const { return setup_priority::HARDWARE; }
float StaffordLED::get_loop_priority() const { return 50.0f; }

}  // namespace stafford_led
}  // namespace esphome
