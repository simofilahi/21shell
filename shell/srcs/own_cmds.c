/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:55:56 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/17 14:53:23 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_chdir_1(char **pathtmp, char **lastcwd, t_env **head_ref, int flag)
{
	char	buff[1024];

	if (flag)
	{
		ft_strdel(pathtmp);
		if (!((*pathtmp) = get_var("HOME=", head_ref)))
			return (0);
	}
	if (ft_strcmp((*pathtmp), "-") == 0)
	{
		ft_strdel(pathtmp);
		if (!((*pathtmp = get_var("OLDPWD=", head_ref))))
			return (0);
	}
	ft_bzero(buff, 1024);
	(*lastcwd) = ft_strdup(getcwd(buff, sizeof(buff)));
	return (1);
}

void	ft_chdir_free(char **pathtmp, char **cwd, char **lastcwd)
{
	ft_strdel(pathtmp);
	ft_strdel(cwd);
	ft_strdel(lastcwd);
}

void	ft_chdir(char *path, char *cwd, t_env **head_ref, int flag)
{
	char	buff[1024];
	char	*pathtmp;
	DIR		*dir;
	char	*lastcwd;

	pathtmp = ft_strdup(path);
	if (!(ft_chdir_1(&pathtmp, &lastcwd, head_ref, flag)))
		return ;
	if (access(pathtmp, F_OK) == 0)
	{
		if (access(pathtmp, X_OK) == 0)
		{
			chdir(pathtmp);
			cwd = ft_strdup(getcwd(buff, sizeof(buff)));
			swap(head_ref, lastcwd, cwd);
			ft_chdir_free(&pathtmp, &cwd, &lastcwd);
			return ;
		}
		(!(dir = opendir(pathtmp))) ? chdir_gerror(pathtmp, 0) :\
		chdir_gerror(pathtmp, 1);
		(dir) ? closedir(dir) : 0;
	}
	else
		chdir_gerror(pathtmp, 2);
	ft_chdir_free(&pathtmp, &cwd, &lastcwd);
}

void	echo_cmd(char *arg, char *narg, int flag)
{
	if (arg == NULL)
		ft_putchar_fd('\n', 1);
	else if (ft_strcmp(arg, "-n") == 0)
		return ;
	else if (arg && !narg && flag)
		ft_putstr_fd(arg, 1);
	else if (arg && !narg && !flag)
		ft_putendl_fd(arg, 1);
	else if (arg && narg)
	{
		ft_putstr_fd(arg, 1);
		ft_putchar_fd(' ', 1);
	}
}
