.PHONY: all re clean fclean

NAME = ft_ls

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_INC = -L $(LIBFT_PATH) -lft

CC = gcc

COLOR = echo

CC_FLAGS = -Wall -Werror -Wextra

SRC =		main.c\
			ft_recup_info.c\
			ft_recup_stats.c\
			ft_padding.c \
			ft_sort_list.c \
			ft_display.c \
			ft_recursive.c \
			ft_fill_struct.c \
			ft_free_list.c \
			ft_error.c \
			ft_opti.c \
			ft_opti2.c \
			ft_opti_recu.c \

INCLUDES_PATH = includes

INCLUDES = -I $(LIBFT_PATH) -I $(INCLUDES_PATH)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@ printf "\033[1mCompilation du projet \033[34m$@\033[0m \033[1men \033[31m$@\033[0m ✅\n"
	@$(CC) $(CC_FLAGS) -o $@ $^ $(LIBFT_INC)
$(LIBFT):
	@make -C $(LIBFT_PATH)

%.o: %.c ./$(INCLUDES_PATH)/$(NAME).h
	@ printf "\033[1mCompilation de \033[36m%-20s\033[37m\ten \033[32m%-20s\033[0m ✅\n" $< $@
	@ $(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all
