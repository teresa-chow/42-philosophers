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
	(void)argv;
    if (argc != 4)
	{
		write(2, "Wrong number or arguments\n", 26);
		write(1, "Usage: ./philo <number_of_philosophers> <time_to_die> "
        "<time_to_eat> <time_to_sleep>\n", 84);
		return (1);
    }
	/*argv[1]int number_of_philosophers
	argv[2]int time_to_die
	argv[3]int time_to_eat
	argc[4]int time_to_sleep*/
	return (0);
}

/*
pthread_t thread;
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
thread_create(&thread, NULL, thread_routine, NULL);

pthread_mutex_t mutex;
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr); // create the mutex
int pthread_mutex_lock(pthread_mutex_t *mutex));
int pthread_mutex_unlock(pthread_mutex_t *mutex); // lock and unlock mutexes (to avoid data races)
int pthread_mutex_destroy(pthread_mutex_t *mutex); // destroy (unlocked) mutex when no longer needed

! careful to avoid deadlock !

1 philosopher to N philosophers
1 philosopher always dies ? (can never get two forks)

philosopher's forks are mutexes to be locked? (philosophers need two forks to eat, none to sleep or think)

how are scenarios different for odd and even numbers of philosophers ?
*/
