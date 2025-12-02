/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:29:33 by lsarraci          #+#    #+#             */
/*   Updated: 2025/12/01 17:28:10 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phi_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&table->write_mtx, NULL) != 0)
		return (0);
	return (1);
}

int	init_table(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->phi_num);
	if (!table->philo)
		return (0);
	table->forks = malloc(sizeof(t_mtx) * table->phi_num);
	if (!table->forks)
	{
		free(table->philo);
		return (0);
	}
	if (!init_mutexes(table))
	{
		free(table->philo);
		free(table->forks);
		return (0);
	}
	table->death_flag = 0;
	table->start_time = 0;
	return (1);
}

void	init_philosophers(t_table *table, int i)
{
	while (i < table->phi_num)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].meals_taken = 0;
		table->philo[i].last_meal = table->start_time;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->phi_num];
		i++;
	}
}
