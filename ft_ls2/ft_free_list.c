/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/27 20:22:25 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/27 21:41:10 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_free_list(t_ls *ls)
{
	while (ls)
	{
//		printf("ls d_ddname = %s\n", ls->d_name);
		free(ls->mode);
		free(ls->pw_name);
		free(ls->gr_name);
//		free(ls);
		ls = ls->next;
		free(ls->path);
//		free(tmp);
//		printf("ls path = %s\n", ls->path);
//		free(ls->prev);
	}
}
