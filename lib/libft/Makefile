SRCS	= ft_isalpha.c \
		ft_isdigit.c ft_isascii.c ft_isalnum.c ft_isalnum.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_strdup.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_printf.c \
		ft_putaddr_fd.c ft_putuint_fd.c ft_revbits.c ft_puthex_fd.c \
		ft_get_next_line.c
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
NAME		= libft.a
INCDIR		= include/
BINDIR		= bin/
SRCDIR		= src/
LIBC		= ar rcs
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
CC			= gcc

all : $(NAME)

$(BINDIR)%.o : $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) -o $@ $^ -I $(INCDIR)

$(NAME) : $(BINDIR) $(OBJS)
	$(LIBC) $@ $(OBJS)

$(BINDIR) :
	mkdir $(BINDIR)

clean :
	$(RM) -r $(BINDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all