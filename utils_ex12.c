/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex12.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:58:37 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/26 14:24:02 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_quote(char *str, t_pd *pd)
{
	pd->i++;
	pd->helper = extract_quoted_substring(str, &pd->i, str[pd->i]);
	pd->result = ft_strjoin(pd->result, pd->helper);
}

int	get_last_node_content(t_list *head)
{
	t_list	*current;

	if (head == NULL)
		return (1);
	current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (ft_strcmp(current->content, "export"));
}

t_list	*process_node_content2(char *str, t_env *lst, int flag)
{
	t_pd	pd;

	init_pd(&pd);
	while (str[pd.i])
	{
		if (str[pd.i] == '"' || str[pd.i] == '\'')
			handle_quoted_string(str, &pd);
		else if (str[pd.i] == '=' && str[pd.i + 1] != ' ' && flag == 0)
			handle_assignment(str, &pd);
		else if (str[pd.i] == '$' && (ft_isalpha(str[pd.i + 1]) || (str[pd.i
						+ 1] == '_' || str[pd.i + 1] == '?')))
			handle_env_variable(str, &pd, lst);
		else if (str[pd.i] == '$' && str[pd.i + 1] == '\'')
			handle_dollar_quote(str, &pd);
		else
		{
			pd.result = ft_strjoin(pd.result, ft_substr(str, pd.i, 1));
			pd.i++;
		}
	}
	if (pd.result && *pd.result)
		ft_lstadd_back(&pd.tmp, fill_node(pd.result, T_WORD, 0));
	return (pd.tmp);
}

void	init_st(t_dolar2 *st, t_list *list)
{
	st->tmp = NULL;
	st->current = list;
}

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}
