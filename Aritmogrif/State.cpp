#include "State.h"
#include "StateManager.h"

State::State(StateManager &stack, sf::RenderWindow &window)
	: stack(stack)
	, window(window)
	, active(true)
{

}

bool State::isActive()
{
	return active;
}

sf::RenderWindow &State::getWindow()
{
	return window;
}

void State::pushState(States::ID state)
{
	stack.pushState(state);
}

void State::popState()
{
	stack.popState();
}

void State::clearStates()
{
	stack.clearStates();
}

void State::setActive(bool value)
{
	active = value;
}