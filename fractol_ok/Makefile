# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecullier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 17:12:05 by ecullier          #+#    #+#              #
#    Updated: 2023/07/06 17:20:05 by ecullier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FRACTOL_SRCS = srcs/event.c \
		srcs/algofractal.c \
		srcs/fractol.c

HEADER = srcs/fractol.h

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -O2 -O3 -march=native -funroll-loops -ffast-math -fomit-frame-pointer -pthread
MLXFLAG = -Lminilibx-linux -lmlx -lX11 -lXext -lm -lbsd

GREEN = \033[1;32m

all: libft minilibx-linux $(NAME)
	@echo "$(GREEN)✅ Fract-ol compiled\n"
	@echo "$$ASCII_MANDATORY"
libft:
	@make -s -C libft
	@echo "$(GREEN)✅ Libft compiled\n"

minilibx-linux:
	@make -s -C minilibx-linux
	@echo "$(GREEN)✅ minilibx compiled\n"

$(NAME): $(FRACTOL_SRCS:%.c=%.o) $(HEADER)
	@$(CC) $(CFLAGS) $(FRACTOL_SRCS:%.c=%.o) -o $(NAME) -Llibft -lft $(MLXFLAG)
	
srcs/%.o: srcs/%.c ${HEADER}
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.c ${HEADERS}
	 @$(CC) $(CFLAGS) libft -c $< -o $@

clean:
	@rm -rf $(FRACTOL_SRCS:%.c=%.o)
	@make fclean -s -C libft
	@echo "$(GREEN)✅ Fract-ol cleaned\n"

fclean: clean
	@echo "$(GREEN)✅ Clean Fract-ol\n"
	@rm -f $(NAME)
	@make fclean -s -C libft

re: fclean all
	@echo "$(GREEN)✅ Fract-ol recompiled\n"

.PHONY: all libft clean fclean re minilibx-linux

# Colors
RED = \033[0;31m
NO_COLOR = \033[0m

# Ascii
info: ascii

define ASCII_MANDATORY

$(NO_COLOR)

$(RED) ███████ ██████   █████   ██████ ████████  ██████  ██      $(RED)
$(RED) ██      ██   ██ ██   ██ ██         ██    ██    ██ ██      $(RED)
$(RED) █████   ██████  ███████ ██         ██    ██    ██ ██      $(RED)
$(RED) ██      ██   ██ ██   ██ ██         ██    ██    ██ ██      $(RED)
$(RED) ██      ██   ██ ██   ██  ██████    ██     ██████  ███████ $(RED)

$(NO_COLOR)

endef
export ASCII_MANDATORY
