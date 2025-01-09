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
	j = 0;
	while (i < argc && argv[i])
	{
		res = 0;
		while (argv[i][j])
		{
			res = res * 10 + (argv[i][j] - '0');
			if (res > UINT_MAX)
			{
				write(2, "Invalid argument(s): value(s) above limit\n", 42);
				return (0);
			}
			j++;
		}
		if (i == 1 && res == 0)
		{
			write(2, "Insufficient number of philosophers to run "
			"a simulation\n", 56);
			return (0);
		}
		set_info(info);
		i++;
	}
	return (1);
}