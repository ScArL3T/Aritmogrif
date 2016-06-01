#include "StateManager.h"
#include "Game.h"

StateManager::StateManager(sf::RenderWindow &window)
	: window(window)
{
}

StateManager::~StateManager()
{
}

void StateManager::pushState(States::ID state)
{
	queue.push_back(std::make_pair(Action::Push, state));
}

void StateManager::popState()
{
	queue.push_back(std::make_pair(Action::Pop, States::ID::None));
}

void StateManager::clearStates()
{
	queue.push_back(std::make_pair(Action::Clear, States::ID::None));
}

void StateManager::handleEvent(const sf::Event &event)
{
	for (State::Ptr &state : stateStack)
		if (state->isActive())
			state->handleEvent(event);

	applyChanges();
}

void StateManager::update(sf::Time gameTime)
{
	for (State::Ptr &state : stateStack)
		if (state->isActive())
			state->update(gameTime);

	applyChanges();
}

void StateManager::draw()
{
	for (State::Ptr &state : stateStack)
		state->draw();
}

State::Ptr StateManager::createState(States::ID state)
{
	switch (state)
	{
	case States::ID::Game:
		return std::make_unique<Game>(*this, window);
		break;
	default:
		break;
	}
	return nullptr;
}

void StateManager::applyChanges()
{
	for (std::pair<Action, States::ID> &change : queue)
	{
		switch (change.first)
		{
		case Action::Push:
			stateStack.push_back(createState(change.second));
			break;
		case Action::Pop:
			stateStack.pop_back();
			break;
		case Action::Clear:
			stateStack.clear();
			break;
		default:
			break;
		}
	}

	queue.clear();
}