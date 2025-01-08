/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:11:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/06 15:22:25 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

/* Colors for formatting output */
#define NC "\e[0m"
#define YEL "\e[33m"
#define YEL_B "\e[1;33m"
#define RED "\e[31m"
#define GRN "\e[32m"

typedef struct s_info
{
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_info;

enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
};

#endif
