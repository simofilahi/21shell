/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:31:34 by mfilahi           #+#    #+#             */
/*   Updated: 2019/08/10 11:44:26 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		len_of_list(t_env **head_ref)
{
	t_env	*current;
	int		counter;

	current = *head_ref;
	counter = 0;
	while (current)
	{
		current = current->next;
		counter++;
	}
	return (counter);
}

void	print_env(t_env **head_ref)
{
	t_env *current;

	current = *head_ref;
	while (current)
	{
		if (current->var)
			ft_putstr_fd(current->var, 1);
		if (current->value)
			ft_putstr_fd(current->value, 1);
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}

char	*get_var(char *deli, t_env **head_ref)
{
	t_env *current;

	current = *head_ref;
	while (current)
	{
		if (ft_strcmp(deli, current->var) == 0)
		{
			if (current->value)
				return (ft_strdup(current->value));
			return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}

void	swap(t_env **head_ref, char *lastcwd, char *cwd)
{
	t_env	*current;

	current = *head_ref;
	while (current)
	{
		if (ft_strcmp("OLDPWD=", current->var) == 0)
		{
			ft_strdel(&current->value);
			current->value = ft_strdup(lastcwd);
		}
		if (ft_strcmp("PWD=", current->var) == 0)
		{
			ft_strdel(&current->value);
			current->value = ft_strdup(cwd);
		}
		current = current->next;
	}
}

t_env	*copy_of_env(char **env)
{
	t_env	*head;
	t_env	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = -1;
	while (env[++i])
		createlist(&head, &tail, env[i]);
	return (head);
}
