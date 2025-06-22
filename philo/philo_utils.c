/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:57:17 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/20 00:24:03 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_all_ate(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->meal);
	i = 0;
	while (i < table->num_philos)
	{
		if (table->philo[i].meals_eaten < table->must_eat)
		{
			return (0);
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal);
	return (1);
}

void	create_philo_threads(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philo[i];
		if (pthread_create(&philo->thread, NULL, philo_routine, philo))
			ft_error(ERR_THREAD);
		i++;
	}
}

void	join_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			ft_error(ERR_JOIN);
		i++;
	}
}

void	init_philo(t_table *table)
{
	pthread_t	monitor;

	init_philos_struct(table);
	ft_last_meal(table);
	create_philo_threads(table);
	if (pthread_create(&monitor, NULL, simulation_monitor, table))
		ft_error(ERR_THREAD);
	if (pthread_join(monitor, NULL))
		ft_error(ERR_JOIN);
	join_philo_threads(table);
}

