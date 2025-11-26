/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:08:06 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 16:55:44 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <limits.h>

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define BLINK "\033[5m"
# define REVERSE "\033[7m"
# define INVISIBLE "\033[8m"

# define F_BLACK "\033[30m"
# define F_RED "\033[31m"
# define F_GREEN "\033[32m"
# define F_YELLOW "\033[33m"
# define F_BLUE "\033[34m"
# define F_MAGENTA "\033[35m"
# define F_CYAN "\033[36m"
# define F_WHITE "\033[37m"

typedef struct s_philo			t_philo;
typedef struct s_table			t_table;
typedef struct pthread_mutex_t	t_mtx;

struct	s_philo {
	int				philo_id;
	int				meals_taken;
	long			meal_timer;
	long			last_meal;
	t_table			*table;
	pthread_t		trhead_id;
	t_mtx			*left_fork;
	t_mtx			*right_fork;
};

struct s_table {
	t_philo		*philo;
};

/* ------------------utilities------------------------*/

int		is_valid_number(char *ch, int i);
long	atol_safe(char *ch, int *error);
int		strcmp(const char *c1, const char *c2);

/*------------------validation------------------------*/



#endif