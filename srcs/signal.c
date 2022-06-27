/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2022/02/02 09:28:02 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interrupt_signal(int signal)
{
	(void) signal;
	if (g_env.fork)
	{
		kill(g_env.fork, SIGINT);
		write(1, "\n", 1);
		g_env.fork = 0;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	quit_signal(int signum)
{
	if (g_env.fork)
	{
		kill(g_env.fork, signum);
		if (signum == SIGQUIT)
			printf("Quit: 3\n");
		g_env.fork = 0;
		return ;
	}
	if (signum == 11)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(int is_printed)
{
	struct termios	t;

	tcgetattr(0, &t);
	if (is_printed)
		(&t)->c_lflag |= ECHOCTL;
	else
		(&t)->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
