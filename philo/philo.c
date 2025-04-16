/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:38 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/16 17:26:23 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->philo || !table->forks)
		ft_error(ERR_MALLOC);
}
void f()
{
	system("leaks -q philo");
}
int main(int ac, char **av)
{
	// atexit(f);
	t_table	table;

	if (ac != 5 && ac != 6)
	{
		ft_error(ERR_ARGS);
		return (1);
	}
	if (!parse_arguments(ac, av, &table))
		return (1);
	init_table(&table);
	init_philo(&table);
	init_mutexes(&table);
	simulation_monitor(&table);
	free(table.philo);
	free(table.forks);
	ft_destroy_mutexes(&table);
	return (0);
}
