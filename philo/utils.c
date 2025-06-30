/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:49 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/30 18:09:39 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
int	ft_atoi(char *str)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

int	is_dead(t_table *table)
{
	int	is_dead;

	pthread_mutex_lock(&table->deadlock);
	is_dead = table->dead;
	pthread_mutex_unlock(&table->deadlock);
	return (is_dead);
}
void	ft_print_status(t_philo *philo, char *status)
{
	long	timestamp;

	if (is_dead(philo->table))
		return;
	timestamp = get_time_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print);
	if (!is_dead(philo->table))
		printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->table->print);
}


