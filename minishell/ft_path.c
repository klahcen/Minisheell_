/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:12:40 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/04 17:07:49 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_path(char **path_split, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (!path_split || !*path_split || cmd == NULL || cmd[0] == '\0')
		return (cmd);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	while (path_split[i])
	{
		cmd_path = ft_strjoin2(path_split[i], "/", cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			return (cmd_path);
		}
		i++;
	}
	return (NULL);
}

t_cmd	*ft_get_path(t_cmd *cmd, t_env *envir)
{
	t_cmd	*tmp;
	char	*path;
	char	**path_split;
	char	*cmd_path;

	if (!cmd)
		return (NULL);
	tmp = cmd;
	path = ft_get_env_value("PATH", envir);
	path_split = ft_split(path, ':');
	while (tmp)
	{
		cmd_path = find_cmd_path(path_split, tmp->cmd);
		if (cmd_path)
			tmp->cmd = cmd_path;
		tmp = tmp->next;
	}
	return (cmd);
}

char	*ft_get_env_value(char *name, t_env *envir)
{
	t_env	*tmp;

	tmp = envir;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
