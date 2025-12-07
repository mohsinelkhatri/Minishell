/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex20.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:03:23 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/30 13:47:53 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_nodes(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

static char	*build_env_string(t_env *node)
{
	int		len_var;
	int		len_val;
	char	*str;

	len_var = ft_strlen(node->var);
	len_val = ft_strlen(node->val);
	str = ft_malloc(len_var + len_val + 2, &set_get_data(NULL)->lst_gc_g);
	if (!str)
		return (NULL);
	ft_strlcpy(str, node->var, len_var + 1);
	str[len_var] = '=';
	ft_strlcpy(str + len_var + 1, node->val, len_val + 1);
	return (str);
}

char	**reverse_env(t_env *lst)
{
	int		count;
	char	**str_arr;
	int		i;

	count = count_env_nodes(lst);
	str_arr = ft_malloc(sizeof(char *) * (count + 1),
			&set_get_data(NULL)->lst_gc_g);
	i = 0;
	while (lst)
	{
		if (ft_strcmp(lst->var, "LD_PRELOAD") != 0)
			find_and_remove_var("LD_PRELOAD", &lst);
		else
		{
			str_arr[i] = build_env_string(lst);
			if (!str_arr[i])
				return (NULL);
			i++;
		}
		lst = lst->next;
	}
	str_arr[i] = NULL;
	return (str_arr);
}
