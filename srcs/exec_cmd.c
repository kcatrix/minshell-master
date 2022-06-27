/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:18:49 by acolin            #+#    #+#             */
/*   Updated: 2022/02/01 13:03:42 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirect_out(t_redir **redir)
{
	t_redir		*r;

	r = *redir;
	while (r)
	{
		if (r->type == 0 || r->type == 1)
			return (1);
		r = r->next;
	}
	return (0);
}

int	ft_exec(t_cmd **cmd, char *path, int *pipe, int in)
{	
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (in)
			dup2(in, STDIN_FILENO);
		close(pipe[0]);
		if (cmd[1] || is_redirect_out(cmd[0]->redirections))
			dup2(pipe[1], STDOUT_FILENO);
		if (execve(path, cmd[0]->args, g_env.var_env) == -1)
			perror(path);
		exit(1);
	}
	free(path);
	return (pid);
}

char	*get_exec_path(char *cmd, char *path, int *exist)
{
	char	**splited_path;
	char	*test;
	int		i;

	i = 0;
	if (!get_var_env("PATH"))
		return (NULL);
	splited_path = ft_split(get_var_env("PATH"), ':');
	while (splited_path[i])
	{
		test = ft_strjoin(splited_path[i], "/");
		path = ft_strjoin(test, cmd);
		free(test);
		if (open(path, O_RDONLY) > -1)
		{
			*exist = 1;
			free_cmds(splited_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_cmds(splited_path);
	return (NULL);
}

int	is_path(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	cmd_exec(t_cmd **cmd, int *pipe, int in)
{
	char	*path;
	int		exist;

	exist = 0;
	path = NULL;
	if (open(cmd[0]->kw, O_RDONLY) > -1)
	{
		exist = 1;
		path = ft_strdup(cmd[0]->kw);
	}
	else if (!is_path(cmd[0]->kw))
		path = get_exec_path(cmd[0]->kw, path, &exist);
	if (exist == 0)
	{
		printf("minishell: %s: command not found\n", cmd[0]->kw);
		g_env.status = 127;
	}
	else
		return (ft_exec(cmd, path, pipe, in));
	return (0);
}
