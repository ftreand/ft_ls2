/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/27 20:22:25 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:50:20 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

void	ft_free_list(t_ls *ls)
{
	t_ls *tmp;

	while (ls)
	{
		tmp = ls->next;
		free(ls->mode);
		free(ls->pw_name);
		free(ls->gr_name);
		free(ls->path);
		ls = tmp;
	}
}
