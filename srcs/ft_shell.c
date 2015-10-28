/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:53:07 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/28 18:41:15 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

char	*m_getenv(char *str, char **env)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(str);
	while (env && env[++i])
		if (!strncmp(str, env[i], len) && (env[i][len] == '='))
			return (env[i] + len + 1);
	return (NULL);
}

char	*ft_getpath(char *cmd, char **env)
{
	char			*path;
	static char		str[256];
	int				i;
	int				j;

	i = 0;
	j = 0;
	path = m_getenv("PATH", env);
	while (path && path[i])
	{
		if (path[i++] == ':')
		{
			path[i - 1] = '\0';
			ft_bzero(&str, 256);
			ft_strcat(ft_strcat(ft_strcat(str, path + j), "/"), cmd);
			if (access(str, X_OK) >= 0)
				return (path = str);
			j = i;
		}
	}
	return (NULL);
}

int		ft_print_err(int n, char *cmd)
{
	if (n <= 0)
		ft_fdprint(2, "script: %s: No such file or directory\n", cmd);
	return (n >= 0 ? 1 : 0);
}

int		ft_getexec(char **cmd, char **env)
{
	return (access(cmd[0], X_OK) < 0 ?
		execve(ft_getpath(cmd[0], env), cmd, env) :
		execve(cmd[0], cmd, env));
}

int		slave(t_script *args, int fd_slave, int fd_master)
{
	char *tab[3];

	tab[0] = NULL;
	tab[1] = "-i";
	tab[2] = NULL;
	(void)fd_master;
	dup2(fd_slave, 0);
	dup2(fd_slave, 1);
	dup2(fd_slave, 2);
	close(fd_slave);
	setsid();
	ioctl(0, TIOCSCTTY, 1);
	if (args->command == NULL || !args->command[0])
	{
		if ((tab[0] = m_getenv("SHELL", args->env)) == NULL)
			tab[0] = DSHELL;
		return (ft_print_err(ft_getexec(tab, args->env), tab[0]));
	}
	else
		return (ft_print_err(ft_getexec(args->command, args->env),
			args->command[0]));
}
