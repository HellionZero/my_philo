/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:29:33 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:14:03 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, int i)
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
	while (i < table->phi_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&table->print_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->die_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->event_mtx, NULL) != 0)
		return (0);
	table->death_flag = 0;
	table->start_time = get_time_ms();
	return (1);
}

void	init_philosophers(t_table *table, int i)
{
	while (i < table->phi_num)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].meals_taken = 0;
		table->philo[i].last_meal = table->start_time;
		table->philo[i].state = THINKING;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->phi_num];
		i++;
	}
}
