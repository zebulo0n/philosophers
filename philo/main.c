/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:05:39 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/22 11:06:32 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	table;

	if (!init_structs(&table, ac, av))
		return (0);
	table.start_time = get_time();
	if (!init_threads(&table))
		return (0);
	monitor(&table);
	if (!join_threads(&table))
		return (0);
	free_all(&table);
}
