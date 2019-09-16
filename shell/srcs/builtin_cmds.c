/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:50:38 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/10 11:42:23 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** set new variables to environment;
*/

int		setenv_cmd(char *arg, char *sarg, t_env **head_ref, int flag)
{
	char *tmp;
	char *s;

	tmp = NULL;
	s = ft_strjoin(arg, "=");
	del_node(s, head_ref);
	tmp = s;
	if (flag)
	{
		s = ft_strjoin(tmp, sarg);
		add_node(head_ref, s, flag);
		ft_strdel(&s);
	}
	else
		add_node(head_ref, s, flag);
	(tmp != NULL) ? ft_strdel(&tmp) : 0;
	return (1);
}

void	builtin_cmd_2(t_holder *h, int j, int i, int flag)
{
	while (h->lst->cmd[i])
	{
		if ((j == 2 && i == 2) || (j == 3 && error_cases(h->lst->cmd)))
			return ;
		else if (j == 1)
		{
			if ((ft_strcmp(h->lst->cmd[1], "-n") == 0) && i == 1)
				flag = 1;
			echo_cmd(h->lst->cmd[i], h->lst->cmd[i + 1], flag);
		}
		else if (j == 2)
			ft_chdir(h->lst->cmd[i], NULL, &h->head_ref, 0);
		else if (j == 3)
		{
			flag = (h->lst->cmd[i + 1]) ? 1 : 0;
			if (!setenv_cmd(h->lst->cmd[i], h->lst->cmd[i + 1], \
				&h->head_ref, flag) || flag)
				return ;
		}
		else if (j == 4)
			del_node(h->lst->cmd[i], &h->head_ref);
		else if (j == 6)
			which_cmd(h->lst->cmd[i], &h->head_ref);
		i++;
	}
}

void	builtin_cmds_1(t_holder *h, int j, int i, int flag)
{
	if ((ft_strcmp(h->lst->cmd[0], "cd") == 0) && !h->lst->cmd[1])
		ft_chdir(h->lst->cmd[0], NULL, &h->head_ref, 1);
	else
		builtin_cmd_2(h, j, i, flag);
}

void	builtin_cmds(t_holder *h, int j)
{
	int flag;

	flag = 0;
	if (j == 5)
		print_env(&h->head_ref);
	else if (j == 1 && !h->lst->cmd[1])
		echo_cmd(NULL, NULL, flag);
	else if (j == 7)
	{
		free_structure(h, 1);
		exit(0);
	}
	else
		builtin_cmds_1(h, j, 1, flag);
}

int		own_commands(char *cmd)
{
	char	*command[9];
	int		i;

	command[1] = "echo";
	command[2] = "cd";
	command[3] = "setenv";
	command[4] = "unsetenv";
	command[5] = "env";
	command[6] = "which";
	command[7] = "exit";
	command[8] = NULL;
	i = 1;
	while (command[i])
	{
		if ((ft_strcmp(cmd, command[i]) == 0))
			return (i);
		i++;
	}
	return (0);
}
