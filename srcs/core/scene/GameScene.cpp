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
		this->_map = parseur.start(ressources, this);
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
	bool computerOn = false;
	for (auto &e : this->_entities)
	{
		if (auto *c = dynamic_cast<Computer *>(e.get()))
			if (c->isOn())
				computerOn = true;
	}

	if (computerOn)
		return ;
	if (inputs.isKeyPressed(SDL_SCANCODE_E)) 
    {
       for (auto &e : this->_entities)
	   {
			if (auto* c = dynamic_cast<Computer*>(e.get()))
			{
				if (c->canInteract(*gameState.player))
				{
					c->interact(*gameState.player);
					computerOn = true;
				}
			}
	   }
    }
	this->updatePlayer(inputs, gameState, deltaTime);
}

void	GameScene::updatePlayer(InputSDL &inputs, const GameState &gameState, float deltaTime)
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

	gameState.player->updateWithCollision(
		[this](int x, int y){ return this->_map->isWalkable(x, y);},
		this->_width,
		this->_height
	);
	gameState.player->update(deltaTime);
	this->_camera.setPos(gameState.player->getX() - (this->_width / 4),
		gameState.player->getY() - (this->_height / 4));
}

void	GameScene::render(RendererSDL &renderer, const GameState &gameState)
{
	this->_map->render(this->_camera);
	gameState.player->render(this->_camera);
    for (auto &e : this->_entities)
	{
		if (auto* c = dynamic_cast<Computer*>(e.get()))
		{
			if (c->isOn())
				this->_computerRenderer.draw(renderer, *c);
		}
    }
	renderer.present();
}
