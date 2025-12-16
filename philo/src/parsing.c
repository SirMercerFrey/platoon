/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:26:24 by mcharret          #+#    #+#             */
/*   Updated: 2025/11/29 18:26:28 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo philo_nbr to_die to_eat to_sleep [meals]\n");
		return (0);
	}
	if (!check_atoi(argv[1]) || !check_atol(argv[2])
		|| !check_atol(argv[3]) || !check_atol(argv[4]))
	{
		printf("Arguments must be valid numbers\n");
		return (0);
	}
	if (argc == 6 && !check_atoi(argv[5]))
	{
		printf("Arguments must be valid numbers\n");
		return (0);
	}
	return (1);
}

int	check_atoi(char *str)
{
	long	result;

	while (*str && is_space(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (0);
		++str;
	}
	if (!*str)
		return (0);
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		if (result > INT_MAX)
			return (0);
		++str;
	}
	if (*str != '\0')
		return (0);
	return (1);
}

int	check_atol(char *str)
{
	long	result;

	while (*str && is_space(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (0);
		++str;
	}
	if (!*str)
		return (0);
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (result > ((LONG_MAX - *str + '0') / 10))
			return (0);
		result = result * 10 + *str - '0';
		++str;
	}
	if (*str != '\0')
		return (0);
	return (1);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
