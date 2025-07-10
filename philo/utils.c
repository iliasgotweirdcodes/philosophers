/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:49 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/10 17:39:12 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


int	simulation_should_stop(t_table *table)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&table->deadlock);
	if (table->dead || table->sim_done)
		stop = 1;
	pthread_mutex_unlock(&table->deadlock);
	return (stop);
}

void	ft_print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->deadlock);
	if (!philo->table->dead && !philo->table->sim_done)
	{
		timestamp = get_time_ms() - philo->table->start_time;
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %d %s\n", timestamp, philo->id, status);
		pthread_mutex_unlock(&philo->table->print);
	}
	pthread_mutex_unlock(&philo->table->deadlock);
}
