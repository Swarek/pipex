NAME = pipex

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

# Les sources obligatoires n'incluent plus le main.c depuis src, il est maintenant dans le répertoire racine
MANDATORY_SOURCES := $(wildcard $(SRC_DIR)/setting_up/*.c)
MANDATORY_OBJECTS = $(MANDATORY_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MANDATORY_OBJECTS += $(OBJ_DIR)/main.o

# Les sources bonus incluent les fichiers bonus ainsi que ceux de setting_up, mais pas le main.c
BONUS_SOURCES := $(wildcard $(SRC_DIR)/bonus/*.c $(SRC_DIR)/setting_up/*.c)
BONUS_OBJECTS = $(BONUS_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJECTS := $(BONUS_OBJECTS:main_bonus.c=$(OBJ_DIR)/main_bonus.o)

FLAGS = -fPIC -I$(INC_DIR) -I$(LIBFT_DIR)/includes
LINKS = -L$(LIBFT_DIR) -lft

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Compilation normale
all: $(NAME)

$(NAME): $(LIBFT) $(MANDATORY_OBJECTS)
	gcc $(MANDATORY_OBJECTS) -o $(NAME) $(FLAGS) $(LINKS)

# Compilation bonus qui écrase l'exécutable précédent
bonus: $(LIBFT) $(BONUS_OBJECTS)
	gcc $(BONUS_OBJECTS) -o $(NAME) $(FLAGS) $(LINKS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	gcc $(FLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(dir $@)
	gcc $(FLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/main_bonus.o: $(SRC_DIR)/bonus/main_bonus.c
	@mkdir -p $(dir $@)
	gcc $(FLAGS) -I $(INC_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	find $(OBJ_DIR) -type f -name '*.o' -delete
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(OBJ_DIR)/*.o
	make -C $(LIBFT_DIR) fclean

re: fclean all

debug: FLAGS += -g
debug: re
