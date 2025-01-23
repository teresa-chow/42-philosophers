/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//static void even_routine(t_sim **sim, int i);
//static void odd_routine(t_sim **sim, int i);

void	*main_routine(void *arg) //REDO: act_die is also setting active to 0
{
    t_sim *sim;

    sim = (t_sim *)arg;
    while (1)
    {
        if (sim->active == 0)
        {
            printf("---------------------\n"); //delete
            break ;
        }
    }
	return (NULL);
}

void	*philo_routine(void *arg)
{
    struct timeval  now;
    static int	i = -1;
    t_sim	*sim;
	
	sim = (t_sim *)arg;
    while (1)
    {
        if (sim->active == 1)
        {
            pthread_mutex_lock(&sim->counter);
            i++;
            pthread_mutex_unlock(&sim->counter);
            pthread_mutex_lock(&sim->pair);
            pthread_mutex_lock(&sim->forks[i]);
            gettimeofday(&now, NULL);
            printf(WHI "%d\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
            pthread_mutex_lock(&sim->forks[i + 1]);
            pthread_mutex_unlock(&sim->pair);
            gettimeofday(&now, NULL);
            printf(WHI "%d\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
            act_eat(sim->info, i, &sim->philo);
            pthread_mutex_unlock(&sim->forks[i]);
            pthread_mutex_unlock(&sim->forks[i + 1]);
            act_sleep(sim->info, i, &sim->philo);
            act_think(i, &sim->philo);
            act_die(&sim, sim->info, i, &sim->philo);
            if (sim->active == 0)
                break ;
        }
    }
    return (NULL);
}

/*static void even_routine(t_sim **sim, int i)
{
    struct timeval  now;

    while ((*sim)->active == 1)
    {
        //pthread_mutex_lock(&(*sim)->pair);
        pthread_mutex_lock(&(*sim)->forks[i]);
        gettimeofday(&now, NULL);
        printf(WHI "%d\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
        pthread_mutex_lock(&(*sim)->forks[i + 1]);
        //pthread_mutex_unlock(&(*sim)->pair);
        gettimeofday(&now, NULL);
        printf(WHI "%d\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
        act_eat((*sim)->info, i, &(*sim)->philo);
        pthread_mutex_unlock(&(*sim)->forks[i]);
        pthread_mutex_unlock(&(*sim)->forks[i + 1]);
        act_sleep((*sim)->info, i, &(*sim)->philo);
        act_think(i, &(*sim)->philo);
        act_die(&(*sim), (*sim)->info, i, &(*sim)->philo);
        if ((*sim)->active == 0)
            break ;
    }
}

static void odd_routine(t_sim **sim, int i)
{
    struct timeval  now;

    while ((*sim)->active == 1)
    {
        act_sleep((*sim)->info, i, &(*sim)->philo);
        act_think(i, &(*sim)->philo);
        act_die(&(*sim), (*sim)->info, i, &(*sim)->philo);
        if ((*sim)->active == 0)
            break ;
        //pthread_mutex_lock(&(*sim)->pair);
        pthread_mutex_lock(&(*sim)->forks[i]);
        gettimeofday(&now, NULL);
        printf(WHI "%d\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
        pthread_mutex_lock(&(*sim)->forks[i - 1]);
        //pthread_mutex_unlock(&(*sim)->pair);
        gettimeofday(&now, NULL);
        printf(WHI "%d\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
        act_eat((*sim)->info, i, &(*sim)->philo);
        pthread_mutex_unlock(&(*sim)->forks[i]);
        pthread_mutex_unlock(&(*sim)->forks[i - 1]);
    }
}*/

//NOTES
/*
    even index: same index and + 1
    odd index: same index and - 1

        act_think(i, &sim->philo);
        act_eat(sim->info, i, &sim->philo);
        act_sleep(sim->info, i, &sim->philo);
        act_die(&sim, sim->info, i, &sim->philo);

	acquire forks: acquire_own_fork + acquire_next_fork
	release forks

        pthread_mutex_lock(&sim->forks[i]);
        pthread_mutex_lock(&sim->forks[i + 1]);
        sim->philo[i].state = EATING;
        usleep(sim->info.time_to_eat);
        pthread_mutex_unlock(&sim->forks[i]);
        pthread_mutex_unlock(&sim->forks[i + 1]);
*/