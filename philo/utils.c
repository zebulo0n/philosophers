/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:06:04 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/22 16:16:19 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}

long	ft_atol(const char *nptr)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb *= 10;
		nb = nb + (*nptr - 48);
		nptr++;
	}
	return (nb * sign);
}

void	free_all(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (table->forks)
	{
		while (i < table->philo_nbr)
			pthread_mutex_destroy(&table->forks[i++]);
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->write_mtx);
	pthread_mutex_destroy(&table->death_mtx);
	pthread_mutex_destroy(&table->full_mtx);
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
