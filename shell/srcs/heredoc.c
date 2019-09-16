/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recall_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 18:45:41 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/10 17:41:54 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_needle(char *s, char **needle)
{
	int	end;
	int	start;

	start = 0;
	while (s[start] && s[start] == ' ')
		start++;
	end = start;
	while (s[end] &&\
			!(s[end + 1] == ' ' || s[end + 1] == '\n') &&\
			!metacharacters(s[end + 1], 0) &&\
			!metacharacters(s[end + 1], 1) &&\
			!((s[end + 1] == '<') || (s[end + 1] == '<' && s[end + 2] == '<'))\
			&& !(s[end + 1] == '>'))
	{
		end++;
	}
	if (start == end)
		end += 1;
	*needle = ft_strsub(s, start, (end > start) ? end - start : end);
	if (ft_strlen(*needle) >= 1 && !(*needle[0] == '\n'))
		return (1);
	return (0);
}

static int	heredoc_is_found(char *s, char **needle, int *index)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == SQUOTE || *s == DQUOTE)
			return (0);
		if (*s == '<' && *(s + 1) == '<')
		{
			if (i == *index)
			{
				if (get_needle(s + 2, needle))
					return (1);
				else
					return (0);
			}
			i++;
		}
		s++;
	}
	return (0);
}

static char	*join_in_line(char *str, char *heredoc, char *ptr, int *counter)
{
	int		key;
	char	*tmp;
	char	*ptr_2;
	int		len;
	int		i;

	ptr = ft_strdup("");
	ptr_2 = ft_strdup(str);
	key = get_len_before_heredoc(str, *counter);
	i = key;
	if (ptr_2[key] == ' ')
		key++;
	ptr_2[key] = '\0';
	ptr = ft_joinchar(ptr, '"');
	tmp = heredoc;
	(heredoc = ft_strjoin(ptr, heredoc)) ? ft_strdel(&ptr) : 0;
	ft_strdel(&tmp);
	(heredoc = ft_joinchar(heredoc, '"'));
	(tmp = ft_strjoin(ptr_2, heredoc)) ? ft_strdel(&ptr_2) : 0;
	ft_strdel(&heredoc);
	len = get_len_of_needle(str + i);
	ptr = tmp;
	(tmp = ft_strjoin(tmp, str + len + i)) ? ft_strdel(&ptr) : 0;
	ft_strdel(&str);
	return (tmp);
}

static int	heredoc_handler_1(t_holder *h, char **line, char *s, char *needle)
{
	while ((s = ft_readline("<<.", h->his_tail, 1)))
	{
		ft_putchar_fd('\n', 1);
		if (g_signal_num == 3)
		{
			ft_strdel(&(*line));
			(*line = ft_strdup(s)) ? ft_strdel(&s) : 0;
			return (0);
		}
		if ((ft_strncmp(s, needle, ft_strlen(needle)) == 0))
		{
			free_heredoc_helper(needle, s);
			return (1);
		}
		else
		{
			h->tmp = h->heredoc;
			(h->heredoc = ft_strjoin(h->heredoc, s)) ? ft_strdel(&h->tmp) : 0;
			ft_strdel(&s);
		}
	}
	ft_putchar_fd('\n', 1);
	ft_strdel(&needle);
	return ((h->hdocflg = 1));
}

int			heredoc_handler(t_holder *h, char **line)
{
	char	*needle;
	char	*s;
	int		counter;
	char	*tmp;

	needle = NULL;
	s = NULL;
	tmp = ft_strdup(*line);
	counter = 0;
	while (heredoc_is_found(*line, &needle, &counter))
	{
		if (h->hdocflg)
			break ;
		if (h->linecpyflag == 0)
			h->linecpy = ft_strdup(*line);
		h->linecpyflag = 1;
		h->heredoc = ft_strnew(1);
		if (!(heredoc_handler_1(h, line, NULL, needle)))
			return (0);
		tmp = join_in_line(tmp, h->heredoc, NULL, &counter);
		counter++;
	}
	h->hdocflg = 0;
	*line = heredoc_new_line(&tmp, line);
	return (1);
}
