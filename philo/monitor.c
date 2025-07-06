/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 06:27:44 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/06 18:19:13 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->table->deadlock);
	if (philo->table->dead == false)
	{
		pthread_mutex_unlock(&philo->table->deadlock);
		pthread_mutex_lock(&philo->table->deadlock);
		philo->table->dead = true;
		pthread_mutex_unlock(&philo->table->deadlock);
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %d died\n", get_time_ms() - philo->table->start_time, 1);
		pthread_mutex_unlock(&philo->table->print);
	}
	else
		pthread_mutex_unlock(&philo->table->deadlock);
}

int	check_all_ate(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->must_eat < 0)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal);
		if (table->philo[i].meals_eaten < table->must_eat)
		{
			all_ate = 0;
			pthread_mutex_unlock(&table->meal);
			break ;
		}
		pthread_mutex_unlock(&table->meal);
		i++;
	}
	return (all_ate);
}

int	check_philo_death(t_table *table, int i, long current_time)
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

int	check_starvation(t_table *table)
{
	int		i;
	long	current_time;
	long	last_meal;
	long	time_diff;

	current_time = get_time_ms();
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal);
		last_meal = table->philo[i].last_meal;
		pthread_mutex_unlock(&table->meal);
		time_diff = current_time - last_meal;
		if (time_diff > table->time_to_die)
			return (check_philo_death(table, i, current_time));
		i++;
	}
	return (0);
}

void	*simulation_monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (table->must_eat > 0 && check_all_ate(table))
		{
			pthread_mutex_lock(&table->deadlock);
			table->sim_done = true;
			pthread_mutex_unlock(&table->deadlock);
			break ;
		}
		if (check_starvation(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
