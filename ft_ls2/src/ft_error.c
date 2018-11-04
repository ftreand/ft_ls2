/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_error.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 14:28:42 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 14:50:36 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <errno.h>
#include <stdio.h>

void	ft_recup_name(char *file, char **name)
{
	int i;

	i = ft_strlen(file);
	while (i && file[i] != '/')
		i--;
	ft_ocurences(file, '/') ? i++ : i;
	ft_strcpy((*name), file + i);
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

void	ft_display_l_file(char *file, t_ls *ls, t_pad *pad)
{
	char	*name;

	ls = (t_ls*)malloc(sizeof(t_ls));
	name = (char*)malloc(sizeof(char*) * (ft_strlen(file) + 1));
	if (!ft_ocurences(file, '/') || (file[0] == '.' && file[1] == '/'))
		ft_print_file0(file, &(*name), ls);
	else if ((file[0] != '.' && ft_ocurences(file, '/')) || (file[1] == '.' &&
			file[0] == '.' && ft_ocurences(file, '/')))
		ft_print_file1(file, &(*name), ls);
	ft_padding_1(pad);
	ft_display_l(ls, pad);
	ft_ocurences(file, '/') ? ft_putendl(file) : ft_putendl(ls->d_name);
	ft_strdel(&name);
	ft_free_list(&(*ls));
}

void	ft_errno_2(char **av, int start, int *i)
{
	DIR *dir;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		*i = errno == 2 ? *i += 1 : *i;
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

void	ft_errno_20(char **av, int start, t_flags fg, int *i)
{
	DIR		*dir;
	t_ls	ls;
	t_pad	pad;

	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		*i = errno == 20 ? *i += 1 : *i;
		if (errno == 20 && !fg.l)
			ft_putendl(av[start]);
		else if (errno == 20 && fg.l)
			ft_display_l_file(av[start], &ls, &pad);
		if (dir)
			closedir(dir);
		start++;
	}
	if (*i < fg.nb_arg && *i)
		ft_putchar('\n');
}
