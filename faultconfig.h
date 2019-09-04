#ifndef _FAULTABLE_H_
#define _FAULTABLE_H_

#define FAULTCONFIG_CONCATENATE_DETAIL(x, y) x##y
#define FAULTCONFIG_CONCATENATE(x, y) FAULTCONFIG_CONCATENATE_DETAIL(x, y)
#define FAULTCONFIG_MAKE_UNIQUE(x) FAULTCONFIG_CONCATENATE(x, __COUNTER__)

#define FAULT_CONFIG_DETAIL(fnc, x) void fnc(void) { asm volatile(".byte 'F','A','U','L','T','C','O','N','F','I','G',0"); asm volatile(".ascii " #x "\n.byte 0"); };
#define FAULT_CONFIG(x) FAULT_CONFIG_DETAIL(FAULTCONFIG_MAKE_UNIQUE(__fc_magic_), x)

#endif
