CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I ./include

LIB			=	./lib
LIBFTDIR	=	$(LIB)/ft_printf
LIBFT		=	$(LIBFTDIR)/libftprintf.a

CLIENT_NAME		=	client
CLIENT_SRCS		=	./src/client.c\

CLIENT_OBJS		=	$(CLIENT_SRCS:%.c=%.o)

SERVER_NAME		=	server
SERVER_SRCS		=	./src/server.c\

SERVER_OBJS		=	$(SERVER_SRCS:%.c=%.o)

.PHONY: all clean fclean re test

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT)
	$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(LIBFT) $(CFLAGS)

$(SERVER_NAME): $(SERVER_OBJS) $(LIBFT)
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJS) $(LIBFT) $(CFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) bonus

clean:
	$(RM) $(CLIENT_OBJS) $(SERVER_OBJS)

fclean: clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

test: 
	norminette include src bonus
	$(MAKE) all
