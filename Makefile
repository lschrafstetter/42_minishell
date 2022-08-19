# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 16:58:21 by lschrafs          #+#    #+#              #
#    Updated: 2022/08/19 14:28:34 by lschrafs         ###   ########.fr        #
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
				$(BUILTINS)ms_builtins_utils1 \
				$(BUILTINS)ms_builtins_utils2 \
				$(BUILTINS)ms_cd \
				$(BUILTINS)ms_env \
				$(BUILTINS)ms_export \
				$(BUILTINS)ms_pwd_echo_unset \
				$(EXECUTE)ms_input_execute \
				$(EXECUTE)ms_redirect \
				$(EXECUTE)ms_exec_single \
				$(EXECUTE)ms_exec_piped \
				$(EXECUTE)ms_exec_pi_exe \
				$(EXECUTE)ms_exec_utils \
				$(INIT)ms_data_init \
				$(INIT)ms_signaling \
				$(PARSING)ms_pa \
				$(PARSING)ms_pa_exp \
				$(PARSING)ms_pa_exp_str \
				$(PARSING)ms_pa_exp_quotes \
				$(PARSING)ms_pa_exp_lst \
				$(PARSING)ms_pa_utils1 \
				$(PARSING)ms_pa_utils2 \
				$(UTILS)ms_utils \
				$(UTILS)ms_free_exit \
				$(UTILS)ms_lst_str1 \
				$(UTILS)ms_lst_str2 \
				$(UTILS)ms_lst_env1 \
				$(UTILS)ms_lst_env2 \
				$(UTILS)ms_lst_red

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