/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:44 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/16 16:40:42 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) == -1)
		ft_error(ERR_TIME);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
	{
		if (philo->table->dead == true)
			return ;
		usleep(100);
	}
}

void	ft_print_status(t_philo *philo, char *status)
{
	long	time;

	time = get_time_ms() - philo->table->simulation;
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->print);
		return ;
	}
	printf("%ld %d %s\n", time, philo->id + 1, status);
	pthread_mutex_unlock(&philo->table->print);
}


