/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_info.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 19:04:02 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/21 21:30:17 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>
#include <errno.h>

void	ft_putspace(char *av, size_t j)
{
	size_t i;

	i = ft_strlen(av);
	if (i < j)
	{
		while (i++ < j)
			ft_putchar(' ');
	}
}

int		ft_recup_len_max(char **av, int start)
{
	size_t i;
	DIR *dir;

	i = 0;
	while (start++ < ft_tablen(av))
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 20)
			i = ft_strlen(av[start]) > i ? (ft_strlen(av[start]) + 1) : i;
	}
	return (i);
}

void	ft_display_wrong_dir(char **av, int start)
{
	int i;
	size_t j;
	DIR *dir;

	i = start;
	j = ft_recup_len_max(av, start);
	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 2)
		{
			ft_putstr("ls: ");
			perror(av[start]);
		}
		if (dir)
			closedir(dir);
		start++;
	}
	start = i;
	while (av[start])
	{
		errno = 0;
		dir = opendir(av[start]);
		if (errno == 20)
		{
			ft_putstr(av[start]);
			ft_putspace(av[start], j);
		}
		if (dir)
			closedir(dir);
		start++;
	}
	ft_putchar('\n');
}

void	ft_sort_av(char **av, char *(dup)(const char *s), int start, int *i)
{
	int j;
	char *tmp;

	printf("tablen = %d\n", ft_tablen(av));
	while (start < ft_tablen(av))
	{
		j = start;
		while (av[j])
		{
			if (((ft_strcmp(av[start], av[j])) > 0))
			{
				tmp = (dup)(av[start]);
				av[start] = (dup)(av[j]);
				av[j] = (dup)(tmp);
			}
			j++;
		}
		start++;
		*i += 1;
	}
}

int		ft_recup_start(char **av)
{
	int i;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (av[i][1] == '-')
		{
			if (av[i][2])
			{
				ft_error_flag(av[i][1]);
				ft_return_flag(av, &i);
			}
			i++;
			break ;
		}
		i++;
	}
	printf("i = %d\n", i);
	return (i);
}

/*int		ft_recup_info(char **av)
{
	int	i = 0;
	int start;
	int nb_arg = 0;
//	t_dir	*dirent;
//	DIR *dir;
//	DIR *dir2;
	//	while (av[i])
	//	{
	//		printf("before sort = %s\n", av[i]);
	//		i++;
	//	}
	start = ft_recup_start(av);
	//	while (av[++i])
	//		printf("av = %s\n", av[i]);
	ft_sort_av(av, ft_strdup, start, &nb_arg);
	while (av[i])
	{
		printf("i = %d\n", i);
		printf("av = %s\n", av[i]);
		i++;
	}
	printf("start 1 = %d\n", start);
	printf("nb_arg = %d\n", nb_arg);
	ft_display_wrong_dir(av, start);
	return (0);
}*/
