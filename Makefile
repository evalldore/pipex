NAME		= pipex
SRCS		= pipex.c
BINDIR		= bin/
SRCDIR		= src/
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
RM			= rm -f
CC			= gcc
LIBFT		= ./lib/libft
LIBS		= $(LIBFT)/libft.a
CFLAGS		= -Wall -Wextra -Werror
HEADERS		= -I include -I $(LIBFT)/include

all : libft $(NAME)

libft :
	$(MAKE) -C $(LIBFT)

$(NAME) : $(BINDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(HEADERS)

$(BINDIR)%.o : $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) -o $@ $^ $(HEADERS)

$(BINDIR) :
	mkdir $(BINDIR)

clean : 
	$(RM) -r $(BINDIR)
	$(MAKE) -C $(LIBFT) fclean
	$(RM) in
	$(RM) out

fclean : clean
	$(RM) $(NAME)

re : fclean all