/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex13.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:12:27 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 14:15:38 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_format(t_env *curr)
{
	if (ft_strcmp(curr->var, "?=") == 0)
		return ;
	if (ft_strchr(curr->var, '=') != NULL && curr->val[0] == '\0')
		printf("declare -x %s\"\"\n", curr->var);
	else if (curr->val[0] == '\0')
		printf("declare -x %s\n", curr->var);
	else
		printf("declare -x %s\"%s\"\n", curr->var, curr->val);
}

static void	print_all_exports(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		print_export_format(curr);
		curr = curr->next;
	}
}

static void	export_args(char **cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_export(cmd[i], env);
		i++;
	}
}

void	ft_export_hp(t_spcmd *lst, t_env **env)
{
	if (lst->cmd[1] == NULL)
	{
		print_all_exports(*env);
		check_env("?=", "0", *env);
		return ;
	}
	export_args(lst->cmd, env);
}

void	handle_env_variable(char *str, t_pd *pd, t_env *lst)
{
	pd->start = ++pd->i;
	while (ft_isalnum(str[pd->i]) || (str[pd->i] == '_' || str[pd->i] == '?'))
	{
		if (str[pd->i] == '?' && str[pd->i - 1] == '$')
		{
			pd->i++;
			break ;
		}
		pd->i++;
	}
	pd->env_name = ft_substr(str, pd->start, pd->i - pd->start);
	pd->env_val = ft_getenv(pd->env_name, lst);
	if (pd->env_val)
	{
		if (check_space(pd->env_val))
			handle_env_with_spaces(pd);
		else
			pd->result = ft_strjoin(pd->result, ft_strdup(pd->env_val));
	}
}
