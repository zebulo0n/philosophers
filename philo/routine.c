/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:06:01 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/22 14:56:22 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	solo_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		if (pthread_mutex_lock(philo->right_fork) == 0)
			print_action(philo, "has taken a fork");
		else
			pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		if (pthread_mutex_lock(philo->left_fork) == 0)
			print_action(philo, "has taken a fork");
		else
			pthread_mutex_unlock(philo->right_fork);
	}
}

void	eat(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->table->death_mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->death_mtx);
	philo->meal_count++;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	meal_count_check(t_philo *philo)
{
	if (!philo->is_full && philo->table->dinner_nbr != -1
		&& philo->meal_count == philo->table->dinner_nbr)
	{
		pthread_mutex_lock(&philo->table->full_mtx);
		philo->table->full_philos++;
		pthread_mutex_unlock(&philo->table->full_mtx);
		philo->is_full = 1;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->philo_nbr == 1 && solo_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->table->death_mtx);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->table->death_mtx);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_mtx);
		if (philo->table->death)
			return (pthread_mutex_unlock(&philo->table->death_mtx), NULL);
		pthread_mutex_unlock(&philo->table->death_mtx);
		take_forks(philo);
		eat(philo);
		meal_count_check(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
}
