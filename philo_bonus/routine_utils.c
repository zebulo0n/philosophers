/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:18:21 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/24 19:21:27 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_philo *philo, char *str)
{
	long long	timestamp;

	sem_wait(philo->table->write_sem);
	timestamp = get_time() - philo->table->start_time;
	printf("%lld\t%d %s\n", timestamp, philo->id + 1, str);
	sem_post(philo->table->write_sem);
}

void	print_death(t_philo *philo)
{
	long long	timestamp;

	sem_wait(philo->table->write_sem);
	timestamp = get_time() - philo->table->start_time;
	printf("%lld\t%d died\n", timestamp, philo->id + 1);
	sem_post(philo->table->write_sem);
}

int	philo_died(t_philo *philo)
{
	long long	timestamp;

	sem_wait(philo->table->death_sem);
	timestamp = get_time();
	if ((timestamp - philo->last_meal) > philo->table->time_to_die)
	{
		print_death(philo);
		return (1);
	}
	sem_post(philo->table->death_sem);
	return (0);
}

int	philo_full(t_philo *philo)
{
	if (philo->table->dinner_nbr != -1
		&& philo->meal_count == philo->table->dinner_nbr)
		return (1);
	return (0);
}

void	clean_exit(t_philo *philo, int code)
{
	if (philo && philo->table && philo->table->philos)
		free(philo->table->philos);
	exit(code);
}
