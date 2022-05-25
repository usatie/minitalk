# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 04:40:53 by susami            #+#    #+#              #
#    Updated: 2022/05/25 21:50:32 by susami           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	server client
SERVER_SRC	=	server.c
CLIENT_SRC	=	client.c

ifdef WITH_BONUS
	SERVER_SRC = server_bonus.c
	CLIENT_SRC = client_bonus.c
endif

.PHONY: all clean fclean re bonus kill

all: server client

clean:
	rm -rf server client
fclean: clean
re: fclean all

bonus:
	make WITH_BONUS=1

kill:
	@ps | grep \./server | grep -v grep | awk '{print $$1}' | xargs -n1 kill

test: all
	./server &
	ps | grep "./server" | grep -v grep | head -1 | awk '{printf $$1}' | xargs -I {} ./client {} $$(yes | tr -d '\n' | head -c10000)
	ps | grep "./server" | grep -v grep | awk '{print $$1}' | xargs -n1 kill

server: $(SERVER_SRC)
	gcc $(SERVER_SRC) -o server

client: $(CLIENT_SRC)
	gcc $(CLIENT_SRC) -o client
