/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_info.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 19:04:02 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/03 20:19:32 by ftreand     ###    #+. /#+    ###.fr     */
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
	size_t	i;
	DIR		*dir;

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

void	ft_display_wrong_dir(char **av, int start, t_flags fg)
{
	ft_errno_2(av, start);
	ft_errno_20(av, start, fg);
	ft_errno_13(av, start);
}

void	ft_sort_av(char **av, char *(dup)(const char *s), int start, int *i, t_flags fg)
{
	int		j;
	char	*tmp;

	while (start < ft_tablen(av))
	{
		j = start;
		while (av[j])
		{
			if (((ft_strcmp(av[start], av[j])) < 0) && fg.r)
			{
				tmp = (dup)(av[start]);
				av[start] = (dup)(av[j]);
				av[j] = (dup)(tmp);
			}
			else if ((ft_strcmp(av[start], av[j]) > 0) && !fg.r)
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
		if (!av[i][1])
			break ;
		if (av[i][1] == '-')
		{
			if (av[i][2])
			{
				ft_error_flag(av[i][1]);
			}
			i++;
			break ;
		}
		i++;
	}
	return (i);
}
