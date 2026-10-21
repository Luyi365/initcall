#ifndef __INITCALL_H
#define __INITCALL_H

#define SECTION(x)                  __attribute__((section(x)))
typedef int (*init_fn_t)(void);
#if SYSTEM_DEBUG_INIT
    struct rt_init_desc
    {
        const char* fn_name;
        const init_fn_t fn;
    };
    #define INIT_EXPORT(fn, level)                                                       \
        const char __rti_##fn##_name[] = #fn;                                            \
        __attribute__((used)) const struct rt_init_desc __rt_init_desc_##fn SECTION(".init_fn."level) = \
        { __rti_##fn##_name, fn};
#else
    #define INIT_EXPORT(fn, level)                                                       \
        __attribute__((used)) const init_fn_t __rt_init_##fn SECTION(".init_fn."level) = fn
#endif

#define INIT_MCU_BASE_EXPORT(fn)        INIT_EXPORT(fn, "0")
/* board init routines will be called in board_init() function */
#define INIT_BOARD_EXPORT(fn)           INIT_EXPORT(fn, "1")
/* device initialization */
#define INIT_DEVICE_EXPORT(fn)          INIT_EXPORT(fn, "2")
/* thread initialization */
#define INIT_THREAD_EXPORT(fn)       	INIT_EXPORT(fn, "3")
/* components initialization */
#define INIT_COMPONENT_LEVEL0_EXPORT(fn)       INIT_EXPORT(fn, "4")

#define INIT_COMPONENT_LEVEL1_EXPORT(fn)       INIT_EXPORT(fn, "5")

#define INIT_PERIPHERAL_CLK_EXPORT	INIT_COMPONENT_LEVEL0_EXPORT

void system_mcu_base_init(void);
void system_board_init(void);
void system_device_init(void);
void system_thread_init(void);
void system_component_init(void);

void system_pre_work_init(void);

#endif
