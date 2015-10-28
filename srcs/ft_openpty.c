/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openpty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:52:56 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/28 18:38:23 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <fcntl.h>

#include "libft.h"

char *g_msg_err[] = {"Error opening master file\n", "Error grant tty\n", \
	"Error unlocking tty\n", "Error getting tty name\n", \
	"Error opening slave file\n"};
/*
** posix_openpt :
**			opens the first available master pseudo-terminal device
**			equivalent to opening /dev/ptmx
** grantpt :
**			establish ownership and permissions of the slave device
**			TIOCPTYGRANT request using ioctl
** unlockpt :
**			unlocks the slave pseudo-terminal device
**			TIOCPTYUNLK request using ioctl
** ptsname :
**			full pathname of the slave device
**			TIOCPTYGNAME request using ioctl + open on file name
*/

int			ft_openpt(int *master, int *slave)
{
	int				index;
	struct winsize	win;
	char			ptsname[128];

	index = 0;
	if (ioctl(0, TIOCGWINSZ, &win) != 0)
		return (0);
	if (((*master = open("/dev/ptmx", O_RDWR)) < 0) || !++index ||
		(ioctl(*master, TIOCPTYGRANT) != 0) || !++index ||
		(ioctl(*master, TIOCPTYUNLK) != 0) || !++index ||
		(ioctl(*master, TIOCPTYGNAME, ptsname) != 0) || !++index ||
		((*slave = open(ptsname, O_RDWR)) < 0) || !++index ||
		(ioctl(*master, TIOCSWINSZ, &win) != 0))
	{
		ft_fdprint(2, g_msg_err[index]);
		return (0);
	}
	if (ioctl(*master, TIOCSWINSZ, &win) != 0)
		return (0);
	return (1);
}
