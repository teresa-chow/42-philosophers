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

static int	check_mutex(int status, enum e_op op);
static int	check_thread(int status, enum e_op op);

int	handle_mutex(pthread_mutex_t *mutex, enum e_op op)
{
	int ret;

	if (op == INIT)
		ret = check_mutex(pthread_mutex_init(mutex, NULL), op);
	else if (op == LOCK)
		ret = check_mutex(pthread_mutex_lock(mutex), op);
	else if (op == UNLOCK)
		ret = check_mutex(pthread_mutex_unlock(mutex), op);
	else if (op == DESTROY)
		ret = check_mutex(pthread_mutex_destroy(mutex), op);
	return (ret);
}

static int	check_mutex(int status, enum e_op op)
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

	if (op == CREATE)
		ret = check_thread(pthread_create(thread, NULL, start_routine, arg), op);
	else if (op == DETACH)
		ret = check_thread(pthread_detach(thread), op);
	else if (op == JOIN)
		ret = check_thread(pthread_join(thread, NULL), op);
	return (ret);
}

static int	check_thread(int status, enum e_op op)
{
	if (status == 0)
		return (0);
	else
	{
		write(2, "Thread error\n", 12);
		return (-1);
	}
}