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

// Max thread & time caps
# define MAX_PHILO 50
# define MAX_DIE 10000000 /* 10 sec */
# define MAX_EAT 1000000 /* 1 sec */
# define MAX_SLEEP 1000000 /* 1 sec */

// Printf formatting
# define NC "\033[0m"
// Regular
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define CYA "\033[0;36m"
# define WHI "\033[0;37m"

enum	e_state
{
	NONE,
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

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	bool				taken;
}	t_fork;

typedef struct s_philo
{
	unsigned int	index;
	pthread_t		thread;
	struct timeval	last_meal;
	enum e_state	state;
	t_fork			*fork1;
	t_fork			*fork2;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	t_info				info;
	bool				active;
	pthread_t			main;
	t_fork				*forks;
	t_philo				*philo;
	struct timeval		start;
	pthread_mutex_t		check;
}	t_sim;

/* ======================= PARSING & ERROR HANDLING ======================== */
int		check_input(int argc, char **argv, t_info *info);
// Input value errors
int		print_above_limit(void);
int		print_philo_zero(void);
void	print_usage(void);
// Memory errors
int		err_forks(void);
int		err_threads(t_sim *sim, t_philo **philo);
// Set info
void	set_info(int i, unsigned int res, t_info *info);

/* ============================= SIMULATION ================================ */
int		init_simulation(t_sim *simulation);
// Thread routines
void	*main_routine(void *arg);
void	*philo_routine(void *arg);
// Actions
int		check_forks(int i, t_sim *sim);
void	acquire_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	act_think(int i, t_philo **philo);
void	act_eat(t_info info, int i, t_philo **philo);
void	act_sleep(t_info info, int i, t_philo **philo);
void	act_die(t_sim **sim, t_info info, int i, t_philo **philo);
// End simulation
void	end_simulation(t_sim *sim);

/* =========================== MEMORY HANDLING ============================= */
void	free_forks_array(t_sim *sim);
void	free_philo_array(t_philo **philo);

#endif
