/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:58:10 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/23 14:25:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_info(int i, unsigned int res, t_info *info)
{
	if (i == 1)
		info->n_philo = res;
	else if (i == 2)
		info->time_to_die = res * 1000;
	else if (i == 3)
		info->time_to_eat = res * 1000;
	else if (i == 4)
		info->time_to_sleep = res * 1000;
}
