/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:20:10 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/02 14:51:04 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str + i, "||") == 0 || ft_strcmp(str + i, "&&") == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			ft_putstr_fd(str + i, 2);
			ft_putstr_fd("'\n", 2);
			g_all.status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}

int	gha_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}
