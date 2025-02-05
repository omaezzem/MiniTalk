# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 10:31:54 by omaezzem          #+#    #+#              #
#    Updated: 2025/01/31 15:31:57 by omaezzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME = client
SERVER_NAME = server
CC = cc
CFLAGS = -Wall -Wextra -Werror
MAIN_CLIENT = client.c utilis.c
MAIN_SERVER = server.c utilis.c
CLIENT_OBJECT = $(MAIN_CLIENT:.c=.o)
SERVER_OBJECT = $(MAIN_SERVER:.c=.o)
INCLUDE = Minitalk.h

all : $(SERVER_NAME) $(CLIENT_NAME)

%.o: %.c (INCLUDE)
	$(CC) -c $(CFLAGS) $< -o $@

$(CLIENT_NAME) : $(MAIN_CLIENT)
	$(CC) $(CFLAGS) $(MAIN_CLIENT) -o $(CLIENT_NAME)


$(SERVER_NAME) : $(MAIN_SERVER)
	$(CC) $(CFLAGS) $(MAIN_SERVER) -o $(SERVER_NAME)

clean :
	@rm -f $(CLIENT_OBJECT)
	@rm -f $(SERVER_OBJECT)

fclean : clean
	@rm -f $(SERVER_NAME) $(CLIENT_NAME)

re : fclean all