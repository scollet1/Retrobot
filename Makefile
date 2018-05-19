# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/21 22:34:31 by jchow             #+#    #+#              #
#    Updated: 2017/06/21 22:34:32 by jchow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		ft_retro
UNITNAME = 	UNIT_TEST

UNITSRC = 	UNIT_main
UNITHDR = 	NN \
		Layer \
		Neuron \

SRC = 		Bullet \
			Character \
			Enemy \
			Player \
			GameEntity \
			main \
			Game \

HDR =		Bullet \
			Character \
			Enemy \
			Player \
			GameEntity \
			Header \
			Game \
			NN \
			Neuron \
			Layer

UNIT_SRC_DIR =		src/
SRC_DIR =		src/

UNIT_SRC_C =		$(addsuffix .cpp, $UNITSRC))
SRC_C =			$(addsuffix .cpp, $(SRC))

UNIT_SRC_FILES =	$(addprefix $(UNIT_SRC_DIR), $(UNIT_SRC_C))
SRC_FILES =		$(addprefix $(SRC_DIR), $(SRC_C))

UNIT_OBJ_DIR =		obj/
OBJ_DIR =		obj/

UNIT_OBJ_O =		$(addsuffix .o, $(UNITSRC))
OBJ_O =			$(addsuffix .o, $(SRC))

UNIT_OBJ_FILES =	$(addprefix $(UNIT_OBJ_DIR), $(UNIT_OBJ_O))
OBJ_FILES =		$(addprefix $(OBJ_DIR), $(OBJ_O))

UNIT_HDR_DIR =		inc/
HDR_DIR =		inc/

UNIT_HDR_H =		$(addsuffic .hpp, $(UNITHDR))
HDR_H =			$(addsuffix .hpp, $(HDR))

UNIT_HDR_FILES =	$(addprefix $(UNIT_HDR_DIR), $(UNIT_HDR_H))
HDR_FILES =		$(addprefix $(HDR_DIR), $(HDR_H))

CC =			g++
C_FLAGS =		-Wall -Wextra -Werror

RED =				\033[31m
GREEN =				\033[32m
BLUE =				\033[34m
YELLOW =			\033[33m
MAGENTA =			\033[35m
GREY =				\033[37m
GREEN_LIGHT =		\033[92m
YELLOW_LIGHT =		\033[93m
YELLOW_BOLD =		\033[1;33m
YELLOW_LIGHT_BOLD =	\033[1;93m
MAGENTA_LIGHT =		\033[95m
BLINK =				\033[5m
GREEN_LIGHT_BLINK =	\033[5;92m
END_COLOUR =		\033[0m

.SILENT:

unit_test: $(UNITNAME)

$(UNITNAME): $(UNIT_OBJ_FILES)
	@echo "$(YELLOW_LIGHT)$(UNITNAME): $(YELLOW)Compiling $(UNITNAME)...$(END_COLOUR)"
	@$(CC) $^ -o $@
	@echo "$(YELLOW_LIGHT)$(UNITNAME): $(GREE)Successfully compiled $(UNITNAME)!$(END_COLOUR)"

$(UNIT_OBJ_DIR)%.o: $(UNIT_SRC_DIR)%.cpp
	@mkdir -p obj
	@$(CC) -I $(UNIT_HDR_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Compiling $(NAME)...$(END_COLOUR)"
	@$(CC) $^ -o $@ -lncurses
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully compiled $(NAME)!$(END_COLOUR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p obj
	@$(CC) -I $(HDR_DIR) -c $< -o $@

$(LIBFT_FILES): force
	@make -C $(LIBFT_DIR)

force:
	@true

clean:
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Cleaning objects...$(END_COLOUR)"
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully cleaned all objects!$(END_COLOUR)"

fclean: clean
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Cleaning executable...$(END_COLOUR)"
	@/bin/rm -f $(NAME)
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully cleaned everything!$(END_COLOUR)"

re:	fclean all

.PHONY: all force clean fclean re
