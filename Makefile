NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3 \

SRCS= srcs/main.c srcs/test_utils.c \
	srcs/execution/builtin/cd.c srcs/execution/builtin/env.c srcs/execution/builtin/pwd.c srcs/execution/builtin/export.c \
	srcs/execution/builtin/exit.c srcs/execution/builtin/unset.c srcs/execution/builtin/echo.c srcs/execution/builtin/exec_builtin.c \
	srcs/execution/utils/free.c srcs/execution/utils/exec.c srcs/execution/utils/checkers.c srcs/execution/utils/parse_line.c \
	srcs/execution/utils/getters.c srcs/execution/utils/setters.c srcs/execution/utils/split.c \
	srcs/execution/utils/utils.c srcs/execution/utils/pipe_exec.c srcs/execution/utils/signal.c srcs/execution/utils/heredoc.c \
	srcs/execution/utils/length.c srcs/execution/utils/str_utils.c

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
