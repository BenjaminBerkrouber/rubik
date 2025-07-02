NAME = rubik
TEST_NAME = test

CC = c++
CFLAGS = -g -Wall -Wextra -Werror -std=c++17 -O2
# -pg

SRC = 		main.cpp \
			src/Cube.cpp \
			src/SpinLib.cpp

INC = 		include/Cube.hpp \
			include/SpinLib.hpp \


OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
OBJ_DEBOG = $(addprefix $(OBJ_DIR), $(SRCTEST:.cpp=.o))
INCLUDES_DIR = include/
DEPS = $(INC)

GTEST_LIB = -lgtest -lgtest_main -pthread


RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

all: start $(NAME) end

debog: $(OBJ_DEBOG)
	@echo "$(GREEN)---------- Starting the compilation of $(NAME) ----------$(NC)"
	@$(CC) $(CFLAGS) $(OBJ_DEBOG) -o $(TEST_NAME) $(GTEST_LIB)
	@echo " $(NAME)"
	@echo " "

start:
	@echo " "
	@echo "$(GREEN)---------- Starting the compilation of $(NAME) ----------$(NC)"

$(NAME): $(OBJ)
	@echo "$(BLUE)---------- Creating the executable ----------$(NC)"
	@echo " $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: %.cpp
	@echo " $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -I$(INCLUDES_DIR)/Face_Type -c $< -o $@

end:
	@echo "$(GREEN)---------- Successfully compiled! ----------$(NC)"
	@echo " "

clean:
	@echo "$(RED)---------- Cleaning up files ----------$(NC)"
	@echo " $(OBJ_DIR)"
	@echo " "
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)---------- Full cleanup... ----------$(NC)"
	@echo " "
	@rm -rf $(NAME) a.out

re: fclean all

.PHONY: all clean fclean re start end