/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:10:26 by aariss            #+#    #+#             */
/*   Updated: 2019/08/16 20:26:27 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		avoid_quote(char *line, int i, int param)
{
	int keeper;

	keeper = line[i];
	i++;
	while (line[i] != keeper && line[i])
		i++;
	if (line[i] && line[i] == keeper)
		if (param)
			i++;
	return (i);
}

int		count_special_case(char *line, char token)
{
	int	i;
	int	len;
	int	count;

	i = 0;
	len = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]))
			i = avoid_quote(line, i, 0);
		if (line[i] == token)
			len = 0;
		else if (++len == 1)
			count++;
		i++;
	}
	return (count);
}

int		syntax_check(char *line, int find)
{
	int	i;
	int	count;
	int	keeper;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == find)
			count++;
		else if (ft_isquote(line[i]))
		{
			keeper = line[i];
			i++;
			while (line[i] != keeper)
				i++;
		}
		i++;
	}
	return (count);
}

int		syntax_error(char *line)
{
	int	t;

	t = 1;
	if (syntax_check(line, '|') + 1 != count_special_case(line, '|'))
		t = 0;
	else if (syntax_check(line, ';') == 1 && count_special_case(line, ';') == 1)
		t = 1;
	else if (syntax_check(line, ';') + 1 != count_special_case(line, ';'))
		t = 0;
	if (t == 0)
		ft_putendl_fd("21sh: syntax error near unexpected token `\'", 2);
	return (t);
}

void	reset_fds(void)
{
	int fd;

	fd = open("/dev/tty", O_RDWR);
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	close(fd);
}
