/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:18:25 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/24 19:21:20 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	solo_philo(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	print_action(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die);
	sem_post(philo->table->forks_sem);
	return (1);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	print_action(philo, "has taken a fork");
	sem_wait(philo->table->forks_sem);
	print_action(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	sem_wait(philo->table->dine_sem);
	print_action(philo, "is eating");
	sem_wait(philo->table->death_sem);
	philo->last_meal = get_time();
	sem_post(philo->table->death_sem);
	philo->meal_count++;
	ft_usleep(philo->table->time_to_eat);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->dine_sem);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_detach(philo->monitor);
	while (1)
	{
		if (philo_died(philo))
			clean_exit(philo, 66);
		usleep(1000);
	}
}

void	routine(t_philo *philo)
{
	sem_wait(philo->table->death_sem);
	philo->last_meal = get_time();
	sem_post(philo->table->death_sem);
	if (philo->table->philo_nbr == 1 && solo_philo(philo))
		clean_exit(philo, 0);
	if (pthread_create(&philo->monitor, NULL, monitor, philo) != 0)
		return ;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		if (philo_full(philo))
			clean_exit(philo, 77);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_action(philo, "is thinking");
		if (philo->id % 2 == 0)
			usleep(1000);
	}
}
