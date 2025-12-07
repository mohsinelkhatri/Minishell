/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:20 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/26 14:15:21 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_case(t_dolar2 *st)
{
	if (st->current->next != NULL)
	{
		ft_lstadd_back(&st->tmp,
			fill_node(ft_strdup(st->current->content),
				st->current->type, st->current->remove_qoute));
		st->current = st->current->next;
		ft_lstadd_back(&st->tmp,
			fill_node(ft_strdup(st->current->content),
				st->current->type,
				st->current->remove_qoute));
		st->current = st->current->next;
	}
}

static void	handle_no_dollar(t_dolar2 *st)
{
	ft_lstadd_back(&st->tmp,
		fill_node(ft_strdup(st->current->content),
			st->current->type,
			st->current->remove_qoute));
	st->current = st->current->next;
}

static void	handle_with_dollar(t_dolar2 *st, t_env *env)
{
	st->processed = process_node_content2(st->current->content, env,
			get_last_node_content(st->tmp));
	join_lists(&st->tmp, st->processed);
	st->current = st->current->next;
}

t_list	*convert_dolar2(t_list **list, t_env *env)
{
	t_dolar2	st;

	init_st(&st, *list);
	while (st.current)
	{
		if (st.current->type == T_HEREDOC)
		{
			handle_heredoc_case(&st);
			continue ;
		}
		if (present_dolar(st.current->content) == 0)
			handle_no_dollar(&st);
		else
			handle_with_dollar(&st, env);
	}
	return (st.tmp);
}
