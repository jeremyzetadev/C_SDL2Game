#pragma once

#include "../arraylist/arraylist.h"
#include "../types.h"

typedef struct physics_state_internal {
    Arraylist *body_list;
} Physics_State_Internal;
