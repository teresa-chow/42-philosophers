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
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

// Min time caps (in milliseconds)
# define MIN_DIE 60
# define MIN_EAT 60
# define MIN_SLEEP 60

// Max thread & time caps (in milliseconds)
# define MAX_PHILO 1000
# define MAX_DIE 10000 /* 10 sec */
# define MAX_EAT 1000 /* 1 sec */
# define MAX_SLEEP 1000 /* 1 sec */

// Printf formatting
# define NC "\033[0m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define CYA "\033[0;36m"
# define WHI "\033[0;37m"

enum	e_state
{
	THINKING,
	FORK,
	EATING,
	SLEEPING,
	STARVED
};

// pthread_t and pthread_mutex_t op codes
enum	e_op
{
	CREATE,
	DETACH,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
};

typedef struct s_info
{
	unsigned int	n_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				n_times_to_eat;
}	t_info;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	pthread_mutex_t	state;
	bool			starved;
	pthread_mutex_t	counter;
	bool			full;
	int				n_meals;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	timer;
	unsigned long	last_meal;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	t_info				info;
	bool				active;
	pthread_mutex_t		status;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	t_philo				*philo;
	unsigned long		start;
}	t_sim;

/* ======================= PARSING & ERROR HANDLING ======================== */
int				check_input(int argc, char **argv, t_info *info);
// Error messages
int				err_limit(void);
int				err_philo_zero(void);
int				err_mutexes(t_sim *sim);
int				err_threads(t_sim *sim);
void			print_usage(void);
// Set info
void			set_info(int i, unsigned int res, t_info *info);

/* ============================= SIMULATION ================================ */
int				init_sim(t_sim *sim);
void			run_sim(t_sim *sim);
void			monitor_sim(t_sim *sim);
// Edge case
int				check_edge_cases(t_sim *sim);
// Init simulation utils
void			assign_forks(t_sim *sim);
// General thread and mutex handling
int				handle_mutex(pthread_mutex_t *mutex, enum e_op op);
int				handle_thread(pthread_t *thread,
					void *(*start_routine) (void *), void *arg, enum e_op op);
// Shared data (mutex protected): setters and getters
void			set_bool(pthread_mutex_t *mutex, bool *ptr, bool value);
bool			get_bool(pthread_mutex_t *mutex, bool *ptr);
void			set_ulong(pthread_mutex_t *mutex, unsigned long *ptr,
					unsigned long value);
unsigned long	get_ulong(pthread_mutex_t *mutex, unsigned long *ptr);
// Thread routines
void			*philo_routine(void *arg);
void			*single_routine(void *arg);
// Time tracking
unsigned long	get_time_ms(void);
void			usleep_limit(unsigned long time_ms);
// Actions
void			acquire_forks(t_philo **philo);
void			release_forks(t_philo **philo);
void			act_think(t_philo **philo);
void			act_eat(t_philo **philo);
void			act_sleep(t_philo **philo);
// State messages
void			print_state(t_philo *philo, enum e_state state,
					unsigned int id);
void			print_philos_full(t_sim *sim);
// Monitoring functions
bool			will_starve(t_philo **philo, unsigned long act_time_ms);
void			starvation_checker(t_sim *sim);
void			philos_full_checker(t_sim *sim);
void			time_checker(t_sim *sim);
// End simulation
bool			sim_active(t_sim *sim);
void			end_sim(t_sim *sim);

#endif
