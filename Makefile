# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 20:49:40 by crendeha          #+#    #+#              #
#    Updated: 2022/02/17 03:55:00 by crendeha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_STL		=		stl_containers
NAME_FT			=		ft_containers

OUTFILE_STL		=		"stl.txt"
OUTFILE_FT		=		"ft.txt"

SRC_PATH		=		./
SRC_STL 		= 		stl_tests.cpp
SRC_FT	 		= 		ft_tests.cpp

OBJ_STL 		=		$(patsubst %.cpp,%.o,$(addprefix $(SRC_PATH),$(SRC_STL)))
OBJ_FT	 		=		$(patsubst %.cpp,%.o,$(addprefix $(SRC_PATH),$(SRC_FT)))

D_FILES_STL 	=		$(patsubst %.cpp,%.d,$(addprefix $(SRC_PATH),$(SRC_STL)))
D_FILES_FT	 	=		$(patsubst %.cpp,%.d,$(addprefix $(SRC_PATH),$(SRC_FT)))

STD 			=		-std=c++98 -pedantic
CFLAGS 			= 		-Wall -Wextra -Werror

all 			: 		$(NAME_STL) $(NAME_FT)

$(NAME_STL)		:		$(OBJ_STL)
						c++ $(CFLAGS) $(STD) $(OBJ_STL) -o $(NAME_STL)
						@echo "STL tests compiled"

$(NAME_FT)		:		$(OBJ_FT)
						c++ $(CFLAGS) $(STD) $(OBJ_FT) -o $(NAME_FT)
						@echo "FT tests compiled"

%.o 			: 		%.cpp
						c++ $(CFLAGS) $(STD) -c $< -o $@ -MD

include $(wildcard $(D_FILES_STL))
include $(wildcard $(D_FILES_FT))

compare			:		
						./$(NAME_STL) > OUTFILE_STL && ./$(NAME_FT) > OUTFILE_FT && diff OUTFILE_STL OUTFILE_FT ; [ $$? -eq 1 ]
clean 			: 
						@rm -f $(OBJ_STL) $(OBJ_FT) $(D_FILES_STL) $(D_FILES_FT) OUTFILE_STL OUTFILE_FT "diff.txt"

fclean 			: 		clean
						@rm -f $(NAME_STL) $(NAME_FT)

re 				: 		fclean all

.PHONY			: 		all clean fclean re
