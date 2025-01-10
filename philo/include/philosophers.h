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
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>

typedef struct s_info
{
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}	t_info;

enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	STARVED
};

typedef struct s_philo
{
	pthread_t	*thread_id;
	bool	fork_left;
	bool	fork_right;
	enum e_state	state;
}	t_philo;

typedef struct s_sim
{
	bool	active;
	t_philo	*philo;
	pthread_mutex_t	*forks;
}	t_sim;


/* ======================= PARSING & ERROR HANDLING ======================== */
int check_input(int argc, char **argv, t_info *info);
// Additional error messages
int	print_above_limit(void);
int	print_philo_zero(void);
void	print_usage(void);

void	init_simulation(t_info info, t_sim *simulation); //review return value

/* =========================== MEMORY HANDLING ============================= */
//void	free_philo_array(t_philo **philo);

#endif
