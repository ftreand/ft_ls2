/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 14:28:42 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 13:49:15 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include "includes/libft.h"
#include <errno.h>
#include <stdio.h>

void	ft_recup_name(char *file, char **name)
{
	int i;

	i = ft_strlen(file);
	while (i && file[i] != '/')
		i--;
//	printf("file len = %zu\n", ft_strlen(file));
//	printf("i = %i\n", i);
	ft_ocurences(file, '/') ? i++ : i;
//	while (file[i])
//		name[j++] = file[i++];
	ft_strcpy((*name), file + i);
//	name[j] = '\0';
}

void	ft_recup_file_path(char *file, char **name)
{
	size_t i;

	i = ft_strlen(file);
	while (i && file[i] != '/')
		i--;
	i++;
	ft_strncpy((*name), file, i);

}

void	ft_display_l_file(char *file, t_flags fg, t_ls *ls, t_pad *pad)
{
	DIR		*dir;
	t_fill	fill;
//	t_ls *padd;
	char *name;

	(void)fg;
//	pad = NULL;
//	printf("file = %s\n", file);
	ls = (t_ls*)malloc(sizeof(t_ls));
	name = (char*)malloc(sizeof(char*) * (ft_strlen(file) + 1));
	if (!ft_ocurences(file, '/') || (file[0] == '.' && file[1] == '/'))
	{
		dir = opendir(".");
		ft_recup_name(file, &name);
//		printf("name = %s\n", name);
		if (dir)
		{
			while ((fill.dirent = readdir(dir)) != NULL)
			{
				if (!ft_strcmp(fill.dirent->d_name, name))
				{
					ft_recup_full_path(ls->path, name, fill.dirent);
//					printf("ls path =%s\n", ls->path);
					ft_fill_struct(ls, &fill);
//					printf("ls->pw_name = %s\n", ls->d_name);
					break ;
				}
			}
			if (dir)
				closedir(dir);
		}
	}
	else if ((file[0] != '.' && ft_ocurences(file, '/')) || (file[1] == '.' &&
			file[0] == '.' && ft_ocurences(file, '/')))
	{
		ft_recup_file_path(file, &name);
		dir = opendir(name);
		ft_recup_name(file, &name);
		while ((fill.dirent = readdir(dir)) != NULL)
		{
			if (!ft_strcmp(fill.dirent->d_name, name))
			{
				ft_strcpy(ls->path, file);
				ft_fill_struct(ls, &fill);
			}
		}
		closedir(dir);
	}
	ft_padding_1(pad);
	ft_display_l(ls, pad);
	ft_ocurences(file, '/') ? ft_putendl(file) : ft_putendl(ls->d_name);
	ft_strdel(&name);
	ft_free_list(&(*ls));
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
	int i;

	i = 0;
	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		errno == 0 ? i = 1 : i;
		if (errno == 20 && !fg.l)
			ft_putendl(av[start]);
		else if (errno == 20 && fg.l)
			ft_display_l_file(av[start], fg, &ls, &pad);
		if (dir)
			closedir(dir);
		start++;
	}
	if (!i)
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
			ft_putchar('\n');
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
}
