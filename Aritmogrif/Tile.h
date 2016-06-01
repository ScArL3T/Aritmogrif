#pragma once

#include <SFML/Graphics.hpp>

class Tile final : public sf::Drawable, public sf::Transformable
{
public:
	enum class State
	{
		None = 0,
		Selected,
		Fixed
	};

	explicit Tile(const sf::Font &font);
	~Tile();

	void centerText();

	bool isMouseOver(const sf::Vector2i mouse);
	const State getState() const;
	const sf::Vector2i getMatrixPos() const;
	const char getCharacter() const;

	void setMatrixPos(const sf::Vector2i pos);
	void setState(Tile::State newState);
	void setColor(const sf::Color color);
	void setCharacter(const char c);

private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Vector2f	   size;
	sf::RectangleShape shape;

	sf::Vector2i matrixPos;

	sf::Text letter;

	State state;
};

