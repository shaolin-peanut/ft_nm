NAME = ftnm

HEADERDIR = include/
HEADERS = $(HEADERDIR)ftnm.h

FILES = main.c

OBJDIR = objs/
OBJLIST = $(patsubst %.c, %.o, $(FILES))
OBJS = $(addprefix $(OBJDIR), $(OBJLIST))

CC = gcc
FLAGS = # -Wall -Wextra -Werror
DEBUGGER = gdb
DEBUG_FLGS = -g

all = $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@echo "Linking ftnm: $(OBJS)"
	@$(CC) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJS): $(FILES)
	@echo "Compiling ftnm: $(FILES) and $(HEADERS)"
	@$(CC) $(FLAGS) -I$(HEADERDIR) -c $< -o $@

clean:
	@echo "Deleting object files in /objs"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "deleting $(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY	: all clean fclean re