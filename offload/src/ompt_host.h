#ifndef OMPT_TARGET_H_INCLUDED
#define OMPT_TARGET_H_INCLUDED

#include "ompt.h"

typedef struct ompt_target_data_id_stack_s {
    ompt_target_id_t                        target_data_id;
    struct ompt_target_data_id_stack_s      *prev;
} ompt_target_data_id_stack_t;

typedef struct ompt_target_info_s {
    /* Stack for the ids for the current target data region */
    ompt_target_data_id_stack_t     *target_data_id_stack;

    /* boolean flag to differentiate target data and target update*/
    int                             is_target_data;
} ompt_target_info_t;


// filled in __ompt_target_initialize
extern ompt_get_task_id_t ompt_get_task_id;

typedef int (*ompt_enabled_t)();
extern ompt_enabled_t ompt_enabled;

typedef ompt_callback_t (*ompt_get_target_callback_t)(ompt_event_t);
extern ompt_get_target_callback_t __ompt_get_target_callback;

void __ompt_target_initialize();

// defined in runtime which has C interface
#ifdef __cplusplus
extern "C" {
#endif
extern void ompt_target_initialize(ompt_get_task_id_t *, ompt_enabled_t *,
                                   ompt_get_target_callback_t *,
                                   ompt_target_trace_start_t,
                                   ompt_target_trace_stop_t);
#ifdef __cplusplus
};
#endif

// helper functions for callbacks
static inline ompt_new_target_callback_t
ompt_get_new_target_callback(ompt_event_t evid)
{
    return (ompt_new_target_callback_t) __ompt_get_target_callback(evid);
}

static inline ompt_target_callback_t
ompt_get_target_callback(ompt_event_t evid)
{
    return (ompt_target_callback_t) __ompt_get_target_callback(evid);
}

static inline ompt_new_data_map_callback_t
ompt_get_new_data_map_callback(ompt_event_t evid)
{
    return (ompt_new_data_map_callback_t) __ompt_get_target_callback(evid);
}

static inline ompt_data_map_callback_t
ompt_get_data_map_callback(ompt_event_t evid)
{
    return (ompt_data_map_callback_t) __ompt_get_target_callback(evid);
}


ompt_target_id_t __ompt_target_id_new();

ompt_data_map_id_t __ompt_data_map_id_new();


// tracing inquiry functions
int __ompt_target_trace_start(
        int device_id,
        ompt_target_buffer_request_callback_t request,
        ompt_target_buffer_complete_callback_t complete);

int __ompt_target_trace_stop(int device_id);

#endif
