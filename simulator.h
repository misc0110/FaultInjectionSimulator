#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#define TAG_ERROR "\033[91m[ERROR]\033[0m "
#define TAG_DEBUG "\033[94m[DEBUG]\033[0m "
#define TAG_WARN  "\033[93m[WARN ]\033[0m "
#define TAG_LINE  "\033[95mLine %zd:\033[0m "


typedef enum {
    SKIP = 1,
    BITFLIP = 2,
    LOG = 4,
    HAVOC = 8,
    ZERO = 16,
    __FAULT_END__
} fault_t;

typedef enum {
    RIP = 1,
    INSTRUCTION = 2
} position_t;

typedef enum {
    LOG_RIP = 1,
    LOG_INSTRUCTION = 2,
    LOG_FAULT = 4
} log_t;


typedef struct {
    fault_t type;
    union {
        position_t position;
        log_t log;
    };
    union {
        size_t rip;
        size_t instruction;
    };
    size_t index;
    size_t destination;
} Command;

typedef struct {
    size_t fault_blacklist;
    size_t position_blacklist;
    size_t log_blacklist;
    int skip_min;
    int skip_max;
    int timeout;
    size_t fail_every;
    int seed;
} Config;


#define ERROR(...) tagged_printf(TAG_ERROR, __VA_ARGS__)
#define DEBUG(...) tagged_printf(TAG_DEBUG, __VA_ARGS__)


#define DELIMITER " \t\r\n"

#endif
