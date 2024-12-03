/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:48:04 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/01 17:28:14 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_calloc(size_t count, size_t size)
{
	char	*new;
	size_t	i;

	new = ft_malloc(count * size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		new[i] = 0;
		i++;
	}
	return (new);
}

void	increment_and_assign(char *str, char *line, int *i, int *i2)
{
	str[*i] = line[*i2];
	(*i)++;
	(*i2)++;
}

void	ft_woquote_2(char *line, int *i, int *i2, char *str)
{
	char	c;
	int		quote_open;

	quote_open = 0;
	if (line[*i2] && ft_strchr("\'\"", line[*i2]) && (*i2 == 0 || line[*i2 \
			- 1] != '$'))
	{
		c = line[*i2];
		quote_open = 1;
		(*i2)++;
		while (line[*i2] && line[*i2] != c)
			increment_and_assign(str, line, i, i2);
		if (line[*i2] == c && line[*i2] != '\0')
		{
			quote_open = 0;
			(*i2)++;
		}
	}
	else if (line[*i2])
		increment_and_assign(str, line, i, i2);
	if (quote_open)
	{
		ft_putstr_fd("Syntax error:  unclosed quotes\n", 2);
		g_all.q = 1;
	}
}

char	*ft_woquote_3(char *line)
{
	int		i;
	int		i2;
	char	*str;

	str = ft_calloc(sizeof(char), (ft_strlen(line) + 1));
	i = 0;
	i2 = 0;
	while (line[i2])
		ft_woquote_2(line, &i, &i2, str);
	str[i] = 0;
	return (str);
}

char	*remove_all_quotes(char *line)
{
	char	*str;

	str = NULL;
	if (!line)
		return (0);
	if (ft_strchr(line, '\'') || ft_strchr(line, '\"'))
		str = ft_woquote_3(line);
	else
		return (ft_strdup(line));
	return (str);
}
