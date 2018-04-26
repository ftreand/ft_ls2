/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/27 20:22:25 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/04/26 16:34:03 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_free_list(t_ls *ls)
{
	t_ls *tmp;

	while (ls)
	{
		tmp = ls->next;
//		printf("ls d_ddname = %s\n", ls->d_name);
		free(ls->mode);
		free(ls->pw_name);
		free(ls->gr_name);
//		printf("ls path = %s\n", ls->path);
		free(ls->path);
//		free(ls);
		ls = tmp;
//		free(tmp);
//		free(ls->prev);
	}
}
