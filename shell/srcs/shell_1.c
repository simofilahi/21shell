/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:37:04 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/17 15:34:35 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sys_cmd(char **command, char *arg, t_env **head_ref, pid_t *get)
{
	int		i;
	char	*tmp;
	char	*temp;
	char	**tab;

	if (ft_strncmp(arg, "./", 2) != 0)
	{
		if (!(tab = get_path(head_ref)))
		{
			path_gestion_error(arg);
			return ;
		}
		tmp = ft_strjoin("/", arg);
		i = -1;
		while (tab[++i])
		{
			temp = arg;
			(arg = ft_strjoin(tab[i], tmp)) ? ft_strdel(&temp) : 0;
			if (access(arg, F_OK) == 0)
				break ;
		}
		ft_free2d(tab);
		ft_strdel(&tmp);
	}
	execute(command, arg, head_ref, get);
}

void	child_pid(char **command, t_cmd *lst, t_env **head_ref, pid_t *get)
{
	char	*path;

	(void)lst;
	if (command[0])
	{
		path = ft_strdup(command[0]);
		if (path[0] == '/')
			execute(command, path, head_ref, get);
		else
			sys_cmd(command, path, head_ref, get);
	}
}

void	keephistorylst(t_his **his_tail, char *hline)
{
	t_his		*newnode;

	if (!(newnode = (t_his *)malloc(sizeof(t_his))))
		return ;
	newnode->hline = ft_strdup(hline);
	newnode->next = NULL;
	if (!(*his_tail))
	{
		(*his_tail) = newnode;
		(*his_tail)->prev = NULL;
	}
	else
	{
		newnode->prev = (*his_tail);
		(*his_tail)->next = newnode;
		(*his_tail) = newnode;
	}
}

int		just_spaces(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
			return (0);
	}
	return (1);
}

void	history_terminator(t_holder *h)
{
	if (h->linecpyflag)
	{
		keephistory(&h->his_tail, h->linecpy, h);
		ft_strdel(&h->linecpy);
	}
	else
		keephistory(&h->his_tail, h->line, h);
}
