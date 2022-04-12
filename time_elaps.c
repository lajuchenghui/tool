#include "time_elaps.h"

uint32_t time_ms_elaps(uint32_t prev_tick)
{
    uint32_t act_time = time_ms_get();

    /*If there is no overflow in sys_time simple subtract*/
    if (act_time >= prev_tick) {
        prev_tick = act_time - prev_tick;
    }
    else {
        prev_tick = UINT32_MAX - prev_tick + 1;
        prev_tick += act_time;
    }

    return prev_tick;
}

uint32_t time_ms_get(void)
{
    static uint64_t start_ms = 0;
    uint64_t now_ms;
    uint32_t time_ms;

    if (start_ms == 0) {
        start_ms = clock();
    }

    now_ms = clock();
    time_ms = now_ms - start_ms;

    return time_ms;
}
