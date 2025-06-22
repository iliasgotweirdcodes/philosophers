/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:19:22 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/06/20 00:01:15 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

# define PHILO_MAX 200
# define ERR_MUTEX "Error: Mutex creation failed!\n"
# define ERR_THREAD "Error: Thread creation failed!\n"
# define ERR_JOIN "Error: Thread join failed!\n"
# define ERR_TIME "Error: gettimeofday failed!\n"
# define ERR_MALLOC "Error: Malloc failed!\n"
# define ERR_ARGS "Error: Wrong number of args!\n"
# define ERR_INPUT "Error: Invalid input!\n"

typedef struct s_philo {
	int	id;
	pthread_t	thread;
	int	last_meal;
	int meals_eaten;
	int	left;
	int	right;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	bool			dead;
	long			start_time;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_table;

int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		parse_arguments(int ac, char **av, t_table *table);
long	get_time_ms(void);
void	ft_error(char *message);
void	ft_usleep(int ms, t_philo *philo);
void	ft_print_status(t_philo *philo, char *status);
void	init_philo(t_table *table);
void	init_mutexes(t_table *table);
void	init_table(t_table *table);
void	ft_destroy_mutexes(t_table *table);
int		is_dead(t_table *table);
void	*philo_routine(void *arg);
void	*simulation_monitor(void *arg);
void	init_philo(t_table *table);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	init_philos_struct(t_table *table);
void	ft_last_meal(t_table *table);
int		ft_all_ate(t_table *table);

#endif
