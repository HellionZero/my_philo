/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:13:21 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:29:42 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_parser(int ac, char **av, int iter)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [number_of_times_each_");
		printf("philosopher_must_eat]\n");
		return (0);
	}
	while (iter < ac)
	{
		if (!is_valid_number(av[iter], 0))
		{
			printf("Error: Argument %d is not a valid positive number\n", iter);
			return (0);
		}
		iter++;
	}
	return (1);
}

int	parse_args_to_table(int ac, char **av, t_table *table)
{
	int	error;

	error = 0;
	table->phi_num = ft_atol_safe(av[1], &error);
	if (error)
		return (printf("Error: Number of philosophers overflow\n"), 0);
	table->time_to_die = ft_atol_safe(av[2], &error);
	if (error)
		return (printf("Error: Time to die overflow\n"), 0);
	table->time_to_eat = ft_atol_safe(av[3], &error);
	if (error)
		return (printf("Error: Time to eat overflow\n"), 0);
	table->time_to_sleep = ft_atol_safe(av[4], &error);
	if (error)
		return (printf("Error: Time to sleep overflow\n"), 0);
	if (ac == 6)
	{
		table->meals_max = ft_atol_safe(av[5], &error);
		if (error)
			return (printf("Error: Number of meals overflow\n"), 0);
	}
	else
		table->meals_max = -1;
	return (1);
}

int	arg_range_validator(t_table *table)
{
	if (table->phi_num < 1 || table->phi_num > 200)
		return (printf("Error: Number of philosophers must be 1-200\n"), 0);
	if (table->time_to_die < 60)
		return (printf("Error: Time to die must be at least 60ms\n"), 0);
	if (table->time_to_eat < 60)
		return (printf("Error: Time to eat must be at least 60ms\n"), 0);
	if (table->time_to_sleep < 60)
		return (printf("Error: Time to sleep must be at least 60ms\n"), 0);
	if (table->meals_max == 0)
		return (printf("Error: Number of meals must be positive\n"), 0);
	return (1);
}
