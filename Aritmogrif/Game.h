#pragma once

#include "State.h"
#include "Board.h"

class Game final : public State
{
public:
	explicit Game(StateManager &stack, sf::RenderWindow &window);
	~Game();

	void handleEvent(const sf::Event &event) override;
	void update(sf::Time gameTime) override;
	void draw() override;

private:
	Board board;
};