# -*- Makefile -*-	

CFILES = ft_atoi.c \
         ft_isalnum.c \
         ft_isdigit.c \
         ft_memchr.c \
         ft_memmove.c \
         ft_putendl_fd.c \
         ft_split.c \
         ft_striteri.c \
         ft_strlcpy.c \
         ft_strncmp.c \
         ft_strtrim.c \
         ft_toupper.c \
         ft_bzero.c \
         ft_isalpha.c \
         ft_isprint.c \
         ft_memcmp.c \
         ft_memset.c \
         ft_putnbr_fd.c \
         ft_strchr.c \
         ft_strjoin.c \
         ft_strlen.c \
         ft_strnstr.c \
         ft_substr.c \
         ft_calloc.c \
         ft_isascii.c \
         ft_itoa.c \
         ft_memcpy.c \
         ft_putchar_fd.c \
         ft_putstr_fd.c \
         ft_strdup.c \
         ft_strlcat.c \
         ft_strmapi.c \
         ft_strrchr.c \
         ft_tolower.c

OFILES = $(CFILES:.c=.o)

SRCBONUS = ft_lstadd_back.c \
           ft_lstadd_front.c \
           ft_lstclear.c \
           ft_lstdelone.c \
           ft_lstiter.c \
           ft_lstlast.c \
           ft_lstmap.c \
           ft_lstnew.c \
           ft_lstsize.c \

OBJBONUS = $(SRCBONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME)

$(NAME): $(OFILES)
	@ar rcs $(NAME) $(OFILES) 
	@echo "Libft compiled"

bonus: $(OFILES) $(OBJBONUS)
	@ar rcs $(NAME) $(OFILES) $(OBJBONUS)

%.o: %.c
	@cc $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME) $(OBJBONUS)

re: fclean $(NAME)

.PHONY: all clean fclean re bonus