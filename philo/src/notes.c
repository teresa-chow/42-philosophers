/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:13:48 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/08 14:16:04 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *data)
{
	(void)data;
	pthread_mutex_lock(&mutex); //not being passed here
	printf("Test from threads\n");
	printf("Ending thread\n");
	sleep(3);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	t1;
	pthread_t	t2;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1); //to pass function as parameter, one passes a function pointer, last parameter is for the argument to be passed to the routine
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3); //waits for thread to terminate
	if (pthread_join(t2, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex);
	/*if (argc != 4)
	{
		write(2, "Wrong number or arguments\n", 26);
		write(1, "Usage: ./philo <number_of_philosophers> <time_to_die> "
		"<time_to_eat> <time_to_sleep>\n", 84);
		return (1);
	}*/
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
