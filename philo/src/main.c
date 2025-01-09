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

/*void	*routine(void *info)
{
	*(t_info *)info;
	pthread_mutex_lock(&mutex); //not being passed here
	printf("Test from threads\n");
	printf("Ending thread\n");
	usleep((t_info *)info->time_to_eat);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}*/

int	main(int argc, char **argv)
{
	//int	i;
	t_info	info;
	//pthread_t	*philo;
	//pthread_mutex_t	*forks;

	if (!check_input(argc, argv, &info))
		return (1);
	printf("Input OK\n");
		/*i = 0;
		while (i < info.n_philo)
		{
			pthread_mutex_init(&forks[i], NULL);
			i++;
		}*/
	return (0);
}