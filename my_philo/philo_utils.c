/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:38:42 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 16:55:53 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	return(c >= '0' && c <= '9');
}

int	is_valid_number(char *ch, int i)
{
	if (!ch || !ch[0])
		return (0);
	if (ch[i] == '+')
		i++;
	if (!ch[i])
		return (0);
	while (ch[i])
	{
		if (!is_digit(ch[i]))
			return (0);
		i++;
	}
	return (1);
}

long	atol_safe(char *ch, int *error)
{
	long	temp;
	long	result;
	int		i;

	i = 0;
	result = 0;
	if (ch[i] == '+')
		i++;
	while (ch[i] && !is_digit(ch[i]))
	{
		temp = result * 10 + (ch[i] - '0');
		if (temp < result)
		{
			*error = 1;
			return (0);
		}
		result = temp;
		i++;
	}
	return (result);
}

int	strcmp(const char *c1, const char *c2)
{
	int	i;
	
	i = 0;
	while (c1[i] && c2[i] && c1[i] == c2[i])
		i++;
	return ((unsigned char) c1[i] - (unsigned char) c2[i]);
}