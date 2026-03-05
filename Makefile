CXX 		= g++ 
CXXFLAGS	= -Wall -Wextra -Werror -g3 -std=c++20 $(shell pkg-config --cflags sdl2)
LDFLAGS     = $(shell pkg-config --libs sdl2)

INCLUDES		= -I./includes/
INCLUDES_SDL	= -I./MySDL/includes

NAME		= portfolio

SRCS_DIR 	= srcs
OBJS_DIR 	= objs
SRCS		= $(SRCS_DIR)/main.cpp
OBJS 		= $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

SRCS_SDL_DIR	=	MySDL/srcs
OBJS_SDL_DIR	= 	MySDL/objs
SRCS_SDL		=	$(SRCS_SDL_DIR)/AppSDL.cpp \
					$(SRCS_SDL_DIR)/WindowSDL.cpp \
					$(SRCS_SDL_DIR)/RendererSDL.cpp \
					$(SRCS_SDL_DIR)/EventSDL.cpp \
					$(SRCS_SDL_DIR)/InputSDL.cpp
OBJS_SDL		=	$(SRCS_SDL:$(SRCS_SDL_DIR)/%.cpp=$(OBJS_SDL_DIR)/%.o)


all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(INCLUDES_SDL) -c $< -o $@

$(OBJS_SDL_DIR)/%.o: $(SRCS_SDL_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(INCLUDES) $(INCLUDES_SDL) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_SDL)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(OBJS_SDL) $(LDFLAGS)
	@echo "👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌"

clean:
	rm -rf $(OBJS_DIR) $(OBJS_SDL_DIR)

fclean: clean
	rm -rf $(NAME) *.out *.txt

re : fclean $(NAME)

.PHONY: all clean fclean re