/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:56:52 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/17 15:39:11 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*execute_error(char *arg, char *path)
{
	char		*msgerror;
	struct stat	buffer;

	stat(arg, &buffer);
	msgerror = NULL;
	if (S_ISDIR(buffer.st_mode))
		msgerror = ft_strjoin(arg, ": is a directory");
	else if (access(path, F_OK) == -1)
		msgerror = ft_strjoin("command not found: ", arg);
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		msgerror = ft_strjoin("permission denied: ", arg);
	return (msgerror);
}

void	execute(char **command, char *path_found, t_env **head_ref, pid_t *get)
{
	pid_t		child_pid;
	char		*msgerror;
	char		**env;

	env = get_env(head_ref);
	msgerror = execute_error(command[0], path_found);
	if (!msgerror)
	{
		child_pid = fork();
		*get = child_pid;
		if (child_pid == 0)
			execve(path_found, command, env);
	}
	else
		ft_putendl_fd(msgerror, 2);
	ft_strdel(&path_found);
	ft_strdel(&msgerror);
	ft_free2d(env);
}

char	**get_path(t_env **head_ref)
{
	t_env	*current;

	current = *head_ref;
	while (current)
	{
		if (ft_strcmp(current->var, "PATH=") == 0)
			return (ft_strsplit(current->value, ':'));
		current = current->next;
	}
	return (NULL);
}

void	signal_handler(int sign)
{
	t_package *p;

	p = cloud(NULL);
	if (sign == SIGINT && g_signal_num > 0)
	{
		end_key(p);
		ft_putchar('\n');
		ft_putstr_fd("\033[1;34m$> \033[0m", 1);
		g_signal_num = 2;
	}
}

void	add_node_1(t_env *curr, t_env *new_node)
{
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}
