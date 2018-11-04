/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:36:40 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:50:09 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

void	ft_print_base(char *s)
{
	ft_putchar('\n');
	ft_putstr(s);
	ft_putendl(":");
}

void	ft_errno_13(char **av, t_flags fg)
{
	DIR *dir;

	while (av[fg.start])
	{
		errno = 0;
		dir = opendir(av[fg.start]);
		if (errno == 13)
		{
			if (fg.i)
				ft_putchar('\n');
			if (fg.nb_arg != 1)
			{
				ft_putstr(av[fg.start]);
				ft_putstr(":\n");
			}
			ft_putstr("ls: ");
			ft_putstr(av[fg.start]);
			ft_putendl(": Permission denied");
			fg.i++;
		}
		if (dir)
			closedir(dir);
		fg.start++;
	}
}

void	ft_print_file0(char *file, char *name, t_ls *ls)
{
	DIR		*dir;
	t_fill	fill;

	dir = opendir(".");
	ft_recup_name(file, &name);
	if (dir)
	{
		while ((fill.dirent = readdir(dir)) != NULL)
			if (!ft_strcmp(fill.dirent->d_name, name))
			{
				ft_recup_full_path(ls->path, name, fill.dirent);
				ft_fill_struct(ls, &fill);
				break ;
			}
		closedir(dir);
	}
}

void	ft_print_file1(char *file, char *name, t_ls *ls)
{
	DIR		*dir;
	t_fill	fill;

	ft_recup_file_path(file, &name);
	dir = opendir(name);
	ft_recup_name(file, &name);
	while ((fill.dirent = readdir(dir)) != NULL)
		if (!ft_strcmp(fill.dirent->d_name, name))
		{
			ft_strcpy(ls->path, file);
			ft_fill_struct(ls, &fill);
		}
	closedir(dir);
}
