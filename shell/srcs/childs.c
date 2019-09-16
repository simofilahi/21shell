/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 09:24:18 by aariss            #+#    #+#             */
/*   Updated: 2019/08/10 13:12:46 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		free_child(t_childs *lst)
{
	if (lst == NULL)
		return ;
	free_child(lst->next);
	free(lst);
	lst = NULL;
}

void		kill_pid(t_childs *c_head, int *keeper)
{
	t_childs *head;

	head = c_head;
	while (c_head)
	{
		if (c_head->child != 0 && c_head->index)
		{
			g_signal_num = 0;
			waitpid(c_head->child, 0, 0);
			g_signal_num = 1;
		}
		c_head = c_head->next;
	}
	while (head)
	{
		if (head->child != 0)
			kill(head->child, 9);
		head = head->next;
	}
	cheap_trick(keeper, 1);
}

t_childs	*create_child(pid_t child_pid, int *t, int def)
{
	t_childs *new;

	if (!(new = (t_childs*)malloc(sizeof(t_childs))))
		return (0);
	new->child = child_pid;
	new->index = def;
	new->next = NULL;
	(*t)++;
	return (new);
}
