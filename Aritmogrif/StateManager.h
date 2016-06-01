#pragma once

#include "State.h"

class StateManager : private sf::NonCopyable
{
public:
	explicit StateManager(sf::RenderWindow &window);
	~StateManager();

	void pushState(States::ID state);
	void popState();
	void clearStates();

	void handleEvent(const sf::Event &event);
	void update(sf::Time gameTime);
	void draw();

private:
	State::Ptr createState(States::ID state);
	void       applyChanges();

private:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

	std::vector<std::pair<Action, States::ID>> queue;
	std::vector<State::Ptr> stateStack;
	State::Ptr			    state;

	sf::RenderWindow       &window;
};