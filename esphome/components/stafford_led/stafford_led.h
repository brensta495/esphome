#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace stafford_led {

class StaffordLED : public Component {
 public:
  explicit StaffordLED(GPIOPin *pin);

  void pre_setup();
  void dump_config() override;
  void loop() override;
  float get_setup_priority() const override;
  float get_loop_priority() const override;

 protected:
  GPIOPin *pin_;
};

extern StaffordLED *global_stafford_led;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

}  // namespace stafford_led
}  // namespace esphome
