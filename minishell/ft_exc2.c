/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:14:23 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/04 01:16:44 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_advance_expand(char *str, t_env *envir)
{
	t_exe	exe;

	if (str == NULL)
		return (NULL);
	exe.i = 0;
	while (str[exe.i] && str[exe.i] != '$')
		exe.i++;
	exe.s1 = ft_substr(str, 0, exe.i);
	if (str[exe.i] == '\0')
		return (exe.s1);
	exe.i++;
	exe.len = exe.i;
	while (str[exe.i] && (ft_isalnum(str[exe.i]) || str[exe.i] == '_'))
		exe.i++;
	exe.s3 = ft_substr(str, exe.len, exe.i - exe.len);
	exe.s2 = ft_get_env_value(exe.s3, envir);
	free(exe.s3);
	if (exe.s2 == NULL)
		return (str);
	exe.s1 = ft_strjoin2(exe.s1, exe.s2, &str[exe.i]);
	free(str);
	return (exe.s1);
}

void	ft_red_doc(t_redirect *tmp)
{
	char	*str;
	t_exe	nor;

	tmp->status = 1;
	tmp->fd = tmp->pip[0];
	nor.i = ft_strlen(tmp->lim);
	tmp->lim = ft_strtrim(tmp->lim, "\'\"");
	nor.k = ft_strlen(tmp->lim);
	while (1)
	{
		str = readline("> ");
		if (tmp->lim && ft_strcmp(tmp->lim, str))
		{
			if (nor.i == nor.k && ft_strchr(str, '$'))
				str = ft_advance_expand(str, tmp->envir);
		}
		if (!str || !ft_strcmp(tmp->lim, str))
			break ;
		ft_putstr_fd(str, tmp->pip[1]);
		write(tmp->pip[1], "\n", 1);
		free(str);
		str = NULL;
	}
}

void	ft_next_red(t_redirect *red)
{
	red->fd = open(red->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (red->fd == -1)
		(perror(red->file), exit(1));
	(dup2(red->fd, 1), close(red->fd));
}

void	ft_next_red1(t_redirect *red)
{
	red->fd = open(red->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (red->fd == -1)
		(perror(red->file), exit(1));
	(dup2(red->fd, 1), close(red->fd));
}

void	ft_redirect(t_redirect *red)
{
	int	i;
	int	pip;

	i = 0;
	pip = -1;
	while (red)
	{
		if (red->type == 1)
			ft_next_red(red);
		if (red->type == 2)
			pip = ft_red_next(red);
		if (red->type == 3)
			ft_next_red1(red);
		if (red->type == 4)
			pip = red->pip[0];
		red = red->next;
		i++;
	}
	if (pip != -1)
		(dup2(pip, 0), close(pip));
}
