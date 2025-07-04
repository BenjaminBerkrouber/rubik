NAME = rubik

CXX = g++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++20 -O3
# -pg
GTEST_LIB = -lgtest -lgtest_main -pthread


SRC = 		main.cpp \
			src/Cube.cpp \
			src/SpinLib.cpp \
			src/CubePrinter.cpp \
			src/algo/Kociemba/Pruning/PruningTableG1.cpp \

INC = 		include/Cube.hpp \
			include/SpinLib.hpp \
			include/CubePrinter.hpp \
			include/algo/Kociemba/Pruning/PruningTableG1.hpp \

TEST_BIN = bin/tests/tests
OBJ_BIN = bin/obj/
OBJ = $(addprefix $(OBJ_BIN), $(SRC:.cpp=.o))
OBJ_DEBOG = $(addprefix $(OBJ_BIN), $(SRCTEST:.cpp=.o))

INCLUDES_DIR = include/
DEPS = $(INC)

TESTS = tests/SpinLib_test.cpp \
		tests/Cube_test.cpp \
		tests/spins/spin_*_test.cpp \


RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

all: start $(NAME) end

start:
	@echo " "
	@echo "$(GREEN)---------- Starting the compilation of $(NAME) ----------$(NC)"

$(NAME): $(OBJ)
	@echo "$(BLUE)---------- Creating the executable ----------$(NC)"
	@echo " $(NAME)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJ_BIN)%.o: %.cpp
	@echo " $<"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -I$(INCLUDES_DIR) -I$(INCLUDES_DIR)/Face_Type -c $< -o $@

end:
	@echo "$(GREEN)---------- Successfully compiled! ----------$(NC)"
	@echo " "

SRC_NO_MAIN = $(filter-out main.cpp, $(SRC))

test: $(TESTS) $(SRC)
	@echo "$(BLUE)---------- Building and running tests ----------$(NC)"
	$(CXX) $(CXXFLAGS) -o $(TEST_BIN) $(TESTS) $(SRC_NO_MAIN) $(LDFLAGS) $(GTEST_LIB)
	./$(TEST_BIN)

clean:
	@echo "$(RED)---------- Cleaning up files ----------$(NC)"
	@echo " $(OBJ_BIN)"
	@echo " "
	@rm -rf $(OBJ_BIN)

fclean: clean
	@echo "$(RED)---------- Full cleanup... ----------$(NC)"
	@echo " "
	@rm -rf $(NAME) a.out

re: fclean all

.PHONY: all clean fclean re start end