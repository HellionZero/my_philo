/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:54:29 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/28 18:04:36 by lsarraci         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->table->write_mtx);
	eat_time = get_time_ms();
	philo->last_meal = eat_time;
	philo->meals_taken++;
	pthread_mutex_unlock(&philo->table->write_mtx);
	print_state_with_time(philo, "is eating", eat_time);
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
		if (!take_forks(philo))
			break ;
		eat(philo);
		sleep_and_think(philo);
		print_state(philo, "is thinking");
	}
	return (NULL);
}

/*---------- write before philo_routine  ------------------------------

#ifdef DEBUG
	debug_print_state(philo);
#endif

---------------------------------------------------------------------*/
