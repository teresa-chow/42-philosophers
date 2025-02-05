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
	if (sim.info.n_times_to_eat == 0)
	{
		print_philos_full();
		return (0);
	}
	if ((init_sim(&sim)) == -1)
		return (1);
	end_sim(&sim);
	return (0);
}

/*
To do:
- one philosopher only scenario
- test program with 0 and 1 as time_to_xxx -- needs additional protection ?
- MIN_USLEEP 60 ?
- set philosopher as full
- set all as full and exit program
- check if sim_init error cases will result in leaks
- deal with starved mid-action scenario
*/