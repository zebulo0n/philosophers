/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:17:13 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/24 19:21:10 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		table->full_philos = 0;
		return (1);
	}
	printf("Usage : number_of_philosophers time_to_die time_to_eat time_");
	return (str_err("to_sleep [number_of_times_each_philosopher_must_eat]."));
}

unsigned int	max_dine(int philo_nbr)
{
	if (philo_nbr == 1)
		return (1);
	else
		return (philo_nbr / 2);
}

int	init_semaphores(t_table *table)
{
	sem_unlink("/forks_sem");
	sem_unlink("/dine_sem");
	sem_unlink("/write_sem");
	sem_unlink("/death_sem");
	table->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, table->philo_nbr);
	table->dine_sem = sem_open("/dine_sem", O_CREAT, 0644,
			max_dine(table->philo_nbr));
	table->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	table->death_sem = sem_open("/death_sem", O_CREAT, 0644, 1);
	if (table->dine_sem == SEM_FAILED || table->forks_sem == SEM_FAILED
		|| table->write_sem == SEM_FAILED || table->death_sem == SEM_FAILED)
		return (str_err("Semaphores initialization failed."));
	return (1);
}

int	init_philos(t_table *table)
{
	int			i;
	long long	time;

	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (str_err("Philosophers malloc failed."));
	time = get_time();
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i;
		table->philos[i].last_meal = time;
		table->philos[i].meal_count = 0;
		table->philos[i].pid = 0;
		table->philos[i].table = table;
		i++;
	}
	return (1);
}

int	init_structs(t_table *table, int ac, char **av)
{
	if (!check_args(table, ac, av))
		return (0);
	if (!init_semaphores(table))
		return (0);
	if (!init_philos(table))
		return (0);
	return (1);
}
