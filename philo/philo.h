/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:19:22 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/06 15:30:54 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define PHILO_MAX 200
# define ERR_MUTEX "Error: Mutex creation failed!\n"
# define ERR_THREAD "Error: Thread creation failed!\n"
# define ERR_JOIN "Error: Thread join failed!\n"
# define ERR_TIME "Error: gettimeofday failed!\n"
# define ERR_MALLOC "Error: Malloc failed!\n"
# define ERR_ARGS "Error: Wrong number of args!\n"
# define ERR_INPUT "Error: Invalid input!\n"
# define ERR_INIT "Error: init failed!\n"

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
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
	bool			sim_done;
	long			start_time;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_t		monitor;
}	t_table;

void	ft_error(char *message);
int		init_table(t_table *table, int argc, char **argv);
int		init_philos(t_table *table);
int		init_mutexes(t_table *table);
void	destroy_mutexes(t_table *table);
int		ft_parse_int(char *str);
int		parse_arguments(int argc, char **argv, t_table *table);
int		create_philo_threads(t_table *table);
void	join_threads(t_table *table);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*philo_routine(void *arg);
void	*simulation_monitor(void *arg);
int		check_all_ate(t_table *table);
int		check_starvation(t_table *table);
int		is_dead(t_table *table);
long	get_time_ms(void);
void	ft_usleep(long sleep_time, t_philo *philo);
void	ft_print_status(t_philo *philo, char *status);
int		ft_strlen(char *str);
void	handle_one_philo(t_philo *philo);
int		simulation_should_stop(t_table *table);
void	clean_mutexes(t_table *table, int i);
int		init_table_mutexes(t_table *table);

#endif
