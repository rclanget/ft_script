#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/18 15:55:03 by rclanget          #+#    #+#              #
#    Updated: 2015/09/18 15:55:05 by rclanget         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC_PATH	=	./srcs/
SRC_NAME	=	main.c ft_openpty.c ft_shell.c script_master.c start_script.c \
				term.c
OBJ_PATH	=	./obj/
INC_PATH	=	./include/ ./libft/includes/ ./ft_printf/includes/
NAME		=	./ft_script
CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra

OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I,$(INC_PATH))
LIB_NAMES	=	./libft/libft.a ./ft_printf/libftprintf.a
LDFLAGS		=	$(LIB_NAMES)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft/
	make -C ./ft_printf/
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make clean -C ./libft
	make clean -C ./ft_printf/
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make fclean -C ./libft
	make fclean -C ./ft_printf/
	rm -fv $(NAME)

re: fclean all
	make re -C ./libft
	make re -C ./ft_printf/

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h