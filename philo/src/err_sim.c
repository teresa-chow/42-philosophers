/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:39:29 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/27 09:39:29 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	err_forks(void)
{
	write(2, "Failed to create forks\n", 23);
	return (-1);
}

int	err_threads(t_sim *sim, t_philo **philo)
{
	free_forks_array(sim);
	free_philo_array(&(*philo));
	write(2, "Failed to create threads\n", 25);
	return (-1);
}