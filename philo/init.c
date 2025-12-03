/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:05:24 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/22 15:29:38 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_table *table, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		table->philo_nbr = (int)ft_atol(av[1]);
		if (table->philo_nbr <= 0 || table->philo_nbr > 200)
			return (str_err("Number of philosophers must be under 200."));
		table->time_to_die = ft_atol(av[2]);
		table->time_to_eat = ft_atol(av[3]);
		table->time_to_sleep = ft_atol(av[4]);
		if (table->time_to_die < 60 || table->time_to_eat < 60
			|| table->time_to_sleep < 60)
			return (str_err("Timestamps must be greater than 60ms."));
		if (ac == 6)
		{
			table->dinner_nbr = (int)ft_atol(av[5]);
			if (table->dinner_nbr <= 0)
				return (str_err("Required meals must be greater than 0."));
		}
		else
			table->dinner_nbr = -1;
		table->death = 0;
		table->full_philos = 0;
		return (1);
	}
	printf("Usage : number_of_philosophers time_to_die time_to_eat time_");
	return (str_err("to_sleep [number_of_times_each_philosopher_must_eat]."));
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_mtx) * table->philo_nbr);
	if (!table->forks)
		return (str_err("Forks malloc error."));
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			free(table->forks);
			return (str_err("Fork mutex initialisation failed."));
		}
		i++;
	}
	return (1);
}

int	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->death_mtx, NULL) != 0
		|| pthread_mutex_init(&table->write_mtx, NULL) != 0
		|| pthread_mutex_init(&table->full_mtx, NULL) != 0)
		return (str_err("Mutex initialisation failed."));
	return (1);
}

int	init_philos(t_table *table)
{
	int			i;
	long long	time;

	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (0);
	time = get_time();
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i;
		table->philos[i].last_meal = time;
		table->philos[i].meal_count = 0;
		table->philos[i].is_full = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
		table->philos[i].table = table;
		i++;
	}
	return (1);
}

int	init_structs(t_table *table, int ac, char **av)
{
	if (!check_args(table, ac, av))
		return (0);
	if (!init_forks(table))
		return (0);
	if (!init_mutex(table))
	{
		free(table->forks);
		return (0);
	}
	if (!init_philos(table))
	{
		free(table->forks);
		return (str_err("Philosophers initialisation failed."));
	}
	return (1);
}
