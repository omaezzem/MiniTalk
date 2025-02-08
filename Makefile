# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 10:31:54 by omaezzem          #+#    #+#              #
#    Updated: 2025/02/06 18:28:43 by omaezzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_CLIENT = Mandatory/client.c Mandatory/utilis.c
SRCS_SERVER = Mandatory/server.c Mandatory/utilis.c

SRCS_CLIENT_BONUS = bonus/client_bonus.c bonus/utilis_bonus.c
SRCS_SERVER_BONUS = bonus/server_bonus.c bonus/utilis_bonus.c

OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}
OBJS_SERVER = ${SRCS_SERVER:.c=.o}

OBJS_CLIENT_BONUS = ${SRCS_CLIENT_BONUS:.c=.o}
OBJS_SERVER_BONUS = ${SRCS_SERVER_BONUS:.c=.o}

NAME_CLIENT = client
NAME_SERVER = server

NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: $(NAME_CLIENT) $(NAME_SERVER)
bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

%.o:%.c minitalk.h
	${CC} $(CFLAGS) -c $< -o $@

${NAME_CLIENT}: $(OBJS_CLIENT)
	${CC} $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -o $(NAME_SERVER_BONUS)

clean:
	@$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)

fclean: clean
	@$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all
