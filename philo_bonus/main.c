/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:17:19 by zoeschne          #+#    #+#             */
/*   Updated: 2025/09/24 19:17:23 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char *av[])
{
	t_table	table;

	if (!init_structs(&table, ac, av))
		return (0);
	table.start_time = get_time();
	if (!init_processes(&table))
		return (0);
	if (!wait_processes(&table))
		return (0);
	kill_all(&table);
}
