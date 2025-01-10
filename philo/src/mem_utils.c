/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:46:38 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 10:46:38 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_philo_array(t_philo **philo) //free: invalid pointer
{
	int	i;

	i = 0;
	while (philo[i])
	{
		free(philo[i]->thread_id);
		free(philo[i]);
		i++;
	}
	free(philo);
	return ;
}