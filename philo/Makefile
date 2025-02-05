# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 15:29:44 by aubertra          #+#    #+#              #
#    Updated: 2025/02/05 14:55:01 by aubertra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CPP = cc
FLAGS = -Wall -Wextra -Werror -g3 -pthread

NAME = philo
SRCS =  main.c\
		parsing.c\
		eating.c\
		routine.c\
		monitor.c\
		init.c\
		free.c\
		utils.c\
		threads.c\

OBJS = $(addprefix objs/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $(NAME)

objs/%.o: srcs/%.c
	@mkdir -p objs/
	$(CPP) $(FLAGS) -c $< -o $@ -I includes/

clean:
	rm -rf objs/

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY:				all clean fclean re