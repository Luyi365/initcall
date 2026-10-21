#include "initcall.h"
#if SYSTEM_DEBUG_INIT
#include <stdio.h>
#endif

static int rti_start(void)
{
    return 0;
}
INIT_EXPORT(rti_start, "0");

static int rti_board_start(void)
{
    return 0;
}
INIT_EXPORT(rti_board_start, "0.end");

static int rti_board_end(void)
{
    return 0;
}
INIT_EXPORT(rti_board_end, "1.end");

static int rti_thread_end(void)
{
    return 0;
}
INIT_EXPORT(rti_thread_end, "2.end");

static int rti_component_level_0_end(void)
{
    return 0;
}
INIT_EXPORT(rti_component_level_0_end, "3.end");

static int rti_component_level_1_end(void)
{
    return 0;
}
INIT_EXPORT(rti_component_level_1_end, "4.end");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end, "5.end");

void system_mcu_base_init(void)
{
#if SYSTEM_DEBUG_INIT
    int result;
    volatile const struct rt_init_desc *desc;
    for (desc = &__rt_init_desc_rti_start; desc < &__rt_init_desc_rti_board_start; desc ++)
    {
        printf("initialize %s", desc->fn_name);
        result = desc->fn();
        printf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;
    for (fn_ptr = &__rt_init_rti_start; fn_ptr < &__rt_init_rti_board_start; fn_ptr++)
    {
        (*fn_ptr)();
    }
#endif
}

void system_board_init(void)
{
#if SYSTEM_DEBUG_INIT
    int result;
    volatile const struct rt_init_desc *desc;
    for (desc = &__rt_init_desc_rti_board_start; desc < &__rt_init_desc_rti_board_end; desc ++)
    {
        printf("initialize %s", desc->fn_name);
        result = desc->fn();
        printf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;
    for (fn_ptr = &__rt_init_rti_board_start; fn_ptr < &__rt_init_rti_board_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
#endif
}

void system_device_init(void)
{
#if SYSTEM_DEBUG_INIT
    int result;
    volatile const struct rt_init_desc *desc;
    for (desc = &__rt_init_desc_rti_board_end; desc < &__rt_init_desc_rti_thread_end; desc ++)
    {
        printf("initialize %s", desc->fn_name);
        result = desc->fn();
        printf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;
    for (fn_ptr = &__rt_init_rti_board_end; fn_ptr < &__rt_init_rti_thread_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
#endif
}

void system_thread_init(void)
{
#if SYSTEM_DEBUG_INIT
    int result;
    volatile const struct rt_init_desc *desc;

    for (desc = &__rt_init_desc_rti_thread_end; desc < &__rt_init_desc_rti_component_level_0_end; desc ++)
    {
        printf("initialize %s", desc->fn_name);
        result = desc->fn();
        printf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;
    for (fn_ptr = &__rt_init_rti_thread_end; fn_ptr < &__rt_init_rti_component_level_0_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }
#endif
}

void system_component_init(void)
{
#if SYSTEM_DEBUG_INIT
    int result;
    volatile const struct rt_init_desc *desc;

    for (desc = &__rt_init_desc_rti_component_level_0_end; desc < &__rt_init_desc_rti_end; desc ++)
    {
        printf("initialize %s", desc->fn_name);
        result = desc->fn();
        printf(":%d done\n", result);
    }
#else
    volatile const init_fn_t *fn_ptr;
    for (fn_ptr = &__rt_init_rti_component_level_0_end; fn_ptr < &__rt_init_rti_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }
#endif
}

void system_pre_work_init(void)
{
	system_mcu_base_init();
	system_board_init();
	system_device_init();
	system_thread_init();
	system_component_init();
}
