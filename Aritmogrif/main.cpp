#include <iostream>
#include <SFML/Graphics.hpp>

#include "StateManager.h"

using namespace std;

int main()
{
	sf::RenderWindow window;
	window.create({ 880, 440 }, "Aritmogrif");
	window.setFramerateLimit(60); // cpu usage

	StateManager manager(window);
	manager.pushState(States::ID::Game);

	const sf::Time gameTime = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time passedTime = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		passedTime += elapsedTime;

		while (passedTime > gameTime)
		{
			passedTime -= gameTime;

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				manager.handleEvent(event);
			}
			manager.update(gameTime);
		}

		window.clear(sf::Color(210, 210, 210)); // GREY
		manager.draw();
		window.display();
	}

	return 0;
}