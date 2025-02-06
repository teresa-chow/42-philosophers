/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:08:47 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/06 15:09:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (!check_input(argc, argv, &sim.info))
		return (1);
	if ((init_sim(&sim)) == -1)
		return (1);
	if ((sim.info.n_times_to_eat > 0) && (sim.info.n_philo > 1))
		end_sim(&sim);
	return (0);
}

/*
TO DO:
- set all as full and exit program

TEST:
- test program with 0 and 1 as time_to_xxx - MIN_USLEEP 60 ?

FIXED:
- sim_init error cases will result in leaks

DONE:
- one philosopher only scenario
- set philosopher as full
- deal with starved mid-action scenario
*/