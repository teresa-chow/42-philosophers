/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:51:10 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/29 14:51:10 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_bool(pthread_mutex_t *mutex, bool *ptr, bool value)
{
	handle_mutex(mutex, LOCK);
	*ptr = value;
	handle_mutex(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *ptr)
{
	bool	value;
	
	handle_mutex(mutex, LOCK);
	value = *ptr;
	handle_mutex(mutex, UNLOCK);
	return (value);
}