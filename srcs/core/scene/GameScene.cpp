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
