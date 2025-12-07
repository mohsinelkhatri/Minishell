/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:05:35 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/27 19:07:18 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pd(t_pd *pd)
{
	pd->i = 0;
	pd->result = ft_strdup("");
	pd->tmp = NULL;
}

char	*join_in_dqout(char *str)
{
	char	*result;

	result = ft_strjoin("\"", str);
	result = ft_strjoin(result, "\"");
	return (result);
}

void	handle_quoted_string(char *str, t_pd *pd)
{
	pd->helper = extract_quoted_substring(str, &pd->i, str[pd->i]);
	pd->result = ft_strjoin(pd->result, pd->helper);
}

void	handle_assignment(char *str, t_pd *pd)
{
	pd->start = pd->i;
	while (str[pd->i] && str[pd->i] != ' ')
		pd->i++;
	pd->helper = ft_substr(str, pd->start, pd->i - pd->start);
	pd->helper = join_in_dqout(pd->helper);
	pd->result = ft_strjoin(pd->result, pd->helper);
}

void	handle_env_with_spaces(t_pd *pd)
{
	pd->sp = 0;
	while (pd->env_val[pd->sp] && pd->env_val[pd->sp] != ' ')
		pd->sp++;
	if (pd->sp > 0)
	{
		pd->first = ft_substr(pd->env_val, 0, pd->sp);
		pd->result = ft_strjoin(pd->result, pd->first);
		ft_lstadd_back(&pd->tmp, fill_node(ft_strdup(pd->result), T_WORD, 1));
		pd->result = ft_strdup("\0");
	}
	if (pd->env_val[pd->sp] != '\0')
	{
		if (pd->result[0] != '\0')
			ft_lstadd_back(&pd->tmp, fill_node(pd->result, T_WORD, 0));
		join_lists(&pd->tmp, split_dolar(pd->env_val + pd->sp));
		pd->result = ft_strdup("");
	}
}
