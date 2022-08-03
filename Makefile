# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 16:58:21 by lschrafs          #+#    #+#              #
#    Updated: 2022/08/03 15:47:34 by lschrafs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

COMPILER 	= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror

MYLIBS 		= 	libft/libft.a
LIBS 		= 	-lreadline

SRCS_PATH 	= 	./src/
BUILTINS	=	builtins/
EXECUTE		=	execute/
INIT		=	init/
PARSING		=	parsing/
UTILS		=	utils/

SRCS_NAMES	= 	main \
				$(BUILTINS)ms_env \
				$(EXECUTE)ms_input_execute \
				$(INIT)ms_data_init \
				$(INIT)ms_signaling \
				$(PARSING)ms_parse \
				$(PARSING)ms_parse_expand \
				$(PARSING)ms_parse_utils \
				$(UTILS)ms_utils \
				$(UTILS)ms_free_exit \
				$(UTILS)ms_lst_str \
				$(UTILS)ms_lst_env

OBJS_PATH	= 	./obj/
OBJS_NAMES	= 	$(SRCS_NAMES:%=%.o)
OBJS		= 	$(addprefix $(OBJS_PATH), $(OBJS_NAMES))

ALL_DIRS	= 	$(BUILTINS) $(EXECUTE) $(INIT) $(PARSING) $(UTILS)
DIRS_PATHS	=	$(addprefix $(OBJS_PATH), $(ALL_DIRS))

all: $(NAME)

$(NAME): $(OBJS) $(MYLIBS)
	$(COMPILER) $(CFLAGS) $(OBJS) $(MYLIBS) $(LIBS) -o $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	echo $(DIRS_PATHS)
	mkdir -p $(OBJS_PATH)
	mkdir -p $(DIRS_PATHS)
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(MYLIBS): FORCE
	make -C $(dir $@)

FORCE: ;

clean:
	rm -rf $(OBJS_PATH)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all