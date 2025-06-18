/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:44 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/18 22:22:49 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_ms(void)
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) == -1)
		ft_error(ERR_TIME);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long	start;

	start = get_time_ms();
	while (!is_dead(philo->table) && get_time_ms() - start < ms)
		usleep(100);
}

void	ft_print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print); // use 'print' not 'prlong'
	timestamp = get_time_ms() - philo->table->start_time;
	if (!is_dead(philo->table))
		printf("%ld %d %s\n", timestamp, philo->id + 1, status);
	pthread_mutex_unlock(&philo->table->print);
}


