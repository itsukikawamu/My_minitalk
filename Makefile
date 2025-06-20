# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 13:17:32 by ikawamuk          #+#    #+#              #
#    Updated: 2025/06/19 20:12:45 by ikawamuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME := client
SERVER_NAME := server

CC := cc
CFLAGS=-Wall -Wextra -Werror $(addprefix -I,$(INCLUDES))
AR := ar
ARFLAGS := rcs
RM := rm -f
RMDIR := rm -rf

SRCDIR := src
OBJDIR := obj
INCDIR := include
LIBFTDIR := libft
TMPDIR := ar_tmp

CLIENT_SRCFILES_BASE :=	client_main \
						client_sigaction \
						client_utils \
						client_send_str \

SERVER_SRCFILES_BASE :=	server_main \
						server_sigaction \
						server_process_signal \

SRC_SUFFIX := .c
ifeq ($(IS_BONUS),1)
	SRC_SUFFIX := _bonus.c
	SRCDIR := src/bonus
endif

CLIENT_SRCFILES := $(addsuffix $(SRC_SUFFIX), $(CLIENT_SRCFILES_BASE))
SERVER_SRCFILES := $(addsuffix $(SRC_SUFFIX), $(SERVER_SRCFILES_BASE))

CLIENT_SRCS := $(addprefix $(SRCDIR)/, $(CLIENT_SRCFILES))
SERVER_SRCS := $(addprefix $(SRCDIR)/, $(SERVER_SRCFILES))
CLIENT_OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CLIENT_SRCS))
SERVER_OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SERVER_SRCS))
INCLUDES := $(INCDIR) $(LIBFTDIR)/include

LIBFT := $(LIBFTDIR)/libft.a

VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-leak-kinds=all

all: $(LIBFT) $(CLIENT_NAME) $(SERVER_NAME) 

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)
	
$(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) -o $@

$(SERVER_NAME): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean	
	@$(RMDIR) $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

bonus:
	$(MAKE) IS_BONUS=1 all

# test: all
# 	@$(CC) test.c $(NAME) $(LIBFT) -o test
# 	$(VALGRIND) $(VALGRIND_FLAGS) ./test

.PHONY:all clean fclean re bonus test
