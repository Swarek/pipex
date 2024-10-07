NAME = pipex

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SOURCES := $(wildcard $(SRC_DIR)/**/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJECTS := $(OBJECTS:main.c=$(OBJ_DIR)/main.o)

$(info SOURCES: $(SOURCES))
$(info OBJECTS: $(OBJECTS))

FLAGS = -fPIC -I$(INC_DIR) -I$(LIBFT_DIR)/includes
LINKS = -L$(LIBFT_DIR) -lft

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	gcc $(OBJECTS) -o $(NAME) $(FLAGS) $(LINKS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	gcc $(FLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/main.o: main.c
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

re: fclean $(NAME)

debug: FLAGS += -g
debug: re