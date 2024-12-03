/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:02:02 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/01 05:25:18 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_next_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	(ft_putstr_fd(str, 2), ft_putstr_fd(" Is a directory\n", 2));
	exit(126);
}

void	ft_error(char *str)
{
	char	*s;

	if (str[0] == '/' || str[0] == '.')
	{
		s = ft_strjoin(str, "/");
		if (access(s, F_OK) != -1)
			ft_next_error(str);
		else if (access(str, F_OK | W_OK | R_OK) != -1)
		{
			(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(str, 2));
			ft_putstr_fd(" Permission denied\n", 2);
			exit(126);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			perror(str);
			exit(126);
		}
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" command not found\n", 2);
	g_all.status = 127;
	exit(127);
}

void	ft_closered(t_cmd *cmd)
{
	t_redirect	*data;

	while (cmd)
	{
		data = cmd->redirect;
		while (data)
		{
			close(data->pip[1]);
			data = data->next;
		}
		cmd = cmd->next;
	}
}

void	ft_closered1(t_cmd *cmd)
{
	t_redirect	*data;

	while (cmd)
	{
		data = cmd->redirect;
		while (data)
		{
			close(data->pip[1]);
			data = data->next;
		}
		cmd = cmd->next;
	}
}

int	ft_nbr_her(t_cmd *tmp)
{
	int			nbr_her;
	t_redirect	*red;

	nbr_her = 0;
	red = tmp->redirect;
	while (red)
	{
		if (pipe(red->pip) == -1)
		{
			perror("pipe");
			exit(1);
		}
		nbr_her++;
		red = red->next;
	}
	return (nbr_her);
}
