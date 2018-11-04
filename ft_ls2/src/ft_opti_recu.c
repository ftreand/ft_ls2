/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_opti_recu.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/24 16:58:34 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:49:59 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <errno.h>
#include <stdio.h>

void	ft_opti_recu0(t_flags fg, t_ls **ls, t_ls *padd, t_ls *begin)
{
	t_pad pad;

	if (!fg.a)
	{
		while (padd->d_name[0] == '.' && padd->next)
			padd = padd->next;
		padd->d_name[0] == '.' ? fg.i = 0 : fg.i;
	}
	pad = ft_padding(&padd);
	ft_print_base((*ls)->path);
	if (fg.i)
		ft_display(begin, &fg, &pad);
}

void	ft_manage_reverse(t_ls **ls)
{
	while ((*ls)->next)
		(*ls) = (*ls)->next;
}

void	ft_manage_no_a(t_flags fg, t_ls **ls)
{
	while (!fg.a && (*ls)->d_name[0] == '.')
	{
		if (((*ls)->prev && fg.r) || ((*ls)->next && !fg.r))
			(*ls) = fg.r ? (*ls)->prev : (*ls)->next;
		else
			break ;
	}
}

void	ft_recursive1(t_ls **ls, t_flags fg, char *path)
{
	DIR		*dir;

	while (ls)
	{
		ft_manage_no_a(fg, &(*ls));
		if ((*ls) && ((*ls)->type == 4 && ((*ls)->d_name[0] != '.'
						|| (((*ls)->d_name[1] && (*ls)->d_name[1] != '.')))))
		{
			errno = 0;
			dir = opendir((*ls)->path);
			if (errno)
				ft_recursive_error(ls, fg);
			else
				ft_recursive_no_error(ls, fg, path, dir);
		}
		if ((((*ls)->next) && !fg.r) || ((*ls)->prev && fg.r))
			(*ls) = fg.r ? (*ls)->prev : (*ls)->next;
		else
			break ;
	}
}

void	ft_recursive(t_ls **ls, t_flags fg, char *path)
{
	t_ls	*tmp;

	tmp = (*ls);
	if (fg.r)
		ft_manage_reverse(&(*ls));
	fg.i = 1;
	ft_recursive1(ls, fg, path);
	(*ls) = tmp;
	ft_free_list((*ls));
}
