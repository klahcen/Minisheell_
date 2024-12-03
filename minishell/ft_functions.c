/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:43:30 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/01 05:23:56 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_input(char *input, int *i, int *in_quotes, int *special_chars)
{
	if (input[*i] == '\"')
	{
		*in_quotes = !(*in_quotes);
	}
	else if (!(*in_quotes) && ft_strchr("><|", input[*i]))
	{
		(*special_chars)++;
		if ((input[*i] == '>' || input[*i] == '<') && input[*i \
			+ 1] == input[*i])
		{
			(*i)++;
		}
	}
	(*i)++;
	return (*special_chars);
}

void	process_special_chars(t_exe *exe, char *input)
{
	exe->s1[exe->j++] = ' ';
	exe->s1[exe->j++] = input[exe->i];
	if ((input[exe->i] == '>' || input[exe->i] == '<') && input[exe->i \
		+ 1] == input[exe->i])
	{
		exe->s1[exe->j++] = input[++exe->i];
	}
	exe->s1[exe->j++] = ' ';
}

char	*ft_set_spaces(char *input)
{
	t_exe	exe;

	exe.ac = 0;
	exe.ac = 0;
	exe.status = 0;
	exe.i = 0;
	while (input[exe.i])
		exe.ac = process_input(input, &exe.i, &exe.status, &exe.ac);
	exe.s1 = ft_malloc(sizeof(char) * (ft_strlen(input) + exe.ac * 2 + 1));
	exe.i = 0;
	exe.j = 0;
	while (input[exe.i])
	{
		if (input[exe.i] == '\"')
			exe.status = !exe.status;
		if (!exe.status && ft_strchr("><|", input[exe.i]))
			process_special_chars(&exe, input);
		else
			exe.s1[exe.j++] = input[exe.i];
		exe.i++;
	}
	exe.s1[exe.j] = '\0';
	return (exe.s1);
}
