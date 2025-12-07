/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:03:05 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/27 19:07:37 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_next_word(char *str, int i, int *start)
{
	*start = i;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

static int	add_word_node(t_list **head, char *str, int start, int end)
{
	char	*word;
	t_list	*node;

	word = ft_substr(str, start, end - start);
	node = fill_node(word, T_WORD, 1);
	if (ft_lstadd_back(head, node) == 1)
		return (1);
	return (0);
}

t_list	*split_dolar(char *str)
{
	int		i;
	int		start;
	t_list	*head;
	int		end;

	i = 0;
	start = 0;
	head = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (str[i] == '\0')
			break ;
		end = get_next_word(str, i, &start);
		if (end > start)
		{
			if (add_word_node(&head, str, start, end))
				return (NULL);
		}
		i = end;
	}
	return (head);
}
