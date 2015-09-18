/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:53:14 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:53:15 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>

int			ft_usage(char c)
{
	if (c)
		ft_fdprintf(2, "ft_script: illegal option -- %c\n", c);
	ft_fdprintf(2, "usage: ft_script [-aq] [file [command ...]]\n");
	return (-1);
}

int			ft_err(int ret, char *str)
{
	ft_fdprintf(2, str);
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	int			i;
	t_script	args;

	ft_bzero(&args, sizeof(t_script));
	args.env = env;
	if ((i = ft_option(ac, av, "aq", &args.option)) == -1)
		return (ft_usage(0));
	args.filename = (*(av += i)) ? *av : DFILE;
	if ((args.out_file = open(args.filename, (args.option & OPT_A)
		? F_APPEND : F_WRITE, F_RIGHTS)) == -1)
		return (ft_err(-1, "Error : Failing opening file"));
	args.command = (*av && *(av++)) ? av : NULL;
	if (!launch_script(&args))
		return (ft_err(-1, "Error"));
	close(args.out_file);
	return (0);
}
