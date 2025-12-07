/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:57:39 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/29 13:25:43 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static char	*get_var_key(char *var)
{
	int	i;

	i = 0;
	srch(var, &i);
	if (var[i] == '=')
		return (ft_substr(var, 0, i));
	else
		return (var);
}

static int	compare_var_keys(char *key1, char *key2)
{
	int		i;
	char	*sub_key2;
	int		cmp_result;

	i = 0;
	srch(key2, &i);
	sub_key2 = ft_substr(key2, 0, i);
	cmp_result = ft_strcmp(key1, sub_key2);
	return (cmp_result);
}

int	check_env(char *var, char *val, t_env *lst)
{
	char	*key;

	key = get_var_key(var);
	while (lst)
	{
		if (compare_var_keys(key, lst->var) == 0)
		{
			if (val != NULL)
			{
				lst->var = ft_strdup_env(var);
				lst->val = ft_strdup_env(val);
			}
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}
