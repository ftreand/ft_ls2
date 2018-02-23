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

INCLUDES_PATH = includes

INCLUDES = -I $(LIBFT_PATH) -I $(INCLUDES_PATH)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@ echo "\033[1mCompilation de ft_ls \033[34m$<\033[37m en \033[31m$@\033[0m ✅ "
	@$(CC) $(CC_FLAGS) -o $@ $^ $(LIBFT_INC)

$(LIBFT):
	@make -C $(LIBFT_PATH)

%.o: %.c ./$(INCLUDES_PATH)/$(NAME).h
	@ echo "\033[1mCompilation de \033[33m$<\033[37m en \033[32m$@\033[0m ✅ "
	@ $(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all
