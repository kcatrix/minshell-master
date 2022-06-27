/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2022/02/02 13:13:55 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	g_env = {0, 0, NULL, NULL, 0, 0};

void	loop(void)
{
	int		i;

	i = 0;
	set_signal(1);
	while (g_env.lines[i])
	{
		exec(g_env.lines[i]->cmds, 0);
		i++;
	}
	set_signal(0);
	free_lines();
}

int	is_error(char *str, int i, int j, int k)
{
	if (!str[j] || (k == 0 && str[i] == '|'))
	{
		printf("minishell: syntax error near unexpected token '%c'\n", str[i]);
		g_env.error = 1;
		g_env.status = 258;
		free(str);
		return (1);
	}
	return (0);
}

void	check_line(char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '.' && str[i] != ' '
			&& str[i] != '\'' && str[i] != '"' && str[i] != '$'
			&& str[i] != '/' && str[i] != '=')
		{
			j = i;
			k = i;
			while ((str[j] == str[i] || str[j] == ' ') && str[j])
				j++;
			while ((str[k] == str[i] || str[k] == ' ') && k)
				k--;
			if (is_error(str, i, j, k))
				return ;
		}
		i++;
	}
	parse(str);
}

int	main(int argc, char *argv[], char **ev)
{
	char	*line;

	(void) argc;
	(void) argv;
	init(ev);
	while (1)
	{
		g_env.error = 0;
		g_env.fork = 0;
		line = readline(SHELL_TEXT);
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		expend(&line);
		check_line(line);
		if (g_env.error <= 0)
			loop();
	}
}
