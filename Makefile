NAME		= pipex
SRCS		= pipex.c
INCLUDE		= include/
BINDIR		= bin/
SRCDIR		= src/
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
RM			= rm -f
CC			= gcc
LIBFT		= ./lib/libft
LIBS		= $(LIBFT)/libft.a
CFLAGS		= -Wall -Wextra -Werror

all : libft $(NAME)

libft :
	$(MAKE) -C $(LIBFT)

$(NAME) : $(BINDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -I $(INCLUDE)

$(BINDIR)%.o : $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) -o $@ $^ -I $(INCLUDE)

$(BINDIR) :
	mkdir $(BINDIR)

clean : 
	$(RM) -r $(BINDIR)
	$(MAKE) -C $(LIBFT) fclean

fclean : clean
	$(RM) $(NAME)

re : fclean all