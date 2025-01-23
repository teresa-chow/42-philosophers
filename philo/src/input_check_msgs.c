/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_msgs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:51:23 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 09:22:32 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	print_above_limit(void)
{
	write(2, "Invalid argument(s): value(s) above limit\n", 42);
	return (0);
}

int	print_philo_zero(void)
{
	write(2, "Insufficient number of philosophers to run "
		"a simulation\n", 56);
	print_usage();
	return (0);
}

void	print_usage(void)
{
	write(1, "Usage: ./philo <number_of_philosophers> <time_to_die> "
		"<time_to_eat> <time_to_sleep>\n", 84);
}
