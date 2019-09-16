/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_extras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:01:22 by aariss            #+#    #+#             */
/*   Updated: 2019/08/10 11:59:12 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		retrieve_the_digit(char *name, int delimiter)
{
	if (delimiter == 0)
		return (ft_atoi(name));
	while (ft_isdigit(*name))
		name++;
	while (ft_istoken(*name))
		name++;
	return (ft_atoi(name));
}

int		count_arg(char **kratos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (kratos[i])
	{
		if (!ultimate_check(kratos[i]))
			count++;
		i++;
	}
	return (count + 1);
}
