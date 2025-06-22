/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:49 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/22 18:33:59 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - 48);
	if (res > 2147483647 && sign == 1)
		return (-1);
	return (res * sign);
}

int	is_dead(t_table *table)
{
	int dead;

	pthread_mutex_lock(&table->deadlock);
	dead = table->dead;
	pthread_mutex_unlock(&table->deadlock);
	return (dead);
}

void	init_table(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->philo || !table->forks)
		ft_error(ERR_MALLOC);
}

void	init_mutexes(t_table *table)
{
	int	i;

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
