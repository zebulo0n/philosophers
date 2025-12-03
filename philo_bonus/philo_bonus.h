/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:20:38 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/24 19:20:39 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	int					id;
	long				last_meal;
	int					meal_count;
	pid_t				pid;
	t_table				*table;
	pthread_t			monitor;

}						t_philo;

typedef struct s_table
{
	int					philo_nbr;
	int					full_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					dinner_nbr;
	long long			start_time;
	sem_t				*death_sem;
	sem_t				*write_sem;
	sem_t				*dine_sem;
	sem_t				*forks_sem;
	t_philo				*philos;
}						t_table;

int						str_err(char *str);
long					ft_atol(const char *nptr);
long long				get_time(void);
void					ft_usleep(long long time);

int						init_structs(t_table *table, int ac, char **av);

int						init_processes(t_table *table);
int						wait_processes(t_table *table);

void					routine(t_philo *philo);
void					print_action(t_philo *philo, char *str);
void					print_death(t_philo *philo);
int						philo_died(t_philo *philo);
int						philo_full(t_philo *philo);

void					kill_all(t_table *table);
void					clean_exit(t_philo *philo, int code);

#endif