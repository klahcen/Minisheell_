/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:57:59 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/04 17:22:52 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle(int signum)
{
	(void)signum;
	g_all.status = 130;
	write(1, "\n", 1);
	if (g_all.c == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle2(int signum)
{
	(void)signum;
	write(2, "Quit: 3\n", 9);
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*envir;

	if (ac != 1)
		return (1);
	(void)av;
	envir = ft_get_env(env);
	g_all.status = 0;
	g_all.c = 0;
	signal(SIGINT, handle);
	(signal(SIGQUIT, SIG_IGN), ft_ascii());
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			(write(1, "exit\n", 5));
			break ;
		}
		g_all.c = 1;
		(ft_parse_input(input, &envir), add_history(input));
		free(input);
		g_all.c = 0;
	}
	ft_free_all(envir);
}
