/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:21:01 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/04 16:46:05 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_buil(t_cmd *cmd, t_env **envir, int pip)
{
	if (!pip)
	{
		if (!ft_strcmp("cd", ft_last_world(cmd->cmd)))
		{
			if (cmd->redirect)
			{
				if (cmd->redirect->type == 1 || cmd->redirect->type == 3)
				{
					cmd->redirect->fd = open(cmd->redirect->file,
							O_CREAT | O_WRONLY | O_TRUNC, 0644);
					if (cmd->redirect->fd == -1)
						(perror(cmd->redirect->file), exit(1));
				}
			}
			return (ft_cd(cmd, *envir));
		}
		if (!cmd->redirect)
		{
			if (!ft_builtins(cmd, envir))
				return (0);
		}
	}
	return (-1);
}

int	ft_red_next(t_redirect *red)
{
	if (access(red->file, R_OK) == -1)
		(perror(red->file), exit(1));
	red->fd = open(red->file, O_RDONLY);
	if (red->fd == -1)
		(perror(red->file), exit(1));
	return (red->fd);
}

void	ft_next_echo(t_cmd *tmp, char *str, int i)
{
	if (tmp && tmp->args)
	{
		if (tmp->files)
			printf("%s ", tmp->files);
		if (!ft_strcmp(tmp->args[0], str))
			i++;
		while (tmp->args[i])
		{
			printf("%s ", tmp->args[i]);
			i++;
		}
	}
	if (ft_strcmp(tmp->args[0], str))
		printf("\n");
}
