/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_padding.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/21 15:03:58 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/23 14:27:07 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

int		ft_num_len(int lk)
{
	int i;

	i = 0;
	if (!lk)
		i++;
	while (lk)
	{
		lk /= 10;
		i++;
	}
	return (i);
}

t_pad	*ft_padding(t_ls **ls, size_t (len)(const char *s))
{
	t_pad *pad;

	pad = NULL;
	if (!pad)
	{
		if (!(pad = (t_pad*)malloc(sizeof(t_pad))))
			return (NULL);
		pad->lk = ft_num_len((*ls)->link);
		pad->pw = ft_strlen((*ls)->pw_name);
		pad->gr = ft_strlen((*ls)->gr_name);
		pad->size = ft_num_len((*ls)->size);
		pad->name = ft_strlen((*ls)->d_name);
		*ls = (*ls)->next;
	}
	while (*ls != NULL)
	{
		pad->lk = ft_num_len((*ls)->link) > pad->lk ? ft_num_len((*ls)->link)
			: pad->lk;
		pad->pw = (len)((*ls)->pw_name) > pad->pw ? (len)((*ls)->pw_name)
			: pad->pw;
		pad->gr = (len)((*ls)->gr_name) > pad->gr ? (len)((*ls)->gr_name)
			: pad->gr;
		pad->size = ft_num_len((*ls)->size) > pad->size ? ft_num_len((*ls)->size)
			: pad->size;
		pad->name = (len)((*ls)->d_name) > pad->name ? (len)((*ls)->d_name) : pad->name;
		*ls = (*ls)->next;
	}
	return (pad);
}