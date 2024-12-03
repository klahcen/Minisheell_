/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:43:20 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/04 17:08:03 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_ha(void)
{
	g_all.q = 0;
	return (NULL);
}

t_cmd	*ft_set_arguments(char **args, t_cmd *cmd, t_redirect *first_redirect)
{
	t_exe	exe;

	exe.i = 0;
	exe.fd = -1;
	cmd->cmd = NULL;
	cmd->flags = NULL;
	cmd->files = NULL;
	if (args[0] == NULL || g_all.q == 1)
		return (ft_ha());
	ft_norm_hna(args, &exe.fd, &exe.i, first_redirect);
	while (args[exe.i] && args[exe.i + 1] && (ft_strcmp(args[exe.i], "<") == 0
			|| ft_strcmp(args[exe.i], ">") == 0 || ft_strcmp(args[exe.i],
				">>") == 0 || ft_strcmp(args[exe.i], "<<") == 0))
	{
		exe.i += 2;
		if (!args[exe.i] || !args[exe.i + 1])
			break ;
	}
	if (args[exe.i] && ft_strcmp(args[exe.i], "<") != 0
		&& ft_strcmp(args[exe.i], ">") != 0 && ft_strcmp(args[exe.i], ">>") != 0
		&& ft_strcmp(args[exe.i], "<<") != 0)
		cmd->cmd = args[exe.i++];
	cmd->args = (char **)ft_malloc(sizeof(char *) * (ft_args_len(args) + 1));
	exe.j = 0;
	return (ft_set_arguments2(args, cmd, exe.i, exe.j));
}

t_cmd	*ft_set_arguments2(char **args, t_cmd *cmd, int i, int j)
{
	while (args[i])
	{
		if (access(args[i], F_OK) == 0)
			cmd->files = ft_join(cmd->files, args[i]);
		else if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<") == 0 || ft_strcmp(args[i], "<<") == 0)
		{
			if (args[i + 1] == NULL)
			{
				printf("minishell: syntax error near unexpected token \n");
				return (NULL);
			}
			else if (!ft_strcmp(args[i + 1], ""))
				return (ft_error1(args[i + 1]));
			i += 2;
			continue ;
		}
		else if (!ft_strcmp(args[i], ""))
			return (ft_error1(args[i]));
		else
			cmd->args[j++] = args[i];
		i++;
	}
	cmd->args[j] = NULL;
	return (cmd);
}

void	ft_norm_hna(char **args, int *fd, int *i, t_redirect *first_redirect)
{
	(void)first_redirect;
	while (args[*i])
	{
		if (ft_strcmp(args[*i], "<") == 0)
		{
			if (args[*i + 1] == NULL)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token \n",
					2);
				return ;
			}
			if (args[*i + 2])
				close(*fd);
			else
				break ;
			*i += 2;
		}
		else
			break ;
	}
}
