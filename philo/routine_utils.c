/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:39 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/29 17:22:27 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ate(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->must_eat < 0)
		return (0);
	all_ate = 1;
	pthread_mutex_lock(&table->meal);
	i = 0;
	while (i < table->num_philos)
	{
		if (table->philo[i].meals_eaten < table->must_eat)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal);
	return (all_ate);
}

int	check_philosopher_death(t_table *table, int i, long current_time, long last_meal)
{
	long	time_diff;

	time_diff = current_time - last_meal;
	if (time_diff > table->time_to_die)
	{
		pthread_mutex_lock(&table->deadlock);
		if (!table->dead)
		{
			table->dead = true;
			pthread_mutex_unlock(&table->deadlock);
			pthread_mutex_lock(&table->print);
			printf("%ld %d died\n", current_time - table->start_time, i + 1);
			pthread_mutex_unlock(&table->print);

			return (1);
		}
		else
			pthread_mutex_unlock(&table->deadlock);
		return (1);
	}
	return (0);
}

int	check_starvation(t_table *table)
{
	int		i;
	long	current_time;
	long	last_meal;

	current_time = get_time_ms();
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal);
		last_meal = table->philo[i].last_meal;
		pthread_mutex_unlock(&table->meal);
		if (last_meal > 0 && last_meal <= current_time)
		{
			if (check_philosopher_death(table, i, current_time, last_meal))
				return (1);
		}
		i++;
	}
	return (0);
}

void	*simulation_monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	ft_usleep(10, table->philo);
	while (1)
	{
		if (check_starvation(table))
			break ;
		if (table->must_eat > 0 && check_all_ate(table))
		{
			pthread_mutex_lock(&table->deadlock);
			table->dead = true;
			pthread_mutex_unlock(&table->deadlock);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

