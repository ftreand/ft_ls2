/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_major_minor.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 12:23:37 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:50:14 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_major_minor(t_ls *ls)
{
	if (ls->mode[0] == 'c' || ls->mode[0] == 'b')
	{
		if (ft_num_len(ls->major) != 4)
			ft_pad(4 - ft_num_len(ls->major));
		ft_putnbr(ls->major);
		ft_putchar(',');
		if (ft_num_len(ls->minor) != 4)
			ft_pad(4 - ft_num_len(ls->minor));
		ft_putnbr(ls->minor);
	}
	else
	{
		ft_pad(8);
		ft_putnbr(ls->size);
	}
}
