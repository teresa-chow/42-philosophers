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
# include <sys/time.h>
# include <pthread.h>

// Printf formatting
#define NC "\033[0m"
// Regular
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define CYA "\033[0;36m"
#define WHI "\033[0;37m"

enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	STARVED
};

typedef struct s_info
{
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}	t_info;

typedef struct s_philo
{
	int	index;
	pthread_t	thread;
	struct timeval	last_meal;
	enum e_state	state;
}	t_philo;

typedef struct s_sim
{
	t_info	info;
	bool	active;
	pthread_t	main;
	pthread_mutex_t	counter;
	pthread_mutex_t	pair;
	//pthread_mutex_t	print;
	t_philo	*philo;
	pthread_mutex_t	*forks;
	struct timeval	start;
}	t_sim;


/* ======================= PARSING & ERROR HANDLING ======================== */
int check_input(int argc, char **argv, t_info *info);
// Additional error messages
int	print_above_limit(void);
int	print_philo_zero(void);
void	print_usage(void);

/* ============================= SIMULATION ================================ */
void	init_simulation(t_sim *simulation); //review return value
// Thread routines
void	*main_routine(void *arg);
void	*philo_routine(void *arg);
// Actions
void    act_think(int i, t_philo **philo);
void    act_eat(t_sim **sim, t_info info, int i, t_philo **philo);
void    act_sleep(t_info info, int i, t_philo **philo);
void    act_die(t_sim **sim, t_info info, int i, t_philo **philo);

/* =========================== MEMORY HANDLING ============================= */
void	free_forks_array(t_info info, pthread_mutex_t **forks);
void	free_philo_array(t_info info, t_philo **philo);

#endif
