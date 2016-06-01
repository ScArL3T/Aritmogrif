#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "StatesID.h"

class StateManager;

class State : private sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<State>; // typedef std::unique_ptr<State> Ptr;

	explicit State(StateManager &stack, sf::RenderWindow &window);
	virtual ~State() = default;

	virtual void handleEvent(const sf::Event &event) = 0;
	virtual void update(sf::Time gameTime) = 0;
	virtual void draw() = 0;

	bool isActive();

protected:
	sf::RenderWindow &getWindow();

	void pushState(States::ID state);
	void popState();
	void clearStates();

	void setActive(bool value);

private:
	StateManager	 &stack;
	sf::RenderWindow &window;

	bool active;
};