CXX 		= g++ 
CXXFLAGS	= -Wall -Wextra -Werror -g3 -std=c++20 $(shell pkg-config --cflags sdl2)
LDFLAGS     = $(shell pkg-config --libs sdl2)
INCLUDES	= -I./includes/

NAME		= portfolio

SRCS_DIR 	= srcs
OBJS_DIR 	= objs
SRCS		= $(SRCS_DIR)/main.cpp

OBJS 		= $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌"

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME) *.out *.txt

re : fclean $(NAME)

.PHONY: all clean fclean re