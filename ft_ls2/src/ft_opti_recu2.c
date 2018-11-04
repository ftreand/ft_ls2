/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_opti_recu2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/25 11:27:37 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:49:55 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

void	ft_recursive_error(t_ls **ls, t_flags fg)
{
	ft_print_base((*ls)->path);
	ft_putstr("ls : ");
	perror((*ls)->d_name);
	if ((!fg.r && (*ls)->next) || (fg.r && (*ls)->prev))
		(*ls) = fg.r ? (*ls)->prev : (*ls)->next;
}

void	ft_recursive_no_error(t_ls **ls, t_flags fg, char *path, DIR *dir)
{
	t_ls *padd;
	t_ls *begin;

	ft_recup_recu_path((*ls)->path, path, (*ls)->d_name);
	ft_fill_recursive_stats(&begin, &(*ls), dir, &fg);
	padd = begin;
	ft_opti_recu0(fg, ls, padd, begin);
	closedir(dir);
	ft_recursive(&begin, fg, (*ls)->path);
}
