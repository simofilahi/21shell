/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:38:37 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/10 17:37:17 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	keephistory(t_his **his_tail, char *hline, t_holder *h)
{
	int			len;
	static char	*lline;

	len = ft_strlen(hline);
	hline[len - 1] = '\0';
	if (!(*his_tail))
		lline = ft_strdup(hline);
	else
	{
		if (ft_strcmp(hline, lline) == 0)
			return ;
		free(lline);
		lline = ft_strdup(hline);
		h->stctmp = lline;
	}
	keephistorylst(his_tail, hline);
}

/*
** - get line from readline func;
*/

char	*call_readline(t_holder *h, int *flag)
{
	if (g_signal_num == 3)
		g_signal_num = 1;
	else
	{
		h->line = ft_readline("$> ", h->his_tail, 0);
		if (g_signal_num == 3)
			g_signal_num = 1;
		ft_putchar_fd('\n', 1);
	}
	*flag = 0;
	if (!h->line)
	{
		*flag = 1;
		return (NULL);
	}
	else if (h->line[0] == '\n' || just_spaces(h->line))
	{
		ft_strdel(&h->line);
		h->line = NULL;
		return (h->line);
	}
	return (recall_readline(h));
}

void	shell_1(t_holder *h, int i, int count)
{
	t_cmd	*valhala;
	t__mc	*curr;

	history_terminator(h);
	if (!syntax_error(h->line))
		return ;
	h->linecpyflag = 0;
	h->mclst = mc_maker(h->line, h->head_ref);
	curr = h->mclst;
	if (!(count = count_mclst(curr)))
		return ;
	while (++i < count)
	{
		valhala = last_splice(&curr, h->head_ref);
		h->lst = valhala;
		if (valhala->cmd[0])
			darlin_g(h);
		h->lst = valhala;
		free_main_lst(valhala);
	}
	free_list_mc(h->mclst);
}

void	shell(t_holder *h)
{
	int			flag;

	flag = 0;
	while ("21sh")
	{
		while (((!(call_readline(h, &flag)) && !flag)) || (g_signal_num == 3))
			;
		if (!flag)
		{
			if (h->line[0] == PIPE)
			{
				ft_putstr_fd("21sh: parse error near ", 2);
				ft_putchar_fd(h->line[0], 2);
				ft_putchar_fd('\n', 2);
				ft_strdel(&h->line);
			}
			else
				shell_1(h, -1, 0);
			reset_fds();
		}
		else
			break ;
	}
}

int		main(int ac, char **av, char **envp)
{
	t_holder *h;

	(void)ac;
	(void)av;
	g_signal_num = 1;
	signal(SIGINT, signal_handler);
	h = ft_memalloc(sizeof(t_holder));
	h->head_ref = copy_of_env(envp);
	shell(h);
	free_structure(h, 0);
	return (0);
}
