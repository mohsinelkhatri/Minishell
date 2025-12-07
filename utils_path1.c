/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:11:17 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 16:10:52 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	return (NULL);
}

static char	**get_paths_from_env(t_env *env)
{
	char	*path_env;

	path_env = ft_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}

static char	*search_path_in_dirs(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*full_path;

	if (!cmd)
		return (NULL);
	full_path = is_direct_path(cmd);
	if (full_path)
		return (full_path);
	paths = get_paths_from_env(env);
	if (!paths)
		return (NULL);
	full_path = search_path_in_dirs(paths, cmd);
	return (full_path);
}
