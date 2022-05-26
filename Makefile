CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I ./include

NAME			=	minitalk

LIBFTDIR	=	./lib/libft
LIBFT		=	$(LIBFTDIR)/libft.a
LIB			=	$(LIBFT)

SERVER		=	server
SERVER_SRC		=	./src/server.c

CLIENT		=	client
CLIENT_SRC		=	./src/client.c

ifdef WITH_BONUS
	SERVER_SRC = ./bonus/server_bonus.c
	CLIENT_SRC = ./bonus/client_bonus.c
endif

.PHONY: $(NAME) all bonus clean fclean re test

all: $(NAME)

$(NAME): $(CLIENT) $(SERVER)

bonus:
	$(MAKE) WITHBONUS=1

$(SERVER): $(SERVER_SRC) $(LIB)
	$(CC) -o $(SERVER) $(SERVER_SRC) $(LIB) $(CFLAGS)

$(CLIENT): $(CLIENT_SRC) $(LIB)
	$(CC) -o $(CLIENT) $(CLIENT_SRC) $(LIB) $(CFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(CLIENT) $(SERVER) *.out

fclean: clean

re: fclean all

kill:
	@ps | grep \./server | grep -v grep | awk '{print $$1}' | xargs -n1 kill

tmp:
	diff <(echo "hello") <(print "hello")

test: all
	-norminette include src bonus
	-./test.sh
