/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:42:23 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 19:54:07 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

char	*dollar_get_simple(char *name, t_env *env, char **ptr)
{
	char	*str;

	while (env)
	{
		str = ft_strfchr(env->var, '=');
		if (ft_strncmp(name, env->var, (ft_strlen(env->var) - 1)) == 0)
		{
			*ptr = ft_strdup(str);
			ft_strdel(&str);
			return (env->value);
		}
		ft_strdel(&str);
		env = env->next;
	}
	return (NULL);
}

char	*dollar_get_quoted(char *name, t_env *env, char **ptr)
{
	char	*str;

	while (env)
	{
		str = ft_strfchr(env->var, '=');
		if (ft_strncmp(name, str, ft_strlen(str)) == 0)
		{
			*ptr = ft_strdup(str);
			ft_strdel(&str);
			return (env->value);
		}
		ft_strdel(&str);
		env = env->next;
	}
	return (NULL);
}

char	*dollar_handle_simple(char *toto, char *line, int *i, t_env *env)
{
	char	*str;
	char	*ptr;
	char	*tmp;

	ptr = NULL;
	str = dollar_get_simple(line + (*i) + 1, env, &ptr);
	if (str)
	{
		tmp = toto;
		toto = ft_strjoin(toto, str);
		ft_strdel(&tmp);
		(*i) = (*i) + ft_strlen(ptr);
	}
	else
	{
		(*i)++;
		while (ft_isalpha(line[*i]))
			(*i)++;
	}
	if (ptr)
		ft_strdel(&ptr);
	return (toto);
}

void	skip_alpha(char *line, int *i)
{
	(*i)++;
	while (ft_isalpha(line[*i]))
		(*i)++;
	(*i)--;
}

char	*dollar_handle_quoted(char *toto, char *line, int *i, t_quote sp)
{
	char	*str;
	char	*ptr;
	char	*kali;
	char	*tmp;

	if (sp.keeper == 39)
		toto = ft_joinchar(toto, '$');
	else if (sp.keeper == '"')
	{
		ptr = NULL;
		kali = ft_strfchr_alpha(line + *i + 1);
		str = dollar_get_quoted(kali, sp.env, &ptr);
		if (str)
		{
			tmp = toto;
			toto = ft_strjoin(toto, str);
			ft_strdel(&tmp);
			(*i) = (*i) + ft_strlen(ptr);
		}
		else
			skip_alpha(line, &(*i));
		ft_strdel(&kali);
		ft_strdel(&ptr);
	}
	return (toto);
}
