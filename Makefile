CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I ./include

FTPRINTFDIR	=	.lib/ft_printf
LIB			=	$(FTPRINTFDIR)/libftprintf.a

SERVER		=	server
SERVER_SRC		=	./src/server.c

CLIENT		=	client
CLIENT_SRC		=	./src/client.c

NAME			=	minitalk

ifdef WITH_BONUS
	SERVER_SRC = ./src/server_bonus.c
	CLIENT_SRC = ./src/client_bonus.c
endif

.PHONY: $(NAME) all clean fclean re test

all: $(NAME)

$(NAME): $(CLIENT) $(SERVER)

bonus:
	$(MAKE) WITHBONUS=1

$(CLIENT): $(CLIENT_SRC) $(LIB)
	$(CC) -o $(CLIENT) $(CLIENT_SRC) $(LIB) $(CFLAGS)

$(SERVER): $(SERVER_SRC) $(LIB)
	$(CC) -o $(SERVER) $(SERVER_SRC) $(LIB) $(CFLAGS)

$(LIB):
	$(MAKE) -C $(FTPRINTFDIR) bonus

clean:
	$(RM) $(CLIENT) $(SERVER) *.out

fclean: clean

re: fclean all

kill:
	@ps | grep \./server | grep -v grep | awk '{print $$1}' | xargs -n1 kill

test: all
	@#norminette include src bonus
	./server | tail +2 | wc -c &
	ps | grep "./server" | grep -v grep | head -1 | awk '{printf $$1}' | xargs -I {} ./client {} $$(yes "hello" | tr -d '\n' | head -c10000)
	ps | grep "./server" | grep -v grep | awk '{print $$1}' | xargs -n1 kill
