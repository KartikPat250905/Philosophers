/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputhelper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:28:22 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/12 15:28:24 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	overflow(char *str)
{
	long long	num;

	if (ft_strlen(str) > 11)
		return (1);
	num = ft_atoi(str);
	if ((num > INT_MAX || num < INT_MIN)
		|| (num == 0 && *str != '0') || (num == 1 && *str != '1'))
		return (1);
	return (0);
}

int	ft_isnumstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9')
				|| (str[i] == '.' || str[i] == '+' || str[i] == '-')))
			return (1);
		i++;
	}
	return (0);
}

int	resultcounter(long *result, int sign, char const *str, int i)
{
	while (ft_isdigit(str[i]))
	{
		if (*result > ((INT_MAX - (str[i] - '0')) / 10) && sign == 1)
			return (-1);
		if (sign == -1 && *result > ((-INT_MIN) / 10))
			return (0);
		*result *= 10;
		*result += str[i] - '0';
		i++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	int		checker;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	checker = resultcounter(&result, sign, str, i);
	if (checker == -1)
		return (-1);
	if (checker == 0)
		return (0);
	return (result * sign);
}
