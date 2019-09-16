/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:43:29 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 20:56:53 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t__mc	*mc_lst(char **mc)
{
	t__mc	*lst;
	t__mc	*head;
	int		i;

	if (!(lst = (t__mc*)malloc(sizeof(t__mc))))
		return (NULL);
	i = 0;
	while (mc[i])
	{
		lst->cmd = ft_strsplit(mc[i], -4);
		i++;
		if (i == 1)
			head = lst;
		if (!mc[i])
			break ;
		if (!(lst->next = (t__mc*)malloc(sizeof(t__mc))))
			return (NULL);
		lst = lst->next;
	}
	lst->next = NULL;
	return (head);
}

int		count_delim(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ';')
		i++;
	if (!line[i])
		return (1);
	return (0);
}

t__mc	*make_one_mc(char *line)
{
	t__mc	*lst;

	if (!(lst = (t__mc*)malloc(sizeof(t__mc))))
		return (NULL);
	if (!(lst->cmd = (char**)malloc(sizeof(char*) * 2)))
		return (0);
	lst->cmd[0] = ft_strdup(line);
	lst->cmd[1] = NULL;
	lst->next = NULL;
	return (lst);
}

t__mc	*mc_maker(char *line, t_env *env)
{
	char		**slice;
	char		*parsed;
	t__mc		*lst;

	if (count_delim(line))
	{
		ft_strdel(&line);
		return (NULL);
	}
	parsed = parsin(line, env);
	ft_strdel(&line);
	if (ft_strlen(parsed) == 0)
	{
		ft_strdel(&parsed);
		return (make_one_mc(" "));
	}
	else
	{
		slice = ft_strsplit(parsed, -3);
		ft_strdel(&parsed);
		lst = mc_lst(slice);
		ft_free2d(slice);
	}
	return (lst);
}
