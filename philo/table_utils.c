/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:21:14 by lsarraci          #+#    #+#             */
/*   Updated: 2025/12/04 15:33:49 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_start(t_philo *philo)
{
	long	start;

	start = 0;
	while (start == 0)
	{
		usleep(100);
		start = get_start_time(philo->table);
	}
	pthread_mutex_lock(&philo->table->write_mtx);
	philo->last_meal = start;
	philo->table->ready_count++;
	pthread_mutex_unlock(&philo->table->write_mtx);
}

void	print_state(t_philo *philo, char *message)
{
	long	timestamp;
	long	start;
	int		is_death;

	is_death = (ft_strcmp(message, "died") == 0);
	start = get_start_time(philo->table);
	pthread_mutex_lock(&philo->table->write_mtx);
	if (philo->table->death_flag && !is_death)
	{
		pthread_mutex_unlock(&philo->table->write_mtx);
		return ;
	}
	timestamp = get_time_ms();
	printf("%ld %d %s\n", timestamp - start, philo->philo_id, message);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
