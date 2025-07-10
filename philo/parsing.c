/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:23:16 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/07/09 17:26:43 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *message)
{
	write(2, message, ft_strlen(message));
}

int	ft_parse_int(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (!str || !str[i])
		return (-1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (-1);
	return ((int)res);
}

int	parse_arguments(int ac, char **av, t_table *table)
{
	int	i;
	int	val;

	i = 1;
	while (i < ac)
	{
		val = ft_parse_int(av[i]);
		if (val <= 0)
		{
			write(2, ERR_INPUT, 23);
			return (0);
		}
		i++;
	}
	table->num_philos = ft_parse_int(av[1]);
	if (table->num_philos > PHILO_MAX)
		return (ft_error(ERR_INPUT), 0);
	table->time_to_die = ft_parse_int(av[2]);
	table->time_to_eat = ft_parse_int(av[3]);
	table->time_to_sleep = ft_parse_int(av[4]);
	if (ac == 6)
		table->must_eat = ft_parse_int(av[5]);
	else
		table->must_eat = 0;
	return (1);
}
