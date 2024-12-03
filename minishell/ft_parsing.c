/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:42:45 by ysaber            #+#    #+#             */
/*   Updated: 2024/03/29 01:47:35 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_input(char *input, t_env **envir)
{
	t_parse	parse;

	if (input == NULL || ft_strlen(input) == 0)
		return ;
	if (ft_syntax_error(input) == 1)
		return ;
	parse.str = ft_set_spaces(input);
	parse.pipe = ft_split2(parse.str, "|");
	ft_check_pipe(parse.pipe);
	parse.i = 0;
	parse.node = ft_malloc(sizeof(t_node));
	parse.tmp = parse.node;
	while (parse.pipe[parse.i])
	{
		parse.tmp->args = ft_strdup(parse.pipe[parse.i]);
		if (parse.pipe[parse.i + 1])
		{
			parse.tmp->next = ft_malloc(sizeof(t_node));
			parse.tmp = parse.tmp->next;
		}
		else
			parse.tmp->next = NULL;
		parse.i++;
	}
	ft_minishell(parse.node, envir);
}

int	string_is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'
			&& str[i] != '\v' && str[i] != '\f')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_check_pipe(char **pipe)
{
	int	i;

	i = 0;
	while (pipe[i])
	{
		if (pipe[i + 1] == NULL)
			break ;
		if (pipe[i] == NULL || string_is_spaces(pipe[i]) == 1
			|| ft_strlen(pipe[i]) == 0)
		{
			ft_putstr_fd("Error: syntax error near unexpected token '|'\n", 2);
			g_all.status = 259;
			return ;
		}
		i++;
	}
}

void	ft_ascii(void)
{
	printf("\033[31m");
	printf("  __       __  __            __            ");
	printf("__                  __  __ \n");
	printf("/  \\     /  |/  |          /  ");
	printf("|          /  |                /  |/  |\n");
	printf("$$  \\   /$$ |$$/  _______  $$/   _______ ");
	printf("$$ |____    ______  $$ |$$ |\n");
	printf("$$$  \\ /$$$ |/  |/       \\ /  |");
	printf(" /       |$$      \\  /      \\ $$ |$$ |\n");
	printf("$$$$  /$$$$ |$$ |$$$$$$$  |$$ ");
	printf("|/$$$$$$$/ $$$$$$$  |/$$$$$$  |$$ |$$ |\n");
	printf("$$ $$ $$/$$ |$$ |$$ |  $$ |$$ |$$      \\ ");
	printf("$$ |  $$ |$$    $$ |$$ |$$ |\n");
	printf("$$ |$$$/ $$ |$$ |$$ |  $$ |$$ |");
	printf(" $$$$$$  |$$ |  $$ |$$$$$$$$/ $$ |$$ |\n");
	printf("$$ | $/  $$ |$$ |$$ |  $$ |$$ |/     ");
	printf("$$/ $$ |  $$ |$$       |$$ |$$ |\n");
	printf("$$/      $$/ $$/ $$/   $$/ $$/ $$$");
	printf("$$$$/  $$/   $$/  $$$$$$$/ $$/ $$/ \n");
	printf("\033[0m");
}
