/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overflow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:35:21 by karpatel          #+#    #+#             */
/*   Updated: 2024/08/25 15:35:24 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
