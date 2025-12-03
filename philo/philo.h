/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:05:48 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/24 19:25:00 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_thrd;
typedef struct s_table	t_table;

typedef struct s_philo
{
	t_thrd				thread;
	int					id;
	long				last_meal;
	int					meal_count;
	int					is_full;
	t_mtx				*left_fork;
	t_mtx				*right_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_nbr;
	int					full_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					dinner_nbr;
	int					death;
	long long			start_time;
	t_mtx				*forks;
	t_mtx				death_mtx;
	t_mtx				write_mtx;
	t_mtx				full_mtx;
	t_philo				*philos;
}						t_table;

int						str_err(char *str);
long long				get_time(void);
void					ft_usleep(long long time);
void					print_action(t_philo *philo, char *action);
void					print_death(t_philo *philo);
long					ft_atol(const char *nptr);
void					free_all(t_table *table);

int						init_structs(t_table *table, int ac, char **av);

void					*routine(void *arg);
void					monitor(t_table *table);
int						init_threads(t_table *table);
int						join_threads(t_table *table);

#endif