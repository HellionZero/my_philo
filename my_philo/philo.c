/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:54:29 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:13:07 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_flag(t_table *table)
{
	int	is_dead;

	pthread_mutex_lock(&table->die_mtx);
	is_dead = table->death_flag;
	pthread_mutex_unlock(&table->die_mtx);
	return (is_dead);
}

static void	eat(t_philo *philo)
{
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->table->event_mtx);
	philo->last_meal = get_time_ms();
	philo->meals_taken++;
	pthread_mutex_unlock(&philo->table->event_mtx);
	smart_sleep(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	sleep_and_think(t_philo *philo)
{
	print_state(philo, "is sleeping");
	if (!smart_sleep(philo, philo->table->time_to_sleep))
		return ;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_dead_flag(philo->table))
	{
		philo->state = THINKING;
		if (check_dead_flag(philo->table))
			break ;
		print_state(philo, "is thinking");
		philo->state = HUNGRY;
		if (!take_forks(philo))
			break ;
		philo->state = EATING;
		eat(philo);
		if (check_dead_flag(philo->table))
			break ;
		philo->state = SLEEPING;
		sleep_and_think(philo);
	}
	return (NULL);
}
