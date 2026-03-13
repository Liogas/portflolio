CXX 		= g++
CXXFLAGS 	= -Wall -Wextra -Werror -g3 -std=c++20 $(shell pkg-config --cflags sdl2 SDL2_image)
LDFLAGS 	= $(shell pkg-config --libs sdl2 SDL2_image)
INCLUDES 	= -I./includes -I./MySDL/includes

NAME = portfolio

OBJS_DIR = objs

SRCS_CORE_DIR	= srcs/core
SRCS_GAME_DIR	= srcs/game
SRCS_GRAPH_DIR	= srcs/graphics

SRCS_CORE	= \
	$(SRCS_CORE_DIR)/main.cpp \
	$(SRCS_CORE_DIR)/App.cpp \
	$(SRCS_CORE_DIR)/RessourceManager.cpp \
	$(SRCS_CORE_DIR)/SceneManager.cpp \
	$(SRCS_CORE_DIR)/scene/GameScene.cpp
SRCS_GAME	= \
	$(SRCS_GAME_DIR)/GameState.cpp \
	$(SRCS_GAME_DIR)/Player.cpp
SRCS_GRAPH	= \
	$(SRCS_GRAPH_DIR)/Sprite.cpp

OBJS_CORE 	= $(SRCS_CORE:$(SRCS_CORE_DIR)/%.cpp=$(OBJS_DIR)/core/%.o)
OBJS_GAME 	= $(SRCS_GAME:$(SRCS_GAME_DIR)/%.cpp=$(OBJS_DIR)/game/%.o)
OBJS_GRAPH	= $(SRCS_GRAPH:$(SRCS_GRAPH_DIR)/%.cpp=$(OBJS_DIR)/graph/%.o)

SRCS_SDL_DIR = MySDL/srcs

SRCS_SDL = \
	$(SRCS_SDL_DIR)/AppSDL.cpp \
	$(SRCS_SDL_DIR)/WindowSDL.cpp \
	$(SRCS_SDL_DIR)/RendererSDL.cpp \
	$(SRCS_SDL_DIR)/EventSDL.cpp \
	$(SRCS_SDL_DIR)/AnimationSDL.cpp \
	$(SRCS_SDL_DIR)/TextureSDL.cpp \
	$(SRCS_SDL_DIR)/InputSDL.cpp

OBJS_SDL = $(SRCS_SDL:$(SRCS_SDL_DIR)/%.cpp=$(OBJS_DIR)/sdl/%.o)

OBJS = $(OBJS_CORE) $(OBJS_GAME) $(OBJS_GRAPH) $(OBJS_SDL)

all: $(NAME)

# CORE
$(OBJS_DIR)/core/%.o: $(SRCS_CORE_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# GAME
$(OBJS_DIR)/game/%.o: $(SRCS_GAME_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# GRAPHICS
$(OBJS_DIR)/graph/%.o: $(SRCS_GRAPH_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# SDL
$(OBJS_DIR)/sdl/%.o: $(SRCS_SDL_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "👌 build success"

clean:
	rm -rf $(OBJS_DIR) $(OBJS_SDL_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re