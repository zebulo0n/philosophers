/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:05:43 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/22 15:27:09 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_table *table, int i)
{
	long long	timestamp;

	pthread_mutex_lock(&table->death_mtx);
	timestamp = get_time();
	if ((timestamp - table->philos[i].last_meal) > table->time_to_die)
	{
		table->death = 1;
		print_death(&table->philos[i]);
		pthread_mutex_unlock(&table->death_mtx);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mtx);
	return (0);
}

int	philos_full(t_table *table)
{
	pthread_mutex_lock(&table->full_mtx);
	if (table->dinner_nbr != -1 && table->full_philos == table->philo_nbr)
	{
		pthread_mutex_unlock(&table->full_mtx);
		pthread_mutex_lock(&table->death_mtx);
		table->death = 1;
		pthread_mutex_unlock(&table->death_mtx);
		return (1);
	}
	pthread_mutex_unlock(&table->full_mtx);
	return (0);
}

void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (philo_dead(table, i))
				return ;
			if (philos_full(table))
				return ;
			i++;
		}
		usleep(1000);
	}
}

int	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL, routine,
				&table->philos[i]) != 0)
			return (str_err("Thread creation failed."));
		i++;
	}
	return (1);
}

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (str_err("Thread joining failed."));
		i++;
	}
	return (1);
}
