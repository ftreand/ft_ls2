/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 18:44:28 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/24 16:37:29 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#include <stdio.h>

void	ft_error_flag(char er)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(er);
	ft_putchar('\n');
	ft_putendl("usage: ls [-lRart] [file ...]");
}

char	ft_er_flag(char **av, int i, int j)
{
	char	c;

	c = av[i][j] != 'l' && av[i][j] != 'R' && av[i][j] != 'a' && av[i][j] !=
		'r' && av[i][j] != 't' && av[i][j] != '-' ? av[i][j] : '\0';
	c = (av[i][j] == '-' && av[i][j + 1] != '\0') ? av[i][j] : c;
	return (c);
}

void	ft_recup_char_flag(char **av, t_flags *fg, int i, int j)
{
	fg->l = av[i][j] == 'l' && fg->l == 0 ? 1 : fg->l;
	fg->ur = av[i][j] == 'R' && fg->ur == 0 ? 1 : fg->ur;
	fg->a = av[i][j] == 'a' && fg->a == 0 ? 1 : fg->a;
	fg->r = av[i][j] == 'r' && fg->r == 0 ? 1 : fg->r;
	fg->t = av[i][j] == 't' && fg->t == 0 ? 1 : fg->t;
}

void	ft_manage_flag(char **av, t_flags *fg)
{
	int		i;
	int		j;

	i = 0;
	while (av[++i] && av[i][0] == '-')
	{
		j = 0;
		if (ft_strcmp(av[i], "--") == 0)
			break ;
		while (av[i][++j])
		{
			ft_recup_char_flag(av, fg, i, j);
			fg->er = ft_er_flag(av, i, j);
			if (fg->er != '\0')
			{
				ft_error_flag(fg->er);
				break ;
			}
		}
		if (fg->er)
			break ;
	}
}

int		main(int ac, char **av)
{
	t_flags	fg;

	if (ac)
	{
		fg.l = 0;
		fg.ur = 0;
		fg.a = 0;
		fg.r = 0;
		fg.t = 0;
		fg.i = 0;
		ft_manage_flag(av, &fg);
		if (fg.er)
			return (1);
		fg.start = ft_recup_start(av);
		ft_recup_stats(av, fg);
	}
	return (0);
}
