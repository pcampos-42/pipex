/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 11:01:49 by pcampos-          #+#    #+#             */
/*   Updated: 2022/05/02 17:04:51 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_piping(t_geral *vars, int id, char **env)
{
	if (pipe(vars->pipe) == -1)
		error_handler(vars, 1);
	vars->pid = fork();
	if (vars->pid < 0)
		error_handler(vars, 1);
	if (!vars->pid)
	{
		close (vars->pipe[0]);
		if (vars->cmd_id == 0)
		{
			dup2 (vars->infile, STDIN_FILENO);
			dup2 (vars->pipe[1], STDOUT_FILENO);
		}
		else if (vars->cmd_id == vars->ncmd - 1)
			dup2 (vars->outfile, STDOUT_FILENO);
		else
			dup2 (vars->pipe[1], STDOUT_FILENO);
		get_cmd(vars, id);
		execve(vars->cmd_path, vars->cmd, env);
		error_handler(vars, 3);
	}
	close (vars->pipe[1]);
	wait(NULL);
	dup2 (vars->pipe[0], STDIN_FILENO);
}

void	get_path(t_geral *vars, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			tmp = ft_strdup(env[i] + 5);
	}
	if (!tmp)
		error_handler(vars, 1);
	vars->path = ft_split(tmp, ':');
	free (tmp);
}

int	main(int ac, char **av, char **env)
{
	t_geral	vars;

	if (ac < 5)
	{
		ft_printf("Argumentos insuficientes. Tenta novamente.\n");
		exit(EXIT_FAILURE);
	}
	check_args(&vars, ac, av);
	vars.ncmd = ac - 3 - vars.heredoc;
	get_path(&vars, env);
	vars.cmd_id = -1;
	while (++vars.cmd_id < vars.ncmd)
		start_piping(&vars, vars.cmd_id + vars.heredoc, env);
	if (vars.heredoc)
		unlink(".heredoc_tmp");
	free_all(&vars);
	return (0);
}
