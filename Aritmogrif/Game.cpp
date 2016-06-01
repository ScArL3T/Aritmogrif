#include <fstream>

#include "Game.h"

Game::Game(StateManager &stack, sf::RenderWindow &window)
	: State(stack, window)
	, board(window)
{
		
}


Game::~Game()
{
}

void Game::handleEvent(const sf::Event &event)
{
	board.handleEvent(event);
}

void Game::update(sf::Time gameTime)
{
	board.update();

	if (board.getGameOver())
		getWindow().close();
}

void Game::draw()
{
	board.draw();
}