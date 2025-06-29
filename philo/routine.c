/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:09 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/29 17:31:20 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_table	*table;
	long	current_time;

	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(philo, "has taken a fork");
	current_time = get_time_ms();
	ft_usleep(table->time_to_eat, philo);
	pthread_mutex_lock(&table->meal);
	philo->last_meal = current_time;
	pthread_mutex_unlock(&table->meal);
	ft_print_status(philo, "is eating");
	pthread_mutex_lock(&table->meal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	long	think_time;

	ft_print_status(philo, "is thinking");
	if (philo->table->num_philos % 2 == 1)
	{
		think_time = (philo->table->time_to_eat * 2) - philo->table->time_to_sleep;
		if (think_time > 0)
			ft_usleep(think_time, philo);
	}
}

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die, philo);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
	{
		ft_usleep(400, philo);
		pthread_mutex_lock(&philo->table->meal);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo->table->meal);
	}
	while (!is_dead(philo->table))
	{
		if (philo->table->num_philos == 1)
		{
			handle_single_philo(philo);
			break ;
		}
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
