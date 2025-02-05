/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:28:19 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/05 18:28:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_philos_full(void)
{
	printf(GRN "Simulation stopped: all" NC);
	printf(GRN " philosophers have eaten the minimum amount of times.\n" NC);
}