/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:57:17 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/13 19:45:34 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_all(t_table *table, int i)
{
	pthread_mutex_lock(&table->deadlock);
	table->dead = true;
	pthread_mutex_unlock(&table->deadlock);
	while (--i >= 0)
		pthread_join(table->philo[i].thread, NULL);
}

int	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philo[i].thread,
				NULL, philo_routine, &table->philo[i]) != 0)
		{
			join_all(table, i);
			ft_error(ERR_THREAD);
			return (0);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, simulation_monitor, table) != 0)
	{
		join_all(table, i);
		ft_error(ERR_THREAD);
		return (0);
	}
	return (1);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
