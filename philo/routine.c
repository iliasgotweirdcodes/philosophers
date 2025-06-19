/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:09 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/18 22:40:49 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

void	init_mutexes(t_table *table)
{
	long	i;

	i = 0;
	if (pthread_mutex_init(&table->meal, NULL))
		ft_error(ERR_MUTEX);
	if (pthread_mutex_init(&table->print, NULL))
		ft_error(ERR_MUTEX);
	if (pthread_mutex_init(&table->deadlock, NULL))
		ft_error(ERR_MUTEX);
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_error(ERR_MUTEX);
		i++;
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(philo->table->time_to_eat, philo);
	while (!is_dead(philo->table))
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->meal);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo->table->meal);
		ft_print_status(philo, "is eating");
		ft_usleep(philo->table->time_to_eat, philo);
		pthread_mutex_lock(&philo->table->meal);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->table->meal);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep, philo);
		ft_print_status(philo, "is thinking");
	}
	return (NULL);
}

long	ft_eating(t_table *table)
{
	long	i;
	long	n_meals;

	i = 0;
	n_meals = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal);
		if (table->philo[i].meals_eaten >= table->must_eat)
			n_meals++;
		pthread_mutex_unlock(&table->meal);
		i++;
	}
	return (n_meals == table->num_philos);
}

void	*simulation_monitor(void *arg)
{
	t_table	*table;
	long		i;
	long	last_meal;

	table = (t_table *)arg;
	while (1)
	{
		if (table->must_eat && ft_eating(table))
		{
			pthread_mutex_lock(&table->deadlock);
			table->dead = 1;
			pthread_mutex_unlock(&table->deadlock);
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
				ft_print_status(&table->philo[i], "died");
				pthread_mutex_lock(&table->deadlock);
				table->dead = 1;
				pthread_mutex_unlock(&table->deadlock);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

void	init_philo(t_table *table)
{
	long		i;
	t_philo	*philo;
	pthread_t	monitor;

	i = 0;
	// table->start_time = get_time_ms();
	while (i < table->num_philos)
	{
		philo = &table->philo[i];
		philo->id = i;
		philo->table = table;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->num_philos];
		pthread_mutex_lock(&table->meal);
		philo->meals_eaten = 0;
		philo->last_meal = 0;
		pthread_mutex_unlock(&table->meal);
		if (pthread_create(&philo->thread, NULL, philo_routine, philo))
			ft_error(ERR_THREAD);
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal);
		table->philo[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->meal);
		i++;
	}
	if (pthread_create(&monitor, NULL, simulation_monitor, table))
		ft_error(ERR_THREAD);
	if (pthread_join(monitor, NULL))
		ft_error(ERR_JOIN);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			ft_error(ERR_JOIN);
		i++;
	}
}

