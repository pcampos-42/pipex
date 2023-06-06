# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 14:40:49 by pcampos-          #+#    #+#              #
#    Updated: 2022/04/29 12:36:07 by pcampos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################ PROGRAM ################

NAME	=		pipex

################ TERMINAL ###############

RMV		=		rm -f
MKD		=		mkdir
PRT		=		printf
MKE		=		make
CPY		=		cp

################# COLORS ################

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################# DIRS ##################

_SRC	=		src/
_OBJ	=		obj/
_LIB	=		src/libft
_BIN	=

############### COMPILER ################

CC		=		gcc
CF		=		-Wall -Werror -Wextra

################ FILES ##################

SRCS	=		$(_SRC)pipex_main.c $(_SRC)check_args.c $(_SRC)error_handler.c $(_SRC)get_cmd.c
OBJS	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))
LIBS	=		-lft

################ RULES ##################

all:	$(NAME)

$(_OBJ)%.o: $(_SRC)%.c $(_OBJ)
	$(CC) $(CF) -c $< -o $@

$(NAME): $(_LIB)libft.a $(OBJS)
	$(CC) $(CF) $(LIBS) $(OBJS) -o $(NAME) -L $(_LIB)

################ DEPS ###################

$(_LIB)libft.a: $(shell make -C src/libft -q libft.a || echo force)
	$(MKE) libft.a -C src/libft

############## STRUCTURE ################

$(_OBJ):
	$(MKD) $(_OBJ)

$(_LIB):
	$(MKD) $(_LIB)

$(_SRC):
	$(MKD) $(_SRC)

$(_BIN):
	$(MKD) $(_BIN)

################### CLEAN ###############

clean:
	$(RMV) -r $(_OBJ)

fclean: clean
	$(RMV) -r $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re force

