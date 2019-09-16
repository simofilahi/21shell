/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:11:50 by aariss            #+#    #+#             */
/*   Updated: 2019/08/07 19:24:26 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_info(t_info *lst)
{
	if (lst == NULL)
		return ;
	free_info(lst->next);
	if (lst->file)
		ft_strdel(&lst->file);
	free(lst);
	lst = NULL;
}

void	free_main_lst(t_cmd *lst)
{
	if (lst == NULL)
		return ;
	free_main_lst(lst->next);
	free_info(lst->red);
	ft_free2d(lst->cmd);
	free(lst);
	lst = NULL;
}

void	free_list_env(t_env **head_ref)
{
	t_env	*current;

	while ((*head_ref))
	{
		current = *head_ref;
		*head_ref = (*head_ref)->next;
		ft_strdel(&current->var);
		ft_strdel(&current->value);
		free(current);
		current = NULL;
	}
}

void	free_list_mc(t__mc *lst)
{
	t__mc	*current;

	current = lst;
	while (lst)
	{
		current = lst;
		lst = lst->next;
		ft_free2d(current->cmd);
		free(current);
		current = NULL;
	}
}

void	free_list_history(t_his *his_tail)
{
	t_his *current;

	while (his_tail)
	{
		current = his_tail;
		ft_strdel(&current->hline);
		his_tail = his_tail->prev;
		free(current);
		current = NULL;
	}
}
