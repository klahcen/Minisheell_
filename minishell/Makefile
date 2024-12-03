NAME = minishell

CC = cc


CFLAGS = -Wall -Wextra -Werror 


SRCS = main.c ft_split.c ft_store.c ft_utils.c ft_quotes.c\
	  ft_functions.c ft_exc.c ft_builtins.c ft_syntax_error.c\
	  ft_exc1.c ft_exc2.c ft_exction.c ft_next_builtins.c\
	  ft_next2_builtins.c ft_next1_builtins.c ft_error_exc.c\
	  ft_utils1.c ft_expand.c ft_set_args.c ft_minishell.c\
	  ft_parsing.c ft_utils2.c  ft_utils3.c ft_split2.c\
	  ft_lst_next.c ft_redirection.c ft_path.c ft_help_expand.c\
	  ft_expand1.c ft_file.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC)  $(CFLAGS)  $(SRCS) -o $(NAME) -lreadline -L /Users/lkazaz/readline/lib

clean:
	rm -rf $(OBJS)
	
fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re