/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:59:41 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:14:47 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	smart_sleep(t_philo *philo, long sleep_time_ms)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < sleep_time_ms)
	{
		pthread_mutex_lock(&philo->table->die_mtx);
		if (philo->table->death_flag)
		{
			pthread_mutex_unlock(&philo->table->die_mtx);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->die_mtx);
		usleep(500);
	}
	return (1);
}

void	print_state(t_philo *philo, char *message)
{
	long	timestamp;
	int		death_msg;

	death_msg = (ft_strcmp(message, "died") == 0);
	pthread_mutex_lock(&philo->table->die_mtx);
	pthread_mutex_lock(&philo->table->print_mtx);
	if (philo->table->death_flag && !death_msg)
	{
		pthread_mutex_unlock(&philo->table->die_mtx);
		pthread_mutex_unlock(&philo->table->print_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->table->die_mtx);
	timestamp = get_time_ms() - philo->table->start_time;
	printf("%ld philosopher %d %s\n", timestamp, philo->philo_id, message);
	pthread_mutex_unlock(&philo->table->print_mtx);
}
