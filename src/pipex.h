/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 11:13:03 by pcampos-          #+#    #+#             */
/*   Updated: 2022/05/02 16:13:29 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//------------------------------INCLUDES------------------------------//
# include	"./libft/libft.h"
# include	<fcntl.h>
# include	<stdio.h>
# include	<sys/types.h>
# include	<sys/wait.h>

//------------------------------STRUCTS------------------------------//

typedef struct s_geral {
	int		infile;
	int		outfile;
	int		heredoc;
	int		ncmd;
	int		vcmd;
	int		pipe[2];
	int		cmd_id;
	pid_t	pid;
	char	**args;
	char	**path;
	char	*cmd_path;
	char	**cmd;

}				t_geral;

//------------------------------PIPEX_MAIN------------------------------//
void		get_path(t_geral *vars, char **env);
void		start_piping(t_geral *vars, int id, char **env);

//------------------------------CHECK_ARGS------------------------------//
void		check_args(t_geral *vars, int ac, char **av);
void		handle_here_doc(t_geral *vars, int ac, char **av);
void		fill_heredoc(char **av, int fd);
void		handle_in_out(t_geral *vars, char **av, int ac);

//------------------------------GET_CMD------------------------------//
void		get_cmd(t_geral *vars, int id);
void		good_path(t_geral *vars);
char		*check_cmd_path(char *tmp);
void		get_cmd_path(t_geral *vars);

//------------------------------ERROR_HANDLER------------------------------//
void		error_handler(t_geral *vars, int op);
void		free_all(t_geral *vars);
void		free_path(t_geral *vars);

#endif
