/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display_flag.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/06 15:43:01 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/06 15:43:04 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */



#include "ft_ls.h"
#include <stdio.h>

void	ft_display_reverse(t_ls *ls, t_flags fg, t_pad * pad)
{

}

void	ft_display(t_ls *ls, t_flags fg, t_pad *pad)
{
	if (fg.r)
	{
		while (ls->next)
			ls = ls->next;
		ft_display_reverse(ls, fg, pad);
		printf("ls d_name = %s\n", ls->d_name);
	}
}
