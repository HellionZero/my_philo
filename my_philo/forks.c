/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:17:48 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:59:18 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	order_forks(t_philo *philo, t_mtx **first, t_mtx **second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static int	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

static int	try_take_fork(t_philo *philo, t_mtx *fork, t_mtx *other_fork)
{
	pthread_mutex_lock(fork);
	print_state(philo, "has taken a fork");
	if (check_dead_flag(philo->table))
	{
		pthread_mutex_unlock(fork);
		if (other_fork)
			pthread_mutex_unlock(other_fork);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	t_mtx	*first;
	t_mtx	*second;

	if (check_dead_flag(philo->table))
		return (0);
	if (philo->table->phi_num == 1)
		return (handle_single_philo(philo));
	order_forks(philo, &first, &second);
	if (!try_take_fork(philo, first, NULL))
		return (0);
	if (!try_take_fork(philo, second, first))
		return (0);
	return (1);
}
