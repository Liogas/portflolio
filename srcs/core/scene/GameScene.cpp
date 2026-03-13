#include "GameScene.hpp"

GameScene::GameScene()
{
	std::cout << "GameScene created" << std::endl;
	this->_height = 720;
	this->_width = 1280;
}

GameScene::~GameScene()
{
	std::cout << "GameScene destroyed" << std::endl;
}

void	GameScene::onEnter()
{
	std::cout << "Enter on GameScene" << std::endl;
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

void	GameScene::update(InputSDL &inputs, const GameState &gameState)
{
	if (inputs.isKeyPressed(SDL_SCANCODE_D))
		gameState.player->move(EDirection::RIGHT, *this);
	else if (inputs.isKeyPressed(SDL_SCANCODE_A))
		gameState.player->move(EDirection::LEFT, *this);
	else if (inputs.isKeyPressed(SDL_SCANCODE_S))
		gameState.player->move(EDirection::BOTTOM, *this);
	else if (inputs.isKeyPressed(SDL_SCANCODE_W))
		gameState.player->move(EDirection::TOP, *this);
	else
		gameState.player->move(EDirection::NONE, *this);
	gameState.player->update();
}

void	GameScene::render(RendererSDL &renderer, const GameState &gameState)
{
	gameState.player->render();
	renderer.present();
}
