/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:16 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/04/16 17:17:47 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *message)
{
	write(2, message, ft_strlen(message));
}

int	ft_check(char *str)
{
	int i = 0;

	if (!str || !str[i])
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	parse_arguments(int ac, char **av, t_table *table)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!ft_check(av[i]) || ft_atoi(av[i]) <= 0)
		{
			write(2, ERR_INPUT, 23);
			return (0);
		}
		i++;
	}
	table->num_philos = ft_atoi(av[1]);
	if (table->num_philos > PHILO_MAX)
		return (write(2, ERR_INPUT, 23), 0);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	else
		table->must_eat = 0;
	return (1);
}
