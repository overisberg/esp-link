#include <esp8266.h>
#include "config.h"

// Map pin to mux
uint32_t pin_mux[] = {
  PERIPHS_IO_MUX_GPIO0_U, PERIPHS_IO_MUX_U0TXD_U, PERIPHS_IO_MUX_GPIO2_U, PERIPHS_IO_MUX_U0RXD_U,
  PERIPHS_IO_MUX_GPIO4_U, PERIPHS_IO_MUX_GPIO5_U, -1, -1,
  -1, PERIPHS_IO_MUX_SD_DATA2_U, PERIPHS_IO_MUX_SD_DATA3_U, -1,
  PERIPHS_IO_MUX_MTDI_U, PERIPHS_IO_MUX_MTCK_U, PERIPHS_IO_MUX_MTMS_U, PERIPHS_IO_MUX_MTDO_U,
  PAD_XPD_DCDC_CONF
};

// Map pin to function
uint8_t pin_func[] = {
  FUNC_GPIO0, FUNC_GPIO1, FUNC_GPIO2, FUNC_GPIO3,
  FUNC_GPIO4, FUNC_GPIO5, -1, -1,
  -1, FUNC_GPIO9, FUNC_GPIO10, -1,
  FUNC_GPIO12, FUNC_GPIO13, FUNC_GPIO14, FUNC_GPIO15,
  -1
};

void ICACHE_FLASH_ATTR securityConfigure(int8_t pin) {
  PIN_FUNC_SELECT(pin_mux[pin], pin_func[pin]);
  PIN_PULLUP_EN(pin_mux[pin]);
}

void ICACHE_FLASH_ATTR securityInit(void) {
  if (flashConfig.security_pin >= 0) {
    os_printf("Security pin enabled\n");
    os_printf("Pin %d have to be low during configuration changes\n", flashConfig.security_pin);
    securityConfigure(flashConfig.security_pin);
  }
}

bool ICACHE_FLASH_ATTR okToUpdateConfig(void) {
  if (flashConfig.security_pin < 0 || GPIO_INPUT_GET(flashConfig.security_pin) == 0) {
    return(true);
  } else {
    os_printf("Configuration change blocked because security pin was high\n");
    return(false);
  }
}
