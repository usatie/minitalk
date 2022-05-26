CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I ./include

LIB			=	./lib
LIBFTDIR	=	$(LIB)/ft_printf
LIBFT		=	$(LIBFTDIR)/libftprintf.a

SERVER_NAME		=	server
SERVER_SRC		=	./src/server.c

CLIENT_NAME		=	client
CLIENT_SRC		=	./src/client.c

NAME			=	$(SERVER_NAME) $(CLIENT_NAME)

ifdef WITH_BONUS
	SERVER_SRC = ./src/server_bonus.c
	CLIENT_SRC = ./src/client_bonus.c
endif

.PHONY: all clean fclean re test

all: $(CLIENT_NAME) $(SERVER_NAME)

bonus:
	$(MAKE) WITHBONUS=1

$(CLIENT_NAME): $(CLIENT_SRC) $(LIBFT)
	$(CC) -o $(CLIENT_NAME) $(CLIENT_SRC) $(LIBFT) $(CFLAGS)

$(SERVER_NAME): $(SERVER_SRC) $(LIBFT)
	$(CC) -o $(SERVER_NAME) $(SERVER_SRC) $(LIBFT) $(CFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) bonus

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

kill:
	@ps | grep \./server | grep -v grep | awk '{print $$1}' | xargs -n1 kill

test: all
	@#norminette include src bonus
	./server | tail +2 | wc -c &
	ps | grep "./server" | grep -v grep | head -1 | awk '{printf $$1}' | xargs -I {} ./client {} $$(yes "hello" | tr -d '\n' | head -c10000)
	ps | grep "./server" | grep -v grep | awk '{print $$1}' | xargs -n1 kill
