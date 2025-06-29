/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:57:17 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/28 19:16:42 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_last_meal(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal);
		table->philo[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->meal);
		i++;
	}
}

int	ft_all_ate(t_table *table)
{
	int	i;
	int	all_ate;

	all_ate = 1;
	pthread_mutex_lock(&table->meal);
	i = 0;
	while (i < table->num_philos)
	{
		if (table->philo[i].meals_eaten < table->must_eat)
		{
			all_ate = 0;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal);
	return (all_ate);
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
}

