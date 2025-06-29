/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:21:53 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/29 17:16:33 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_table(t_table *table, int argc, char **argv)
{
    (void)argc;
    (void)argv;

    table->dead = false;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
    table->philo = malloc(sizeof(t_philo) * table->num_philos);
    if (!table->forks || !table->philo)
        return (1);
    return (0);
}

int init_philos(t_table *table)
{
    int i;

    // Set start time ONCE before creating threads
    table->start_time = get_time_ms();

    i = 0;
    while (i < table->num_philos)
    {
        table->philo[i].id = i + 1;
        // Set all last_meal times to the same start time
        table->philo[i].last_meal = table->start_time;
        table->philo[i].meals_eaten = 0;
        table->philo[i].left = i;
        table->philo[i].right = (i + 1) % table->num_philos;
        table->philo[i].left_fork = &table->forks[i];
        table->philo[i].right_fork = &table->forks[(i + 1) % table->num_philos];
        table->philo[i].table = table;

        if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}

void    init_mutexes(t_table *table)
{
    int i;

    pthread_mutex_init(&table->meal, NULL);
    pthread_mutex_init(&table->print, NULL);
    pthread_mutex_init(&table->deadlock, NULL);
    i = 0;
    while (i < table->num_philos)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
}

void ft_destroy_mutexes(t_table *table)
{
    int i;

    pthread_mutex_destroy(&table->meal);
    pthread_mutex_destroy(&table->print);
    pthread_mutex_destroy(&table->deadlock);
    i = 0;
    while (i < table->num_philos)
    {
        pthread_mutex_destroy(&table->forks[i]);
        pthread_mutex_destroy(&table->philo[i].meal_mutex);
        i++;
    }
}
