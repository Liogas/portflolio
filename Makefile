CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -g3 -std=c++20 \
			$(shell pkg-config --cflags sdl2 SDL2_image)

LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image)

INCLUDES = -I./includes -I./MySDL/includes

NAME = portfolio

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = \
	$(SRCS_DIR)/main.cpp \
	$(SRCS_DIR)/App.cpp \
	$(SRCS_DIR)/Sprite.cpp \
	$(SRCS_DIR)/Player.cpp \
	$(SRCS_DIR)/RessourceManager.cpp 

OBJS = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)


SRCS_SDL_DIR = MySDL/srcs
OBJS_SDL_DIR = MySDL/objs

SRCS_SDL = \
	$(SRCS_SDL_DIR)/AppSDL.cpp \
	$(SRCS_SDL_DIR)/WindowSDL.cpp \
	$(SRCS_SDL_DIR)/RendererSDL.cpp \
	$(SRCS_SDL_DIR)/EventSDL.cpp \
	$(SRCS_SDL_DIR)/TextureSDL.cpp \
	$(SRCS_SDL_DIR)/InputSDL.cpp

OBJS_SDL = $(SRCS_SDL:$(SRCS_SDL_DIR)/%.cpp=$(OBJS_SDL_DIR)/%.o)


all: $(NAME)


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_SDL_DIR)/%.o: $(SRCS_SDL_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


$(NAME): $(OBJS) $(OBJS_SDL)
	$(CXX) $(OBJS) $(OBJS_SDL) $(LDFLAGS) -o $(NAME)
	@echo "👌 build success"


clean:
	rm -rf $(OBJS_DIR) $(OBJS_SDL_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re