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
# include <sys/time.h>
# include <pthread.h>

// Max thread & time caps (in milliseconds)
# define MAX_PHILO 200
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
	int	n_times_to_eat; // added, still unused
}	t_info;

typedef struct s_fork
{
	unsigned int		id;
	pthread_mutex_t		mutex;
}	t_fork;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	bool			full; // added, still unused
	int				n_meals;
	enum e_state	state;
	t_fork			*fork1;
	t_fork			*fork2;
	unsigned long	last_meal;
	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	t_info				info;
	bool				active;
	pthread_mutex_t		status;
	pthread_mutex_t		print;
	pthread_mutex_t		checker;
	pthread_t			main;
	t_fork				*forks;
	t_philo				*philo;
	unsigned long		start;
}	t_sim;

/* ======================= PARSING & ERROR HANDLING ======================== */
int		check_input(int argc, char **argv, t_info *info);
// Error messages
int		err_above_limit(void);
int		err_philo_zero(void);
int		err_mutexes(void);
int		err_threads(void);
void	print_usage(void);
// Set info
void	set_info(int i, unsigned int res, t_info *info);

/* ============================= SIMULATION ================================ */
int		init_sim(t_sim *sim);
// General thread and mutex handling
int		handle_mutex(pthread_mutex_t *mutex, enum e_op op);
int		handle_thread(pthread_t *thread, void *(*start_routine) (void *),
		void *arg, enum e_op op);
// Shared data (mutex protected): setters and getters
void	set_bool(pthread_mutex_t *mutex, bool *ptr, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *ptr);
void	set_unsigned_long(pthread_mutex_t *mutex, unsigned long *ptr,
		unsigned long value);
unsigned long	get_unsigned_long(pthread_mutex_t *mutex, unsigned long *ptr);
// Thread routines
void	*main_routine(void *arg);
void	*philo_routine(void *arg);
// Time tracking
unsigned long	get_time_ms(t_sim *sim);
void	usleep_limit(unsigned long time_ms, t_sim *sim);
// Actions
void	acquire_forks(t_philo **philo);
void	release_forks(t_philo **philo);
void	act_think(t_philo **philo);
void	act_eat(t_philo **philo);
void	act_sleep(t_philo **philo);
void	act_die(t_philo **philo);
// End simulation
bool	starvation_checker(t_sim *sim, unsigned int i);
//bool	full_checker(t_sim *sim);
bool	sim_active(t_sim *sim);
void	end_sim(t_sim *sim);

#endif
