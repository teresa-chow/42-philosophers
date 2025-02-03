#include "../include/philosophers.h"

bool    sim_active(t_sim *sim)
{
    return (get_bool(&sim->status, &sim->active));
}