#ifndef _FAULTABLE_H_
#define _FAULTABLE_H_

#define FAULTCONFIG_CONCATENATE_DETAIL(x, y) x##y
#define FAULTCONFIG_CONCATENATE(x, y) FAULTCONFIG_CONCATENATE_DETAIL(x, y)
#define FAULTCONFIG_MAKE_UNIQUE(x) FAULTCONFIG_CONCATENATE(x, __COUNTER__)

#define FAULT_CONFIG_SIGNATURE asm volatile(".byte 'F','A','U','L','T','C','O','N','F','I','G',0");

#define FAULT_CONFIG_DETAIL(fnc, x) void fnc(void) { FAULT_CONFIG_SIGNATURE asm volatile(".ascii " #x "\n.byte 0"); };
#define FAULT_CONFIG(x) FAULT_CONFIG_DETAIL(FAULTCONFIG_MAKE_UNIQUE(__fc_magic_), x)

#define FAULT_CONFIG_DETAIL_ADDRESS(fnc, x, y) void fnc(void) { FAULT_CONFIG_SIGNATURE asm volatile(".asciz " #x "\n.dc.a " #y); };
#define FAULT_CONFIG_ADDRESS(x, y) FAULT_CONFIG_DETAIL_ADDRESS(FAULTCONFIG_MAKE_UNIQUE(__fc_magic_), x, y)


#define FAULT_CONFIG_ENTRY(e) FAULT_CONFIG_ADDRESS("ENTRY", e)
#endif
