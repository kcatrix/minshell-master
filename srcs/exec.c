/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:40:15 by lmataris          #+#    #+#             */
/*   Updated: 2022/02/02 13:14:02 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	select_cmd(t_cmd **cmd, int out)
{
	if (!cmd[1] && !is_redirect_out(cmd[0]->redirections))
		out = 1;
	if (!ft_strcmp(ECHOC, cmd[0]->kw))
		cmd_echo(out, cmd[0]);
	else if (!ft_strcmp(PWD, cmd[0]->kw))
		cmd_pwd(out);
	else if (!ft_strcmp(ENV, cmd[0]->kw))
		cmd_env(out);
	else if (!ft_strcmp(CD, cmd[0]->kw))
		cmd_cd(cmd[0]);
	else if (!ft_strcmp(EXPORT, cmd[0]->kw))
		cmd_export(out, cmd[0]);
	else if (!ft_strcmp(UNSET, cmd[0]->kw))
		cmd_unset(cmd[0]);
	else if (!ft_strcmp(EXIT, cmd[0]->kw))
		cmd_exit(cmd[0]);
	else
		return (0);
	return (1);
}

void	test(int pid, t_cmd	*cmd)
{
	int		status;

	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (!cmd)
			g_env.status = WEXITSTATUS(status);
	}
}

void	exec(t_cmd **cmds, int in)
{
	int		pipes[2];
	int		redirect_out;
	int		redirect_in;
	int		pid;

	redirect_out = 0;
	redirect_in = 0;
	pid = -1;
	get_redirect(cmds[0]->redirections, &redirect_in, &redirect_out);
	if (g_env.error != 0)
		return ;
	if (redirect_in)
		in = redirect_in;
	pipe(pipes);
	if (!select_cmd(cmds, pipes[1]))
		pid = cmd_exec(cmds, pipes, in);
	g_env.fork = pid;
	close(pipes[1]);
	if (redirect_out)
		write_redirection(pipes[0], redirect_out);
	if (cmds[1])
		exec(cmds + 1, pipes[0]);
	close(pipes[0]);
	test(pid, cmds[1]);
}
