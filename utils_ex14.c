/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex14.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:16:03 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 10:36:04 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *str, int *index)
{
	srch(str, index);
	return (ft_substr(str, 0, *index + 1));
}

static char	*get_value(char *str, int i)
{
	if ((size_t)i == ft_strlen(str) - 1)
		return (ft_strdup(""));
	else
		return (ft_substr(str, i + 1, ft_strlen(str) - i - 1));
}

static void	handle_export_with_value(char *str, t_env **env, char *var, int i)
{
	char	*val;

	val = get_value(str, i);
	if (check_env(var, val, *env) == 1)
	{
		return ;
	}
	ft_env_add_back(env, ft_env_new(var, val));
}

static void	handle_export_without_value(t_env **env, char *var)
{
	char	*val;

	if (!check_env(var, NULL, *env))
	{
		val = ft_strdup("");
		ft_env_add_back(env, ft_env_new(var, val));
	}
}

void	ft_export(char *str, t_env **env)
{
	int		i;
	char	*var;

	if (!is_valid_var_name(str))
	{
		ft_putstr_fd(ft_strjoin3("export: `", str,
				"': not a valid identifier\n"), 2);
		check_env("?=", "1", *env);
		return ;
	}
	i = 0;
	var = get_var_name(str, &i);
	if (str[i] == '=')
		handle_export_with_value(str, env, var, i);
	else
		handle_export_without_value(env, var);
	check_env("?=", "0", *env);
}
