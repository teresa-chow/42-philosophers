/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:21:25 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/08 15:21:25 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int check_input(int argc, char **argv)
{
    if (argc != 4)
	{
		write(2, "Wrong number or arguments\n", 26);
		write(1, "Usage: ./philo <number_of_philosophers> <time_to_die> "
		"<time_to_eat> <time_to_sleep>\n", 84);
		return (1);
	}
}