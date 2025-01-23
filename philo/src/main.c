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
	int sim_error;

	sim_error = 0;
	if (!check_input(argc, argv, &sim.info))
		return (1);
	sim_error = init_simulation(&sim);
	//if (sim_error != 0)
		//TODO: deal with simulation errors
	//free_forks_array(sim.info, &sim.forks);
	//free_philo_array(sim.info, &sim.philo);
	return (0);
}
