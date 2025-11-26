/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:08:06 by lsarraci          #+#    #+#             */
/*   Updated: 2025/11/26 19:13:27 by lsarraci         ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

typedef enum e_state {
	THINKING,
	EATING,
	WAITING,
	HUNGRY,
	SLEEPING,
	DEAD
}	t_state;

struct	s_philo {
	int				philo_id;
	int				meals_taken;
	long			last_meal;
	t_state			state;
	pthread_t		trhead_id;
	t_mtx			*left_fork;
	t_mtx			*right_fork;
	t_table			*table;
};

struct s_table {
	int			phi_num;
	int			death_flag;
	int			meals_max;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
	long		start_time;
	t_mtx		*forks;
	t_mtx		print_mtx;
	t_mtx		die_mtx;
	t_mtx		event_mtx;
	t_philo		*philo;
};

/* ------------------utilities------------------------*/

int		is_valid_number(char *ch, int i);
long	ft_atol_safe(char *ch, int *error);
int		ft_strcmp(const char *c1, const char *c2);

/*------------------validation------------------------*/

int		arg_parser(int ac, char **av, int iter);
int		parse_args_to_table(int ac, char **av, t_table *table);
int		arg_range_validator(t_table *table);

/*------------------initialization--------------------*/

int		init_table(t_table *table, int i);
void	init_philosophers(t_table *table, int i);

/*------------------time utilities--------------------*/

long	get_time_ms(void);
int		smart_sleep(t_philo *philo, long sleep_time_ms);
void	print_state(t_philo *philo, char *message);

/*---------philosopher functions--------------------*/

void	*philo_routine(void *arg);
int		take_forks(t_philo *philo);
int		check_dead_flag(t_table *table);

/*---------monitor ----------------------------------*/

void	monitor(t_table *table);

#endif