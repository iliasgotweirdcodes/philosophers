/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:44 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/01 02:06:27 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long milliseconds, t_philo *philo)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < milliseconds)
	{
		if (is_dead(philo->table))
			break ;
		usleep(500);
	}
}
