/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:39 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/21 16:46:25 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos_struct(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philo[i];
		philo->id = i;
		philo->table = table;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->num_philos];
		philo->meals_eaten = 0;
		i++;
	}
}

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

void	set_dead(t_table *table)
{
	pthread_mutex_lock(&table->deadlock);
	table->dead = 1;
	pthread_mutex_unlock(&table->deadlock);
}

void	*simulation_monitor(void *arg)
{
	t_table	*table;
	int		i;
	int		last_meal;

	table = (t_table *)arg;
	while (!is_dead(table))
	{
		if (table->must_eat && ft_all_ate(table))
		{
			set_dead(table);
			return (NULL);
		}
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_lock(&table->meal);
			last_meal = table->philo[i].last_meal;
			pthread_mutex_unlock(&table->meal);
			if (get_time_ms() > last_meal + table->time_to_die)
			{
				set_dead(table);
				ft_print_status(&table->philo[i], "died");
				return (NULL);
			}
			i++;
		}
		ft_usleep(400, table->philo);
	}
	return (NULL);
}
