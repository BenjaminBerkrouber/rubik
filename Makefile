NAME = rubik

CXX = g++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++20 -O3
# -pg
INCLUDES_DIR = include/


SRC = 		main.cpp \
			src/RubikController.cpp \
			verif.cpp \
			src/cube/CubeOperations.cpp \
			src/cube/Encoding.cpp \
			src/spin/SpinManager.cpp \
			src/engine/CubeStateHelper.cpp \
			src/parser/Parser.cpp \
			src/utils/utils.cpp \
			src/solver/Kociemba/KociembaSolver.cpp \
			src/solver/Kociemba/G1Solver.cpp \
			src/solver/Kociemba/G2Solver.cpp \
			src/solver/Pruning/TableIO.cpp \

INC = 		include/RubikController.hpp \
			include/utils/Constants.hpp \
			include/utils/utils.h \
			include/cube/Encoding.hpp \
			include/cube/CubeState.hpp \
			include/cube/CubeOperations.hpp \
			include/spin/Spin.hpp \
			include/spin/SpinManager.cpp \
			include/engine/CubeStateHelper.hpp \
			include/parser/Parser.hpp \
			include/BuildPruningTable/TableGenerator.hpp \
			include/solver/Pruning/TableIO.hpp \
			include/solver/Pruning/PruningTable.hpp \
			include/cube/OrientationEncoding.hpp \
			include/solver/Kociemba/KociembaSolver.hpp \
			include/solver/Kociemba/G1Solver.hpp \
			include/solver/Kociemba/G2Solver.hpp \


OBJ_SRC = bin/

OBJ_BIN = bin/obj/
OBJ = $(addprefix $(OBJ_BIN), $(SRC:.cpp=.o))

INCLUDES_DIR = include/
DEPS = $(INC)


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
	@mkdir -p './table'
	@$(CXX) $(CXXFLAGS) -I$(INCLUDES_DIR) -I$(INCLUDES_DIR)/Face_Type -c $< -o $@

end:
	@echo "$(GREEN)---------- Successfully compiled! ----------$(NC)"
	@echo " "

clean:
	@echo "$(RED)---------- Cleaning up files ----------$(NC)"
	@echo " $(OBJ_SRC)"
	@echo " "
	@rm -rf $(OBJ_SRC)

fclean: clean
	@echo "$(RED)---------- Full cleanup... ----------$(NC)"
	@echo " "
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re start end