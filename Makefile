NAME = ftnm

HEADERDIR = include/
HEADERS = $(HEADERDIR)ftnm.h

FILES = main.c parseelf.c utils.c

OBJDIR = objs/
OBJLIST = $(patsubst %.c, %.o, $(FILES))
OBJS = $(addprefix $(OBJDIR), $(OBJLIST))

CC = gcc
DEBUGGER = gdb
DEBUG_FLGS = -g

all = $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@echo "Linking ftnm: $(OBJS)"
	@$(CC) $(OBJS) -o $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJS): $(FILES)
	@echo "Compiling ftnm: $(FILES) and $(HEADERS)"
	@$(CC) -c $(FILES)
	@mv $(OBJLIST) $(OBJDIR)

clean:
	@echo "Deleting object files in /objs"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "deleting $(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY	: all clean fclean re