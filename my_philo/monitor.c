/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:41:30 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:32:48 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_table *table, int i)
{
	int	all_done;

	if (table->meals_max == -1)
		return (0);
	all_done = 1;
	while (i < table->phi_num)
	{
		pthread_mutex_lock(&table->event_mtx);
		if (table->philo[i].meals_taken < table->meals_max)
			all_done = 0;
		pthread_mutex_unlock(&table->event_mtx);
		i++;
	}
	return (all_done);
}

static int	is_dead(t_table *table, int i)
{
	long	current;
	long	time_since_meal;
	t_philo	*philo;

	while (i < table->phi_num)
	{
		philo = &table->philo[i];
		pthread_mutex_lock(&table->event_mtx);
		current = get_time_ms();
		time_since_meal = current - philo->last_meal;
		pthread_mutex_unlock(&table->event_mtx);
		if (time_since_meal > table->time_to_die)
		{
			pthread_mutex_lock(&table->die_mtx);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->die_mtx);
			philo->state = DEAD;
			print_state(philo, "died");
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor(t_table *table)
{
	while (1)
	{
		if (is_dead(table, 0))
			return ;
		if (check_all_ate(table, 0))
		{
			pthread_mutex_lock(&table->die_mtx);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->die_mtx);
			pthread_mutex_lock(&table->print_mtx);
			printf("All philosophers have eaten %d times\n",
				table->meals_max);
			pthread_mutex_unlock(&table->print_mtx);
			return;
		}
		usleep(1000);
	}
}
