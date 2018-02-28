/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 14:41:59 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/02/28 20:49:04 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h> // stat / lstat
# include <unistd.h>
# include <dirent.h> // opendir / closedir / readdir
# include <pwd.h> //getpwuid
# include <grp.h> //getgrgid
# include <time.h> //time / ctime
# include <errno.h> // perror / 
# include <string.h>

# define CHECK(x, z) if ((x)) return (z)
# define SP ft_putchar(' ')
# define NL ft_putchar('\n')
# define OK ft_putstr("OK\n")

/*int flags pour la recup*/
# define low_l 1
# define up_r 2
# define low_a 4
# define low_r 8
# define low_t 16

typedef struct dirent	t_dir;
typedef struct stat		t_st;
typedef struct passwd	t_pw;
typedef struct group	t_gr;
typedef struct tm		t_tm;

typedef struct			s_fill
{
t_dir	*dirent;
t_st	stats;
t_pw	*passwd;
t_gr	*group;
}						t_fill;

typedef struct	s_ls
{
	char	*path;
	char	*mode;
	int		link;
	char	*pw_name;
	char	*gr_name;
	int		size;
	int		total;
	char	*time;
	char	d_name[256];
	struct s_ls *next;
	struct s_ls *prev;
}				t_ls;

typedef struct	s_pad
{
	int lk;
	size_t pw;
	size_t gr;
	int size;
	size_t name;
}				t_pad;

typedef struct	s_flags
{
	int l;
	int ur;
	int a;
	int r;
	int t;
	char er;
}				t_flags;

int		main(int ac, char **av);
int		ft_return_flag(char **av, int *i);
t_flags	ft_manage_flag(char **av);
char	ft_er_flag(char **av, int i, int j);
void	ft_error_flag(char er);
//int		ft_recup_info(char **av);
void	ft_sort_av(char **av, char *(dup)(const char *s), int start, int *i);
void	ft_recup_stats(char **av, t_flags fg, int start);
int		ft_recup_start(char **av);
void	ft_display_wrong_dir(char **av, int start);
t_pad	*ft_padding(t_ls **ls, size_t (len)(const char *s));
void	ft_fill_stats(DIR *dir, int start, char **av, t_ls **begin, t_flags fg);
int		ft_num_len(int i);
void	ft_sort_list(t_ls **begin, t_ls *ls, t_flags fg);

#endif
