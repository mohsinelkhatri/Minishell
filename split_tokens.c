/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:13:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/27 18:38:18 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(t_token_type type, const char *file)
{
	t_redir	*node;

	node = ft_malloc(sizeof(t_redir), &(set_get_data(NULL)->lst_gc_g));
	node->type = type;
	node->file = ft_strdup(file);
	node->next = NULL;
	return (node);
}

int	ft_lstadd_back_prc(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!lst || !new)
		return (1);
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

void	redir_lstadd_back(t_redir **lst, t_redir *new)
{
	t_redir	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	init_parc(t_spcmd **cmd, int *i, int size)
{
	*cmd = ft_malloc(sizeof(t_spcmd), &(set_get_data(NULL)->lst_gc_g));
	(*cmd)->cmd = ft_malloc(sizeof(char *) * (size + 1),
			&(set_get_data(NULL)->lst_gc_g));
	(*cmd)->redir = NULL;
	(*cmd)->next = NULL;
	*i = 0;
}
