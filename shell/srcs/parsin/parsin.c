/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:52:21 by aariss            #+#    #+#             */
/*   Updated: 2019/08/10 13:07:49 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"
#include <stdio.h>

char	*quote_treatement(char *line, char *str, int *i, t_quote spec)
{
	spec.keeper = line[*i];
	str = ft_joinchar(str, line[*i]);
	(*i)++;
	while (line[*i] != spec.keeper && line[*i])
	{
		if (line[*i] == 92)
		{
			spec.definer = 1;
			str = escape_character(str, line, &(*i), spec);
		}
		else if (line[*i] == '$' && ft_strlen(line + (*i) + 1) > 2)
			str = dollar_handle_quoted(str, line, &(*i), spec);
		else
			str = ft_joinchar(str, line[*i]);
		(*i)++;
	}
	str = ft_joinchar(str, line[*i]);
	return (str);
}

char	*nasty(char *line, char *str, int *i, int def)
{
	char		*tmp;

	if (def)
	{
		str = token_manager(str, line, &(*i));
		while (ft_istoken(line[*i]) && line[*i])
			(*i)++;
		(*i)--;
	}
	else if (!def)
	{
		tmp = str;
		str = ignore_quote(str);
		ft_strdel(&tmp);
	}
	return (str);
}

char	*parse_within(char *line, char *str, int *i, t_quote spec)
{
	if (ft_isquote(line[*i]))
		str = quote_treatement(line, str, &(*i), spec);
	else if (((ft_isdigit(line[*i])
					&& got_token_after_digit(line + (*i)))
				|| ft_istoken(line[*i])) && line[*i])
		str = nasty(line, str, &(*i), 1);
	else if (line[*i] == ';')
		str = ft_joinchar(str, -3);
	else if (line[*i] == '|')
		str = ft_joinchar(str, -4);
	else if (line[*i] == '$' && ft_strlen(line + (*i) + 1) > 1)
		str = dollar_handle_simple(str, line, &(*i), spec.env);
	else
		str = ft_joinchar(str, line[*i]);
	return (str);
}

char	*terminator(char *line, char **str)
{
	*str = ft_strdup("");
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

char	*parsin(char *line, t_env *env)
{
	int			i;
	t_quote		spec;
	int			t;
	char		*str;

	t = 0;
	i = 0;
	spec.env = env;
	line = terminator(line, &str);
	if (!line)
		return (NULL);
	while (line[i] && i < (int)ft_strlen(line))
	{
		if (line[i] == 92)
		{
			spec.keeper = 0;
			spec.definer = 0;
			str = escape_character(str, line, &i, spec);
		}
		else
			str = parse_within(line, str, &i, spec);
		i++;
	}
	str = nasty(line, str, &i, 0);
	return (str);
}
