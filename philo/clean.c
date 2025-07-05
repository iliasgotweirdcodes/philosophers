/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:56:29 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/05 18:02:43 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->meal);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->deadlock);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

void	clean_mutexes(t_table *table, int i)
{
	pthread_mutex_destroy(&table->meal);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->deadlock);
	while (--i >= 0)
		pthread_mutex_destroy(&table->forks[i]);
}
