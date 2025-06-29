/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:49 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/28 17:30:45 by ilel-hla         ###   ########.fr       */
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
    int result;
    int i;

    result = 0;
    i = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0')
        return (-1);
    return (result);
}

bool	is_dead(t_table *table)
{
	bool	is_dead;

	pthread_mutex_lock(&table->deadlock);
	is_dead = table->dead;
	pthread_mutex_unlock(&table->deadlock);
	return (is_dead);
}

