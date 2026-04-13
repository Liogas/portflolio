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

void	GameScene::onEnter(RessourceManager &ressources, const GameState &gameState)
{
	std::cout << "Enter on GameScene" << std::endl;
	try
	{
		MapParseur	parseur("home.tmj");
		this->_map = parseur.start(ressources);
		gameState.player->setPos(550, 280);
		this->_camera.setPos(gameState.player->getX()- (this->_width / 2),
			gameState.player->getY() - (this->_height / 2));
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
	this->_camera.setPos(gameState.player->getX() - (this->_width / 4),
		gameState.player->getY() - (this->_height / 4));
}

bool	GameScene::isWalkable(int posX, int posY) const
{
	auto& map = *this->_map;

    int tileSize = map.getTileSize();
    int tileX = posX / tileSize + 1;
    int tileY = posY / tileSize + 1;

    if (tileX < 0 || tileY < 0 
        || tileX >= map.getWidth() 
        || tileY >= map.getHeight())
        return (false);
    int index = tileY * map.getWidth() + tileX;
    return (map.getCollisionLayer().data[index] == 0);
}

void	GameScene::render(RendererSDL &renderer, const GameState &gameState)
{
	this->_map->render(this->_camera);
	gameState.player->render(this->_camera);
	renderer.present();
}
