##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

D_SRC	=	src/
D_INC	=	include/

SRC	=		\
			$(D_SRC)/main.cpp \
			$(D_SRC)/AppWindow.cpp \

OBJ	=		$(SRC:.cpp=.o)

NAME	=	exec

CXXFLAGS=	-W -Wall -Wextra -I$(D_INC)

LDFLAGS	=	-l GL -l GLEW -l glfw

RM = 		rm -f


all:		$(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

re: fclean all

.PHONY: all options clean fclean re
