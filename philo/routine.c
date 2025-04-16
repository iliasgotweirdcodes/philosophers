/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:09 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/16 17:31:01 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_table *table)
{
	int	i = 0;
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

void	*philo_routine(t_philo *p)
{
	long	now;

	if (p->id % 2)
		ft_usleep(p->table->time_to_eat, p);
	while (!is_dead(p->table))
	{
		now = get_time_ms();
		if (now > p->last_meal + p->table->time_to_die)
			break ;
		pthread_mutex_lock(&p->left_fork[p->id]);
		ft_print_status(p, "has taken a left fork");
		pthread_mutex_lock(&p->right_fork[p->id]);
		ft_print_status(p, "has taken a right fork");
		pthread_mutex_lock(&p->table->meal);
		p->last_meal = get_time_ms();
		p->number_of_meals++;
		pthread_mutex_unlock(&p->table->meal);
		ft_print_status(p, "is eating");
		ft_usleep(p->table->time_to_eat, p);
		pthread_mutex_unlock(&p->left_fork[p->id]);
		pthread_mutex_unlock(&p->right_fork[p->id]);
		ft_print_status(p, "is sleeping");
		ft_usleep(p->table->time_to_sleep, p);
		ft_print_status(p, "is thinking");
	}
	return (NULL);
}


int	ft_eating(t_table *table)
{
	int	i = 0;
	int	n_meals = 0;

	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal);
		if (table->philo[i].number_of_meals >= table->must_eat)
			n_meals++;
		pthread_mutex_unlock(&table->meal);
		i++;
	}
	return (n_meals == table->num_philos);
}

void	*simulation_monitor(t_table *table)
{
	int		i;
	long	last_meal;

	while (1)
	{
		if (table->must_eat && ft_eating(table))
		{
			pthread_mutex_lock(&table->deadlock);
			table->dead = true;
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
				table->dead = true;
				pthread_mutex_unlock(&table->deadlock);
				ft_usleep(100, table->philo);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	init_philo(t_table *table)
{
	int			i;
	t_philo		*philo;
	pthread_t	monitor;

	i = 0;
	table->simulation = get_time_ms();
	while (i < table->num_philos)
	{
		philo = &table->philo[i];
		philo->id = i;
		philo->table = table;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->num_philos];
		pthread_mutex_lock(&table->meal);
		philo->number_of_meals = 0;
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&table->meal);
		if (pthread_create(&philo->thread, NULL, (void *)philo_routine, philo))
			ft_error(ERR_THREAD);
		i++;
	}
	if (pthread_create(&monitor, NULL, (void *)simulation_monitor, table))
		ft_error(ERR_THREAD);
	if (pthread_join(monitor, NULL))
		ft_error(ERR_JOIN);
	i = 0;
	while (i < table->num_philos)
		if (pthread_join(table->philo[i++].thread, NULL))
			ft_error(ERR_JOIN);
}
