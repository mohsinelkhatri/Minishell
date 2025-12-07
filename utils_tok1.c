/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tok1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:04:46 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 12:16:15 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(t_list *head)
{
	int	count;

	count = 0;
	while (head && head->type != T_PIPE)
	{
		if (head->type == T_WORD)
			count++;
		head = head->next;
	}
	return (count);
}

static int	handle_redirection(t_spcmd *cmd, t_list **tmp_ptr)
{
	t_list	*tmp;

	tmp = *tmp_ptr;
	if (tmp->next && tmp->next->type == T_WORD)
	{
		redir_lstadd_back(&cmd->redir, new_redir(tmp->type,
				tmp->next->content));
		*tmp_ptr = tmp->next;
		return (1);
	}
	else
	{
		ft_putstr_fd("Error: command must end with identifier\n", 2);
		check_env("?=", "2", set_get_env(NULL));
		return (0);
	}
}

t_spcmd	*parse_command_segment(t_list **tmp_ptr)
{
	t_list	*tmp;
	t_spcmd	*cmd;
	int		i;

	tmp = *tmp_ptr;
	init_parc(&cmd, &i, count_words(*tmp_ptr));
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type == T_WORD)
			cmd->cmd[i++] = ft_strdup(tmp->content);
		else if (is_redirection(tmp->type))
		{
			if (!handle_redirection(cmd, &tmp))
				return (NULL);
		}
		tmp = tmp->next;
	}
	cmd->cmd[i] = NULL;
	*tmp_ptr = tmp;
	return (cmd);
}

void	spcmd_lstadd_back(t_spcmd **lst, t_spcmd *new_node)
{
	t_spcmd	*temp;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

void	lose(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}
