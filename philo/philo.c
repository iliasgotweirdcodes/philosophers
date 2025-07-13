/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:38 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/13 12:19:43 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_parse(t_table *table, int ac, char **av)
{
	if (!parse_arguments(ac, av, table))
		return (1);
	if (init_table(table))
		return (1);
	if (init_mutexes(table))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac != 5 && ac != 6)
		return (ft_error(ERR_ARGS), 1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (ft_error(ERR_MALLOC), 1);
	if (init_parse(table, ac, av))
		return (free(table->philo), free(table->forks), free(table), 1);
	if (init_philos(table))
		return (free(table->philo), free(table->forks), free(table), 1);
	create_philo_threads(table);
	join_threads(table);
	destroy_mutexes(table);
	return (free(table->philo), free(table->forks), free(table), 0);
}
