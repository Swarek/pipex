NAME = pipex

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

MANDATORY_SOURCES := $(wildcard $(SRC_DIR)/setting_up/*.c)
MANDATORY_OBJECTS = $(MANDATORY_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MANDATORY_OBJECTS += $(OBJ_DIR)/main.o

BONUS_SOURCES := $(wildcard $(SRC_DIR)/bonus/*.c $(SRC_DIR)/setting_up/*.c)
BONUS_OBJECTS = $(BONUS_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJECTS := $(BONUS_OBJECTS:main_bonus.c=$(OBJ_DIR)/main_bonus.o)

FLAGS = -I$(INC_DIR) -I$(LIBFT_DIR)/includes -Wall -Wextra -Werror
LINKS = -L$(LIBFT_DIR) -lft

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(MANDATORY_OBJECTS)
	cc $(MANDATORY_OBJECTS) -o $(NAME) $(LINKS)

bonus: $(LIBFT) $(BONUS_OBJECTS)
	cc $(BONUS_OBJECTS) -o $(NAME) $(LINKS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@

$(OBJ_DIR)/main_bonus.o: $(SRC_DIR)/bonus/main_bonus.c
	@mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@

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

.PHONY: all bonus clean fclean re debug