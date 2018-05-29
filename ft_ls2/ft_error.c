/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 14:28:42 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/29 18:35:17 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include "includes/libft.h"
#include <errno.h>
#include <stdio.h>

void	ft_display_l_file(char *file, t_flags fg, t_ls *ls, t_pad *pad)
{
	DIR		*dir;
	t_fill	fill;
//	t_ls *now;
//	t_ls *curr;
	t_ls *padd;

	(void)fg;
//	(void)now;
	pad = NULL;
	ls = (t_ls*)malloc(sizeof(t_ls));
	if (!ft_ocurences(file, '/') || (file[0] == '.' && file[1] == '/'))
	{
		dir = opendir(".");
		while ((fill.dirent = readdir(dir)) != NULL)
		{
			if (!ft_strcmp(fill.dirent->d_name, file))
			{
				ft_recup_full_path(ls->path, file, fill.dirent);
				ft_fill_struct(ls, &fill);
				padd = ls;
				pad = ft_padding(&padd);
			}
		}
	}
	ft_display_l(ls, pad);
	ft_putendl(ls->d_name);
	free(ls);
}

void	ft_errno_2(char **av, int start)
{
	DIR *dir;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 2)
		{
			ft_putstr("ls: ");
			ft_putstr(av[start]);
			ft_putstr(": No such file or directory\n");
		}
		if (dir)
			closedir(dir);
		start++;
	}
}

void	ft_errno_20(char **av, int start, t_flags fg)
{
	DIR *dir;
	t_ls ls;
	t_pad pad;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 20 && !fg.l)
			ft_putendl(av[start]);
		else if (errno == 20 && fg.l)
			ft_display_l_file(av[start], fg, &ls, &pad);
		if (dir)
			closedir(dir);
		start++;
	}
	ft_putchar('\n');
}

void	ft_errno_13(char **av, int start)
{
	DIR *dir;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 13)
		{
			ft_putstr(av[start]);
			ft_putstr(":\n");
			ft_putstr("ls: ");
			ft_putstr(av[start]);
			ft_putendl(" Permission denied");
		}
		if (dir)
			closedir(dir);
		start++;
	}
	ft_putchar('\n');
}
