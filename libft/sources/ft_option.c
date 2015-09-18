/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:28:28 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:28:33 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_pow(int i, int exposant)
{
	return ((exposant == 0) ? i * ft_pow(i, --exposant) : 1);
}

static void	ft_option_error(char *prog, char c)
{
	char *s;

	s = prog;
	while (*prog)
		prog++;
	write(2, s, prog - s);
	write(2, ": illegal option -- ", 20);
	write(2, &c, 1);
	write(2, "\n", 1);
}

static int	ft_mark_option(char **av, const char *list, int *opt, char *str)
{
	char *s;

	s = (char *)list;
	while (*str)
	{
		list = s;
		while (*list)
		{
			if (*list == *str && (*opt |= ft_pow(2, list - s)))
				break ;
			list++;
		}
		if (!*list)
			return (ft_option_error(av[0], *str), 0);
		str++;
	}
	return (1);
}

static int	ft_get_option(char **av, const char *list, int *option)
{
	int i;

	i = 1;
	*option = 0;
	while (av[i])
	{
		if (av[i][0] != '-')
			break ;
		if (!av[i][1] || (av[i][1] == '-' && i++))
			break ;
		if (!ft_mark_option(av, list, option, &av[i][1]))
			return (-1);
		i++;
	}
	return (i);
}

int			ft_option(int ac, char **av, const char *list, int *option)
{
	char *s;

	if (ac == 1)
		return (1);
	s = (char *)list;
	while (*list)
		list++;
	if (list - s >= 32)
		return (write(2, "Error : Too many option\n", 24), -1);
	return (ft_get_option(av, s, option));
}
