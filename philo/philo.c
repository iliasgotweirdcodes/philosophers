/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:38 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/02 21:26:10 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_parse(t_table *table, int ac, char **av)
{
	if (!parse_arguments(ac, av, table))
		return (free(table), 1);
	if (init_table(table, ac, av))
		return (1);
	if (init_mutexes(table))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac != 5 && ac != 6)
		return (ft_error(ERR_INPUT), 1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (ft_error(ERR_MALLOC), 1);
	if (init_parse(table, ac, av))
		return (1);
	if (init_philos(table))
		return (ft_error(ERR_INIT), 1);
	create_philo_threads(table);
	join_threads(table);
	free(table->philo);
	free(table->forks);
	destroy_mutexes(table);
	free(table);
	return (0);
}
