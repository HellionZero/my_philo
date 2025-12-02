/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:59:41 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/27 16:13:10 by lsarraci         ###   ########.fr       */
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
	long	elapsed;

	start = get_time_ms();
	while (1)
	{
		if (check_dead_flag(philo->table))
			return (0);
		elapsed = get_time_ms() - start;
		if (elapsed >= sleep_time_ms)
			break ;
		usleep(1000);
	}
	return (1);
}

void	print_state_with_time(t_philo *philo, char *message, long timestamp)
{
	int		death_msg;

	death_msg = (ft_strcmp(message, "died") == 0);
	pthread_mutex_lock(&philo->table->write_mtx);
	if (philo->table->death_flag && !death_msg)
	{
		pthread_mutex_unlock(&philo->table->write_mtx);
		return ;
	}
	printf("%ld %d %s\n", timestamp - philo->table->start_time,
		philo->philo_id, message);
	pthread_mutex_unlock(&philo->table->write_mtx);
}

void	print_state(t_philo *philo, char *message)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write_mtx);
	if (philo->table->death_flag)
	{
		pthread_mutex_unlock(&philo->table->write_mtx);
		return ;
	}
	timestamp = get_time_ms();
	printf("%ld %d %s\n", timestamp - philo->table->start_time,
		philo->philo_id, message);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
