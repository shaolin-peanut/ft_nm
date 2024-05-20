NAME = ft_nm

HEADERDIR = include/
HEADERS = $(HEADERDIR)ft_nm.h

FILES = main.c utils.c process_symbols.c

OBJDIR = objs/
OBJLIST = $(patsubst %.c, %.o, $(FILES))
OBJS = $(addprefix $(OBJDIR), $(OBJLIST))


CC = gcc
FLAGS = # -Wall -Wextra -Werror
FSAN = -fsanitize=address
DEBUGGER = gdb
DBG = -g

all = $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@echo "Linking ft_nm: $(OBJS)"
	@$(CC) $(OBJS) $(FSAN)  -o $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJS): $(FILES)
	@echo "Compiling ft_nm: $(FILES) and $(HEADERS)"
	@$(CC) $(FLAGS) -c $(FILES)
	@mv $(OBJLIST) $(OBJDIR)

docker-up:
	docker compose up --build --detach

clean:
	@echo "Deleting object files in /objs"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "deleting $(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY	: all clean fclean re
