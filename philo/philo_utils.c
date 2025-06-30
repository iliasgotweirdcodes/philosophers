/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:57:17 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/30 21:43:32 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_all(t_table *table, int i)
{
	pthread_mutex_lock(&table->deadlock);
	table->dead = true;
	pthread_mutex_unlock(&table->deadlock);
	while (--i < table->num_philos)
		if (pthread_join(table->philo[i].thread, NULL))
			ft_error(ERR_JOIN);
}
int	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]) != 0)
		{
			join_all(table, i);
			ft_error(ERR_THREAD);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, simulation_monitor, table) != 0)
	{
		if (pthread_join(table->monitor, NULL) != 0)
			ft_error(ERR_JOIN);
		ft_error(ERR_THREAD);
	}
	return (1);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			ft_error(ERR_JOIN);
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		ft_error(ERR_JOIN);
}

