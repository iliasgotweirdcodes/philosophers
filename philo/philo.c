/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:38 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/29 17:27:51 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void f()
{
	system("leaks -q philo");
}

static int	handle_init_error(t_table *table, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_error(ERR_INPUT);
		free(table);
		return (0);
	}
	if (!parse_arguments(ac, av, table))
	{
		free(table);
		return (0);
	}
	init_table(table, ac, av);
	init_mutexes(table);
	return (1);
}

int	main(int ac, char **av)
{
	atexit(f);
	t_table		*table;
	pthread_t	monitor;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		ft_error(ERR_MALLOC);
		return (1);
	}
	if (!handle_init_error(table, ac, av))
		return (1);
	if (init_philos(table))
		ft_error(ERR_THREAD);
	if (pthread_create(&monitor, NULL, simulation_monitor, table) != 0)
		ft_error(ERR_THREAD);
	if (pthread_join(monitor, NULL) != 0)
		ft_error(ERR_JOIN);
	join_threads(table);
	free(table->philo);
	free(table->forks);
	ft_destroy_mutexes(table);
	free(table);
	return (0);
}
