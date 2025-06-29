/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:44 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/29 17:09:55 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long milliseconds, t_philo *philo)
{
    long start_time;

    start_time = get_time_ms();
    while ((get_time_ms() - start_time) < milliseconds)
    {
        if (is_dead(philo->table))  // Access table through philo->table
            break;
        usleep(500);
    }
}

void ft_print_status(t_philo *philo, char *status)
{
    long timestamp;

    if (is_dead(philo->table))
        return;
    timestamp = get_time_ms() - philo->table->start_time;
    pthread_mutex_lock(&philo->table->print);
    if (!is_dead(philo->table))  // Check again to avoid printing after death
        printf("%ld %d %s\n", timestamp, philo->id, status);
    pthread_mutex_unlock(&philo->table->print);
}
