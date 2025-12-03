/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:18:16 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/24 19:24:05 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (str_err("Process initialization failed."));
		else if (table->philos[i].pid == 0)
		{
			routine(&table->philos[i]);
			exit(0);
		}
		i++;
	}
	return (1);
}

int	wait_processes(t_table *table)
{
	int	finished_processes;
	int	full_philos;
	int	status;

	finished_processes = 0;
	full_philos = 0;
	while (finished_processes < table->philo_nbr)
	{
		waitpid(-1, &status, 0);
		finished_processes++;
		if (WEXITSTATUS(status) == 66)
			return (1);
		else if (WEXITSTATUS(status) == 77)
			full_philos++;
		if (full_philos == table->philo_nbr)
			return (1);
	}
	return (1);
}

void	kill_all(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->philo_nbr)
	{
		if (table->philos[i].pid > 0)
			kill(table->philos[i].pid, SIGTERM);
		i++;
	}
	sem_close(table->forks_sem);
	sem_close(table->write_sem);
	sem_close(table->dine_sem);
	sem_close(table->death_sem);
	sem_unlink("/forks_sem");
	sem_unlink("/dine_sem");
	sem_unlink("/write_sem");
	sem_unlink("/death_sem");
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
