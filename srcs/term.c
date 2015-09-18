/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:53:38 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:53:39 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <termios.h>

int		term_init(t_script *args)
{
	struct termios	tmp;

	if (ioctl(0, TIOCGETA, &tmp) < 0)
		return (0);
	args->term = tmp;
	tmp.c_iflag &= ~(IGNBRK | BRKINT | PARMRK |
		ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	tmp.c_oflag &= ~(OPOST);
	tmp.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tmp.c_cflag &= ~(CSIZE | PARENB);
	tmp.c_cflag |= CS8;
	tmp.c_cc[VMIN] = 1;
	tmp.c_cc[VTIME] = 0;
	if (ioctl(0, TIOCSETAW, &tmp))
		return (0);
	return (1);
}

void	term_restore(t_script *args)
{
	ioctl(0, TIOCSETAW, &(args->term));
}
