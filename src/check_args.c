/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:58:18 by pcampos-          #+#    #+#             */
/*   Updated: 2022/05/02 17:04:21 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_heredoc(char **av, int fd)
{
	char	*buf;
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strdup(av[2]);
	tmp = ft_strjoin(tmp2, "\n");
	while (1)
	{
		ft_printf("here_doc: ");
		buf = get_next_line(0);
		if (buf)
		{
			if (ft_strlen(buf) == ft_strlen(tmp))
				if (!ft_strncmp(tmp, buf, ft_strlen(av[2])))
					break ;
			write(fd, buf, ft_strlen(buf));
			free (buf);
		}
		else
			break ;
	}
	free (tmp);
	free (tmp2);
	free (buf);
}

void	handle_here_doc(t_geral *vars, int ac, char **av)
{
	int	fd;

	if (ac < 6)
	{
		ft_printf("Argumentos insuficientes, tenta novamente\n");
		exit(EXIT_FAILURE);
	}
	vars->heredoc = 1;
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	vars->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || vars->outfile < 0)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	fill_heredoc(av, fd);
	close(fd);
	vars->infile = open(".heredoc_tmp", O_RDONLY);
	if (vars->infile < 0)
	{
		unlink(".heredoc_tmp");
		exit(1);
	}
}

void	handle_in_out(t_geral *vars, char **av, int ac)
{
	vars->infile = open(av[1], O_RDONLY);
	vars->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	vars->heredoc = 0;
	if (vars-> infile < 0 || vars->outfile < 0)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
}

void	check_args(t_geral *vars, int ac, char **av)
{
	int	i;
	int	j;

	if (!ft_strncmp(av[1], "here_doc", 9))
		handle_here_doc(vars, ac, av);
	else
		handle_in_out(vars, av, ac);
	vars->args = malloc(sizeof(char *) * ac);
	if (!vars->args)
		error_handler(vars, 1);
	i = 1;
	j = -1;
	while (++i < ac)
		vars->args[++j] = ft_strdup(av[i]);
	vars->args[++j] = 0;
}
