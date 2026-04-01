#include "GameScene.hpp"

GameScene::GameScene(int width, int height)
{
	std::cout << "GameScene created" << std::endl;
	this->_height = height;
	this->_width = width;
	this->_map = nullptr;
}

GameScene::~GameScene()
{
	std::cout << "GameScene destroyed" << std::endl;
}

void	GameScene::onEnter(RessourceManager &ressources)
{
	std::cout << "Enter on GameScene" << std::endl;
	try
	{
		MapParseur	parseur("home.tmj");
		this->_map = parseur.start(ressources);
	} catch (const std::exception &e)
	{
		throw std::runtime_error(e.what());
	}
}

void	GameScene::onExit()
{
	std::cout << "Exit of GameScene" << std::endl;
}

void	GameScene::handleEvents(EventSDL &events, const GameState &gameState)
{
	(void)gameState;
	(void)events;
}

void	GameScene::update(InputSDL &inputs, const GameState &gameState, float deltaTime)
{
	if (inputs.isKeyPressed(SDL_SCANCODE_D))
		gameState.player->move(EDirection::RIGHT);
	else if (inputs.isKeyPressed(SDL_SCANCODE_A))
		gameState.player->move(EDirection::LEFT);
	else if (inputs.isKeyPressed(SDL_SCANCODE_S))
		gameState.player->move(EDirection::BOTTOM);
	else if (inputs.isKeyPressed(SDL_SCANCODE_W))
		gameState.player->move(EDirection::TOP);
	else
		gameState.player->move(EDirection::NONE);
	gameState.player->update(deltaTime, *this);
}

void	GameScene::render(RendererSDL &renderer, const GameState &gameState)
{
	gameState.player->render();
	renderer.present();
}
