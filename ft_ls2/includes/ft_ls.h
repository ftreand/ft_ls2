/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 14:41:59 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/29 15:49:08 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <string.h>
#define OK ft_putstr("OK");
typedef struct dirent	t_dir;
typedef struct stat		t_st;
typedef struct passwd	t_pw;
typedef struct group	t_gr;
typedef struct tm		t_tm;

typedef struct			s_fill
{
	t_dir				*dirent;
	t_st				stats;
	t_pw				*passwd;
	t_gr				*group;
}						t_fill;

typedef struct			s_ls
{
	char				path[4096];
	char				*mode;
	int					link;
	char				*pw_name;
	char				*gr_name;
	int					size;
	int					total;
	long				time;
	char				d_name[256];
	int					type;
	struct s_ls			*next;
	struct s_ls			*prev;
}						t_ls;

typedef struct			s_pad
{
	int					lk;
	size_t				pw;
	size_t				gr;
	int					size;
	size_t				name;
}						t_pad;

typedef struct			s_flags
{
	int					l;
	int					ur;
	int					a;
	int					r;
	int					t;
	char				er;
	int					total;
	int					start;
}						t_flags;

int						main(int ac, char **av);
int						ft_return_flag(char **av, int *i);
t_flags					ft_manage_flag(char **av);
char					ft_er_flag(char **av, int i, int j);
void					ft_error_flag(char er);
void					ft_sort_av(char **av, char *(dup)(const char *s),
		int start, int *i, t_flags fg);
void					ft_recup_stats(char **av, t_flags fg, int start);
int						ft_recup_start(char **av);
void					ft_display_wrong_dir(char **av, int start, t_flags fg);
t_pad					*ft_padding(t_ls **ls);
void					ft_fill_stats(DIR *dir, char *av,
		t_ls**begin, t_flags *fg);
int						ft_num_len(int i);
void					ft_sort_list(t_ls **begin, t_ls *ls, t_flags fg);
void					ft_display(t_ls *ls, t_flags *fg, t_pad *pad);
void					ft_pad(int i);
void					ft_display_time(long mtime);
void					ft_recursive(t_ls **ls, t_flags fg, char *path);
void					ft_fill_struct(t_ls *ls, t_fill *fill);
char					*ft_recup_mode(mode_t st_mode);
void					ft_recup_full_path(char *path, char *av
		, struct dirent *dirent);
void					ft_recup_recu_path(char *ret, char *path, char *name);
void					ft_free_list(t_ls *ls);
void					ft_putspace(char *av, size_t j);
void					ft_errno_2(char **av, int start);
void					ft_errno_20(char **av, int start, t_flags fg);
void					ft_errno_13(char **av, int start);
void					ft_display_l_file(char *file, t_flags fg, t_ls *ls, t_pad *pad);
void					ft_display_l(t_ls *ls, t_pad *pad);
void					ft_list_first(t_ls **ls, t_ls ***begin);
void					ft_list_next(t_ls *now, t_ls *ls);
#endif
