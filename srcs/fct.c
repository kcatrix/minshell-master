/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2022/02/01 18:17:29 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(int fd, t_cmd *cmd)
{
	int		i;
	int		ln;

	ln = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-' && is_only_n(cmd->args[1] + 1))
		ln = 1;
	i = 1 + ln;
	while (cmd->args[i])
	{
		putstr(fd, cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			putstr(fd, " ");
		i++;
	}
	if (!ln)
		putstr(fd, "\n");
	g_env.status = 0;
}

void	cmd_pwd(int fd)
{
	char	*path;

	path = get_var_env("PWD");
	if (path != NULL)
		putstr_endl(fd, path);
	g_env.status = 0;
}

void	cmd_exit(t_cmd *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (cmd->args[1])
	{
		if (is_num(cmd->args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->args[1]);
			return ;
		}
		if (cmd->args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		exit_status = ft_atoi(cmd->args[1]);
	}
	printf("exit\n");
	free_lines();
	exit(exit_status);
}

char	*get_new_path(char *path)
{
	char	*var;
	int		i;
	char	*tmp;

	var = ft_strdup(get_var_env("PWD"));
	if (!ft_strcmp(path, "."))
		return (var);
	else if (!ft_strcmp(path, ".."))
	{
		i = ft_strlen(var);
		while (var[i] != '/' || !var[i + 1])
			i--;
		while (var[i])
			var[i++] = '\0';
	}
	else
	{
		tmp = ft_strjoin(var, "/");
		free(var);
		var = ft_strjoin(tmp, path);
		free(tmp);
	}
	return (var);
}

void	cmd_cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->args[1] == NULL)
		path = get_var_env("HOME");
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		putstr(1, "cd: ");
		perror(path);
		g_env.status = 1;
	}
	else
	{
		add_var_env(ft_strdup("OLDPWD"), ft_strdup(get_var_env("PWD")));
		if (path == get_var_env("HOME"))
			set_var_env(ft_strdup("PWD"), ft_strdup(path));
		else
			set_var_env(ft_strdup("PWD"), get_new_path(path));
		g_env.status = 0;
	}
}
