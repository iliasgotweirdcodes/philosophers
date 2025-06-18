/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:38 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/18 22:17:47 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->philo || !table->forks)
		ft_error(ERR_MALLOC);
    table->start_time = get_time_ms();
    printf("---> %ld\n", table->start_time);
    exit(1);
}
void f()
{
	system("leaks -q philo");
}
int main(int ac, char **av)
{
    // atexit(f);
    t_table *table = malloc(sizeof(t_table));
    if (!table)
        ft_error(ERR_MALLOC);
    if (ac != 5 && ac != 6)
    {
        ft_error(ERR_ARGS);
        free(table);
        return (1);
    }
    if (!parse_arguments(ac, av, table))
    {
        free(table);
        return (1);
    }
    init_table(table);
    init_philo(table);
    init_mutexes(table);
    simulation_monitor(table);
    free(table->philo);
    free(table->forks);
    ft_destroy_mutexes(table);
    free(table);
    return (0);
}
