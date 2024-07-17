NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3 \

SRCS= srcs/main.c \
	srcs/builtin/cd.c srcs/builtin/env.c srcs/builtin/pwd.c srcs/builtin/export.c srcs/builtin/exit.c srcs/builtin/unset.c srcs/builtin/echo.c \
	srcs/utils/free.c srcs/utils/exec.c srcs/utils/checkers.c srcs/utils/parse_line.c srcs/utils/getters.c srcs/utils/setters.c srcs/utils/split.c \
	srcs/utils/utils.c srcs/utils/redirect.c

OBJS=$(SRCS:.c=.o)
LIBFT= Libft/libft.a
all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C Libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	clear

test : re
	./minishell
clean :
	@$(MAKE) -C Libft clean
	@rm -f $(OBJS)
	@clear

fclean : clean
	@$(MAKE) -C Libft fclean
	@rm -f $(NAME)
	@clear

re : fclean all

.PHONY: all clean fclean re
