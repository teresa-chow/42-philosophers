/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pthread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:03:02 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/29 09:03:02 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_mutex(int status);
static int	check_thread(int status);

int	handle_mutex(pthread_mutex_t *mutex, enum e_op op)
{
	int ret;

	ret = -1;
	if (op == INIT)
		ret = check_mutex(pthread_mutex_init(mutex, NULL));
	else if (op == LOCK)
		ret = check_mutex(pthread_mutex_lock(mutex));
	else if (op == UNLOCK)
		ret = check_mutex(pthread_mutex_unlock(mutex));
	else if (op == DESTROY)
		ret = check_mutex(pthread_mutex_destroy(mutex));
	return (ret);
}

static int	check_mutex(int status)
{
	if (status == 0)
		return (0);
	else
	{
		write(2, "Mutex error\n", 12);
		return (-1);
	}
}

int	handle_thread(pthread_t *thread, void *(*start_routine) (void *), void *arg, enum e_op op)
{
	int ret;

	ret = -1;
	if (op == CREATE)
		ret = check_thread(pthread_create(thread, NULL, start_routine, arg));
	else if (op == DETACH)
		ret = check_thread(pthread_detach(*thread));
	else if (op == JOIN)
		ret = check_thread(pthread_join(*thread, NULL));
	return (ret);
}

static int	check_thread(int status)
{
	if (status == 0)
		return (0);
	else
	{
		write(2, "Thread error\n", 12);
		return (-1);
	}
}