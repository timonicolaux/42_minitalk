OBJS_DIR		=	.objs
SRCS_DIR		=	src
HEADER_DIR		=	includes

OBJS_DIR_BONUS		=	.objs_bonus
SRCS_DIR_BONUS		=	src_bonus
HEADER_DIR_BONUS	=	includes_bonus

PRINTF_PATH		=	./ft_printf
PRINTF			=	${PRINTF_PATH}/libftprintf.a

LIB				=	$(HEADER_DIR)/minitalk.h

LIB_BONUS		=	$(HEADER_DIR_BONUS)/minitalk_bonus.h

SRC_C			=	$(SRCS_DIR)/client.c \
					$(SRCS_DIR)/shared_utils.c

SRC_S			=	$(SRCS_DIR)/server.c \
					$(SRCS_DIR)/server_utils.c \
					$(SRCS_DIR)/shared_utils.c

SRC_C_BONUS		=	$(SRCS_DIR_BONUS)/client_bonus.c \
					$(SRCS_DIR_BONUS)/shared_utils_bonus.c

SRC_S_BONUS		=	$(SRCS_DIR_BONUS)/server_bonus.c \
					$(SRCS_DIR_BONUS)/server_utils_bonus.c \
					$(SRCS_DIR_BONUS)/shared_utils_bonus.c

OBJ_C			=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRC_C))
OBJ_S			=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRC_S))

OBJ_C_BONUS			=	$(patsubst $(SRCS_DIR_BONUS)%.c, $(OBJS_DIR_BONUS)%.o, $(SRC_C_BONUS))
OBJ_S_BONUS			=	$(patsubst $(SRCS_DIR_BONUS)%.c, $(OBJS_DIR_BONUS)%.o, $(SRC_S_BONUS))

NAME_C	=	client
NAME_S	=	server
NAME_C_BONUS	=	client_bonus
NAME_S_BONUS	=	server_bonus

CC		=	cc
FLAGS	=	-Wall -Wextra -Werror -I $(HEADER_DIR) -I $(PRINTF_PATH)
FLAGS_BONUS	=	-Wall -Wextra -Werror -I $(HEADER_DIR_BONUS) -I $(PRINTF_PATH)

$(OBJS_DIR)/%.o:		$(SRCS_DIR)/%.c $(LIB)
						mkdir -p $(@D)
						$(CC) $(FLAGS) -c $< -o $@

$(OBJS_DIR_BONUS)/%.o:	$(SRCS_DIR_BONUS)/%.c $(LIB_BONUS)
						mkdir -p $(@D)
						$(CC) $(FLAGS_BONUS) -c $< -o $@

all:	lib $(NAME_C) $(NAME_S)

bonus:	lib $(NAME_C_BONUS) $(NAME_S_BONUS)

lib:
		make -C $(PRINTF_PATH)

$(NAME_C):	$(OBJ_C) $(LIB) $(PRINTF)
			$(CC) $(OBJ_C) $(FLAGS) $(PRINTF) -o $(NAME_C)

$(NAME_S):	$(OBJ_S) $(LIB) $(PRINTF)
			$(CC) $(OBJ_S) $(FLAGS) $(PRINTF) -o $(NAME_S)

$(NAME_C_BONUS):	$(OBJ_C_BONUS) $(LIB_BONUS) $(PRINTF)
					$(CC) $(OBJ_C_BONUS) $(FLAGS_BONUS) $(PRINTF) -o $(NAME_C_BONUS)

$(NAME_S_BONUS):	$(OBJ_S_BONUS) $(LIB_BONUS) $(PRINTF)
					$(CC) $(OBJ_S_BONUS) $(FLAGS_BONUS) $(PRINTF) -o $(NAME_S_BONUS)

clean:
		make clean -C $(PRINTF_PATH)
		rm -f ${OBJ_C} ${OBJ_S}
		rm -f ${NAME_C} ${NAME_S}

fclean:	clean
		make fclean -C $(PRINTF_PATH)
		rm -f ${NAME_C} ${NAME_S}

clean_bonus:
		make clean -C $(PRINTF_PATH)
		rm -f ${OBJ_C_BONUS} ${OBJ_S_BONUS}
		rm -f ${NAME_C_BONUS} ${NAME_S_BONUS}

fclean_bonus:	clean_bonus
		make fclean -C $(PRINTF_PATH)
		rm -f ${NAME_C_BONUS} ${NAME_S_BONUS}

re:	fclean all

re_bonus:	fclean_bonus

.PHONY:	all clean fclean re bonus

