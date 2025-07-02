/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:21:53 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/02 21:28:01 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, int ac, char **av)
{
	(void)ac;
	(void)av;
	table->dead = false;
	table->sim_done = false;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (free(table), 1);
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philo)
		return (free(table->forks), free(table), 1);
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->num_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].last_meal = table->start_time;
		table->philo[i].meals_eaten = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->num_philos];
		table->philo[i].table = table;
		i++;
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->meal, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->deadlock, NULL) != 0)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->meal);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->deadlock);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
