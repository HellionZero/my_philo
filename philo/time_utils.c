/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:59:41 by lsarraci          #+#    #+#             */
/*   Updated: 2025/12/04 15:25:09 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_start_time(t_table *table)
{
	long	time;

	pthread_mutex_lock(&table->start_mtx);
	time = table->start_time;
	pthread_mutex_unlock(&table->start_mtx);
	return (time);
}

void	set_start_time(t_table *table, long time)
{
	pthread_mutex_lock(&table->start_mtx);
	table->start_time = time;
	pthread_mutex_unlock(&table->start_mtx);
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
