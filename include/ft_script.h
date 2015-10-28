/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:12:36 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/28 18:44:19 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H

# define FT_SCRIPT_H

# define OPT_Q		0x1
# define OPT_A		0x2
# define OPT_K		0x4
# define OPT_T		0x8

# define DFILE		"typescript"
# define DSHELL		"/bin/sh"

# define F_WRITE	(O_WRONLY | O_CREAT | O_TRUNC)
# define F_APPEND	(O_WRONLY | O_CREAT | O_APPEND)
# define F_RIGHTS	(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

# define STV		((struct timeval){0, 0})

# include "libft.h"
# include <termios.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

typedef struct			s_script
{
	int					option;
	char				*filename;
	int					out_file;
	char				**command;
	char				**env;
	struct termios		term;
	int					fds[2];
}						t_script;

int						launch_script(t_script *args);
int						ft_openpt(int *master, int *slave);
int						slave(t_script *args, int fd_slave, int fd_master);
void					script_master(t_script *script);
int						ft_print_err(int n, char *cmd);

int						term_init(t_script *args);
void					term_restore(t_script *args);

#endif
