# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achernys <achernys@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/27 17:30:25 by achernys          #+#    #+#              #
#    Updated: 2018/02/28 17:13:36 by achernys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_bzero.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strdup.c\
        ft_strlen.c ft_strncpy.c ft_strcat.c ft_strcpy.c ft_strncpy.c ft_strlcat.c ft_strncat.c ft_strchr.c ft_strrchr.c\
        ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
        ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_pow.c ft_memccpy.c ft_memalloc.c ft_memdel.c ft_strnew.c\
        ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c\
        ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_strtrimc.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c\
        ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c\
        ft_lstiter.c ft_lstmap.c ft_lstpushback.c

OFILES = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $@ $^
	ranlib $@

.PHONY: clean

clean:
	rm -f $(OFILES)
	rm -f *~

fclean: clean
	rm -f $(NAME)

re: fclean all
