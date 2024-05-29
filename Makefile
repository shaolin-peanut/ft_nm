NAME = ft_nm

HEADERDIR = include/
HEADERS = $(HEADERDIR)ft_nm.h

FILES = main.c utils.c process_symbols.c sort.c

OBJDIR = objs/
OBJLIST = $(patsubst %.c, %.o, $(FILES))
OBJS = $(addprefix $(OBJDIR), $(OBJLIST))

LIBFT = libft/libft.a

MAKE = make

CC = gcc
FLAGS = -Wall -Wextra -Werror
FSAN = # -fsanitize=address
DEBUGGER = gdb
DBG =  -g

all = $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@echo "Compiling libft"
	@$(MAKE) -C libft
	@echo "Linking ft_nm: $(OBJS)"
	@$(CC) $(OBJS) $(FSAN) $(LIBFT) -o $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJS): $(FILES)
	@echo "Compiling ft_nm: $(FILES) and $(HEADERS)"
	@$(CC) $(FLAGS) $(DBG) -c $(FILES)
	@mv $(OBJLIST) $(OBJDIR)

clean:
	@echo "make clean libft"
	@$(MAKE) clean -C libft
	@echo "Deleting object files in /objs"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "deleting $(NAME)"
	@echo "$(MAKE) fclean -C libft"
	@rm -rf $(NAME)

re: fclean
	$(MAKE) all

up:
	@docker-compose up --build --detach && docker ps
	@docker exec -it nm_ft_nm_1 zsh


down:
	@docker-compose down

.PHONY	: all clean fclean re
