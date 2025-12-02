/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:07:55 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:32:24 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_and_parse(int argc, char **argv, t_table *table)
{
	if (!arg_parser(argc, argv, 1))
		return (0);
	if (!parse_args_to_table(argc, argv, table))
		return (0);
	if (!arg_range_validator(table))
		return (0);
	return (1);
}

static int	setup_simulation(t_table *table)
{
	if (!init_table(table))
		return (0);
	init_philosophers(table, 0);
	return (1);
}

static int	run_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phi_num)
	{
		if (pthread_create(&table->philo[i].trhead_id, NULL,
				philo_routine, &table->philo[i]) != 0)
			return (0);
		i++;
	}
	table->start_time = get_time_ms();
	usleep(1000);
	monitor(table);
	i = 0;
	while (i < table->phi_num)
	{
		pthread_join(table->philo[i].trhead_id, NULL);
		i++;
	}
	return (1);
}

static void	cleanup(t_table *table, int i)
{
	while (i < table->phi_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->write_mtx);
	free(table->philo);
	free(table->forks);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!validate_and_parse(argc, argv, &table))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (!setup_simulation(&table))
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	if (!run_simulation(&table))
	{
		printf("Error: Simulation failed\n");
		return (1);
	}
	cleanup(&table, 0);
	return (0);
}
