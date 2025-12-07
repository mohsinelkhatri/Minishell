/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:55:00 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/26 13:38:26 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int	handle_meta_token(char *str, int *i, t_list **head)
{
	if (ft_lstadd_back(head, chr_meta(str, i)) == 1)
		return (1);
	return (0);
}

int	handle_word_token(char *str, int *i, t_list **head, int flag)
{
	int	start;

	start = *i;
	while (str[*i] && !is_meta(str[*i]) && str[*i] != ' ')
		get_pos(str, i);
	if (*i > start)
	{
		if (ft_lstadd_back(head, fill_node(ft_substr(str, start, *i - start),
					T_WORD, flag)) == 1)
			return (1);
	}
	return (0);
}

void	cleanup_heredoc_files(t_list *hd)
{
	t_list	*tmp;

	tmp = hd;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC && tmp->next)
			unlink(tmp->next->content);
		tmp = tmp->next;
	}
}
