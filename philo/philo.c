/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:38 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/30 21:47:50 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void f()
{
	system("leaks -q philo");
}

int	handle_init_error(t_table *table, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (free(table) ,ft_error(ERR_INPUT), 0);
	if (!parse_arguments(ac, av, table))
		return (free(table), 0);
	if (init_table(table, ac, av))
		return (0);
	if (init_mutexes(table))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	// atexit(f);
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (ft_error(ERR_MALLOC), 1);
	if (!handle_init_error(table, ac, av))
		return (ft_error(ERR_INIT), 1);
	if (init_philos(table))
		return (ft_error(ERR_INIT), 1);
	create_philo_threads(table);
	join_threads(table);
	free(table->philo);
	free(table->forks);
	ft_destroy_mutexes(table);
	free(table);
	return (0);
}
