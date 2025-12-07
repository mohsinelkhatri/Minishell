/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:27:51 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/29 11:37:30 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_spcmd_nodes(t_spcmd *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	if (count == 0)
		check_env("?=", "0", set_get_env(NULL));
	return (count);
}

int	is_built_in(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->var, "?=") != 0)
		{
			if (env->val[0] != '\0' || ft_strchr(env->var, '=') != NULL)
				printf("%s%s\n", env->var, env->val);
		}
		env = env->next;
	}
	check_env("?=", "0", env);
}

char	*get_env_value(const char *key, t_env *env)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->var, key, len) == 0 && env->var[len] == '=')
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

void	ft_exuction(t_spcmd *list, t_env **env)
{
	if (count_spcmd_nodes(list) == 1 && list->redir == NULL)
	{
		if (is_built_in(list->cmd[0]))
			ex_built_in(list, env);
		else
			execute_external(list, *env);
	}
	else
	{
		execute_pipeline(list, *env);
	}
}
