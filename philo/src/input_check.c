/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:21:25 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/09 17:53:33 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	check_argc(int argc);
static int	check_isnum(int argc, char **argv);
static int	check_limits(int argc, char **argv, t_info *info);
static void	set_info(int i, unsigned int res, t_info *info);

int check_input(int argc, char **argv, t_info *info)
{
	if (!check_argc(argc))
		return (0);
	if (!check_isnum(argc, argv))
		return (0);
	if (!check_limits(argc, argv, info))
		return (0);
	return (1);
}

static int	check_argc(int argc)
{
	if (argc != 5)
	{
		write(2, "Wrong number or arguments\n", 26);
		print_usage();
		return (0);
	}
	return (1);
}

static int	check_isnum(int argc, char **argv)
{
	int	i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				write(2, "Invalid argument(s)\n", 20);
				print_usage();
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_limits(int argc, char **argv, t_info *info)
{
	unsigned long	res;
	int	i;
	int j;

	i = 1;
	while (i < argc)
	{
		res = 0;
		j = 0;
		while (argv[i][j])
		{
			res = res * 10 + (argv[i][j] - '0');
			if (res > UINT_MAX)
				return (print_above_limit());
			j++;
		}
		if (i == 1 && res == 0)
			return (print_philo_zero());
		set_info(i, (unsigned int)res, info);
		i++;
	}
	return (1);
}

static void	set_info(int i, unsigned int res, t_info *info)
{
	if (i == 1)
		info->n_philo = res;
	else if (i == 2)
		info->time_to_die = res;
	else if (i == 3)
		info->time_to_eat = res;
	else if (i == 4)
		info->time_to_sleep = res;
}