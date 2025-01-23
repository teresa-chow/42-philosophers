/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	act_think(int i, t_philo **philo)
{
	struct timeval	now;

	(*philo)[i].state = THINKING;
	gettimeofday(&now, NULL);
	printf(WHI "%ld\t\t%d\t" NC CYA "is thinking\n" NC, now.tv_usec, i);
}

/* TODO: acquire and release forks check */
void	act_eat(t_sim **sim, t_info info, int i, t_philo **philo)
{
	struct timeval	now;

	(void)sim; //delete
	(*philo)[i].state = EATING;
	gettimeofday(&now, NULL);
	printf(WHI "%ld\t\t%d\t" NC GRN "is eating\n" NC, now.tv_usec, i);
	usleep(info.time_to_eat);
	gettimeofday(&(*philo)[i].last_meal, NULL);
}

/*void    act_eat(int i, t_sim *sim)
{
    thread_mutex_t act;
    struct timeval  now;
    
    acquire_forks
    acquire own (same index)
    acquire other
    eat – print msg X is eating
    gettimeofday(&now, NULL);
    printf("%ld\t%i is eating", now.tv_usec, i);
    //(time since) last_meal
}*/

void	act_sleep(t_info info, int i, t_philo **philo)
{
	struct timeval	now;

	(*philo)[i].state = THINKING;
	gettimeofday(&now, NULL);
	printf(WHI "%ld\t\t%d\t" NC BLU "is sleeping\n" NC, now.tv_usec, i);
	usleep(info.time_to_sleep);
}

void	act_die(t_sim **sim, t_info info, int i, t_philo **philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if ((unsigned int)(now.tv_usec
		- (*philo)[i].last_meal.tv_usec) > info.time_to_die)
	{
		(*philo)[i].state = STARVED;
		printf(WHI "%ld\t\t%d\t" NC RED "has died\n" NC, now.tv_usec, i);
		(*sim)->active = 0;
	}
	return ;
}

//print time / X died (no more than 10 ms after death)