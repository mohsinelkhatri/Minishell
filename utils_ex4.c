/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:52:59 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/26 13:15:57 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_name(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*join_tokens_with_spaces(t_list *tokens)
{
	size_t	total_len;
	t_list	*tmp;
	char	*result;

	total_len = 0;
	tmp = tokens;
	while (tmp)
	{
		total_len += strlen(tmp->content) + 1;
		tmp = tmp->next;
	}
	result = ft_malloc(total_len, &set_get_data(NULL)->lst_gc_g);
	if (!result)
		return (NULL);
	result[0] = '\0';
	tmp = tokens;
	while (tmp)
	{
		strcat(result, tmp->content);
		if (tmp->next)
			strcat(result, " ");
		tmp = tmp->next;
	}
	return (result);
}
