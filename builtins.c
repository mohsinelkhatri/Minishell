/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:28:25 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/29 10:57:25 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *var)
{
	int	j;

	j = 0;
	srch(var, &j);
	return (ft_substr(var, 0, j));
}

static void	remove_env_var(t_env **env, t_env *curr, t_env *prev)
{
	if (prev)
		prev->next = curr->next;
	else
		*env = curr->next;
}

void	find_and_remove_var(char *var_name, t_env **env)
{
	t_env	*curr;
	t_env	*prev;
	char	*str;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		str = get_var_name(curr->var);
		if (ft_strcmp(str, var_name) == 0)
		{
			remove_env_var(env, curr, prev);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_spcmd *lst, t_env **env)
{
	int	i;

	if (!lst->cmd[1])
		return ;
	i = 1;
	while (lst->cmd[i])
	{
		if (ft_strcmp(lst->cmd[i], "?") == 0)
		{
			i++;
			continue ;
		}
		find_and_remove_var(lst->cmd[i], env);
		i++;
	}
	check_env("?=", "0", *env);
}

int	validate_cd_args(t_spcmd *lst, t_env **env)
{
	if (lst->cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		check_env("?=", "1", *env);
		return (1);
	}
	return (0);
}
