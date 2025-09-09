# ====================================================================================
# Makefile for Rubik's Cube Solver
# ====================================================================================

# ====================================================================================
# Settings and Variables
# ====================================================================================

NAME        := rubik

BNAME		:= rubik_bonus

CXX         := g++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++20 -O3 -g
INCLUDES    := -Iinclude -Iinclude/_bonus -Iinclude/_bonus/libs
SRC_DIR     := src
BSRC_DIR	:= src/_bonus
BIN_DIR     := bin
OBJ_DIR     := $(BIN_DIR)/obj
TABLE_DIR   := table
LIBS_DIR	:= include/_bonus/libs
GLIBFLAGS   := $(LIBS_DIR)/glad/libglad.a $(LIBS_DIR)/GLFW/libglfw3.a $(LIBS_DIR)/gltf/libtinygltf.a $(LIBS_DIR)/imgui/libimgui.a -ldl -lGL -lX11 -lpthread -lXrandr -lXi
# ====================================================================================
# Source Files
# ====================================================================================

SRC_FILES := \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/RubikController.cpp \
	$(SRC_DIR)/cube/CubeOperations.cpp \
	$(SRC_DIR)/cube/Encoding.cpp \
	$(SRC_DIR)/spin/SpinManager.cpp \
	$(SRC_DIR)/engine/CubeStateHelper.cpp \
	$(SRC_DIR)/parser/Parser.cpp \
	$(SRC_DIR)/utils/utils.cpp \
	$(SRC_DIR)/solver/Kociemba/KociembaSolver.cpp \
	$(SRC_DIR)/solver/Kociemba/G1Solver.cpp \
	$(SRC_DIR)/solver/Kociemba/G2Solver.cpp \
	$(SRC_DIR)/solver/Kociemba/p1_move_tables.cpp \
	$(SRC_DIR)/solver/Kociemba/p2_move_tables.cpp \
	$(SRC_DIR)/solver/Pruning/TableIO.cpp \

SRC_FILES_BONUS := \
	$(BSRC_DIR)/main_bonus.cpp \
	$(BSRC_DIR)/RubikController_bonus.cpp \
	$(SRC_DIR)/cube/CubeOperations.cpp \
	$(SRC_DIR)/cube/Encoding.cpp \
	$(SRC_DIR)/spin/SpinManager.cpp \
	$(SRC_DIR)/engine/CubeStateHelper.cpp \
	$(SRC_DIR)/parser/Parser.cpp \
	$(SRC_DIR)/utils/utils.cpp \
	$(SRC_DIR)/solver/Kociemba/KociembaSolver.cpp \
	$(SRC_DIR)/solver/Kociemba/G1Solver.cpp \
	$(SRC_DIR)/solver/Kociemba/G2Solver.cpp \
	$(SRC_DIR)/solver/Kociemba/p1_move_tables.cpp \
	$(SRC_DIR)/solver/Kociemba/p2_move_tables.cpp \
	$(SRC_DIR)/solver/Pruning/TableIO.cpp \
	$(BSRC_DIR)/renderer/Renderer.cpp \
	$(BSRC_DIR)/renderer/Renderer_callbacks.cpp \
	$(BSRC_DIR)/renderer/Renderer_IEngine.cpp \
	$(BSRC_DIR)/renderer/Renderer_imgui.cpp \
	$(BSRC_DIR)/renderer/Shader.cpp \
	$(BSRC_DIR)/renderer/Camera.cpp \
	$(BSRC_DIR)/renderer/Mesh.cpp \
	$(BSRC_DIR)/renderer/RubiksCube.cpp \


TABLE_SRC := \
	$(SRC_DIR)/BuildPruningTable/main.cpp \
	$(SRC_DIR)/spin/SpinManager.cpp \
	$(SRC_DIR)/cube/CubeOperations.cpp \
	$(SRC_DIR)/cube/Encoding.cpp \
	$(SRC_DIR)/solver/Pruning/TableIO.cpp \
	$(SRC_DIR)/solver/Kociemba/p1_move_tables.cpp \
	$(SRC_DIR)/solver/Kociemba/p2_move_tables.cpp \


OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ_FILES_BONUS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES_BONUS))

TABLE_OBJ := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TABLE_SRC))


# ====================================================================================
# Color Codes for Output
# ====================================================================================

RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
NC      := \033[0m

# ====================================================================================
# Makefile Rules
# ====================================================================================

.PHONY: all clean fclean re start end

all: start $(NAME) end

$(NAME): $(OBJ_FILES) 
	@echo "$(BLUE)[LINK] Create the executable ...$(NC)"
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(NAME)

bonus: start $(OBJ_FILES_BONUS) end
	@echo "$(BLUE)[LINK] Create the bonus executable ...$(NC)"
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES_BONUS) $(GLIBFLAGS) -o $(BNAME)

$(OBJ_DIR)/%.o: %.cpp
	@echo "[BUILD] $<"
	@mkdir -p $(dir $@) $(TABLE_DIR)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

start:
	@echo "$(GREEN)========== Compilation $(NAME) started ==========$(NC)"

end:
	@echo "$(GREEN)========== Compilation ended ✅ ==========$(NC)"

clean:
	@echo "$(RED)[CLEAN] Remove objets...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)[FCLEAN] Remove the executable...$(NC)"
	@rm -rf $(BIN_DIR)
	@rm -f $(NAME) $(BNAME)

re: fclean all

# -----------------------------------------------------------
# Special Targets for Table Compilation
# -----------------------------------------------------------

table: $(TABLE_OBJ)
	@echo "$(BLUE)[LINK] Compilation des fichiers Table uniquement...$(NC)"
	@$(CXX) $(CXXFLAGS) $(TABLE_OBJ) -o $(BIN_DIR)/table_exec
	@echo "$(GREEN)Table compilation completed ✅$(NC)"
	@mkdir -p $(TABLE_DIR)
	@mkdir -p $(TABLE_DIR)/Kociemba
	@./$(BIN_DIR)/table_exec

table_clean:
	@echo "$(RED)[CLEAN] Nettoyage des objets Table uniquement...$(NC)"
	@rm -rf $(TABLE_DIR) $(BIN_DIR)/table_exec
