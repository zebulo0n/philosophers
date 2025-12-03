/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:05:54 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/22 15:24:59 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	str_err(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->table->death_mtx);
	if (!philo->table->death)
	{
		pthread_mutex_lock(&philo->table->write_mtx);
		timestamp = get_time() - philo->table->start_time;
		printf("%lld\t%d %s\n", timestamp, philo->id + 1, action);
		pthread_mutex_unlock(&philo->table->write_mtx);
	}
	pthread_mutex_unlock(&philo->table->death_mtx);
}

void	print_death(t_philo *philo)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->table->write_mtx);
	timestamp = get_time() - philo->table->start_time;
	printf("%lld\t%d died\n", timestamp, philo->id + 1);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
