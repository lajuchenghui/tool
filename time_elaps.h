#pragma once

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t time_ms_elaps(uint32_t prev_tick);
uint32_t time_ms_get(void);

#ifdef __cplusplus
}
#endif
