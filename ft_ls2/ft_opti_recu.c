/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_opti_recu.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/24 16:58:34 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 19:29:10 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <errno.h>
#include <stdio.h>

void	ft_opti_recu0(t_flags fg, t_ls **ls, t_ls *padd, t_ls *begin)
{
	t_pad *pad;

	if (!fg.a)
	{
		while (padd->d_name[0] == '.' && padd->next)
			padd = padd->next;
		padd->d_name[0] == '.' ? fg.i = 0 : fg.i;
	}
	pad = ft_padding(&padd);
	ft_print_base((*ls)->path);
	if (fg.i)
		ft_display(begin, &fg, pad);
}

void	ft_manage_reverse(t_ls **ls)
{
	while ((*ls)->next)
		(*ls) = (*ls)->next;
}

void	ft_manage_no_a(t_flags fg, t_ls **ls)
{
	printf("name a manage = %s\n", (*ls)->d_name);
	while (ls)
	{
		if (!fg.a && (*ls)->d_name[0] == '.')
			(*ls) = fg.r ? (*ls)->prev : (*ls)->next;
		else
			break ;
	}
	printf("name a manage 2= %s\n", (*ls)->d_name);
}

void	ft_recursive(t_ls **ls, t_flags fg, char *path)
{
	t_ls	*tmp;
	(void)path;

	tmp = (*ls);
	printf("new dname = %s\n", (*ls)->d_name);
	while (ls)
	{
		ft_manage_no_a(fg, &(*ls));
		printf("name = %s\n", (*ls)->d_name);
		fg.i = 1;
		if ((*ls)->type == 4 && ((*ls)->d_name[0] != '.' || (((*ls)->d_name[1] && (*ls)->d_name[1] != '.'))))
		{

		}
	}
}
