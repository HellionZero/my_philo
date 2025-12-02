/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:54:29 by lsarraci          #+#    #+#             */
/*   Updated: 2025/12/02 14:48:12 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_flag(t_table *table)
{
	int	is_dead;

	pthread_mutex_lock(&table->write_mtx);
	is_dead = table->death_flag;
	pthread_mutex_unlock(&table->write_mtx);
	return (is_dead);
}

static void	eat(t_philo *philo)
{
	long	eat_time;
	int		should_print;

	pthread_mutex_lock(&philo->table->write_mtx);
	should_print = !philo->table->death_flag;
	if (!should_print)
	{
		pthread_mutex_unlock(&philo->table->write_mtx);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	eat_time = get_time_ms();
	philo->last_meal = eat_time;
	philo->meals_taken++;
	printf("%ld %d is eating\n", eat_time - philo->table->start_time,
		philo->philo_id);
	pthread_mutex_unlock(&philo->table->write_mtx);
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

static int	has_eaten_enough(t_philo *philo)
{
	int	enough;

	pthread_mutex_lock(&philo->table->write_mtx);
	enough = (philo->table->meals_max != -1
			&& philo->meals_taken >= philo->table->meals_max);
	pthread_mutex_unlock(&philo->table->write_mtx);
	return (enough);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->table->start_time == 0)
		usleep(100);
	pthread_mutex_lock(&philo->table->write_mtx);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->table->write_mtx);
	while (!check_dead_flag(philo->table) && !has_eaten_enough(philo))
	{
		print_state(philo, "is thinking");
		if (!take_forks(philo))
			break ;
		if (check_dead_flag(philo->table))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		eat(philo);
		if (check_dead_flag(philo->table))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
