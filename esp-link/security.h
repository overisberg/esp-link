#ifndef SECURITY_H
#define SECURITY_H

void securityInit(void);
void ICACHE_FLASH_ATTR securityConfigure(int8_t pin);
bool ICACHE_FLASH_ATTR okToUpdateConfig(void);

#endif

