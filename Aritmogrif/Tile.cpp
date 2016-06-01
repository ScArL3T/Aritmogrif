#include "Tile.h"


Tile::Tile(const sf::Font &font)
	: size(30, 30)
	, letter("", font, 20)
	, state(State::None)
	, matrixPos(0, 0)
{
	shape.setSize(size);
	shape.setFillColor(sf::Color(190, 190, 190));

	letter.setColor(sf::Color::Red);
}


Tile::~Tile()
{
}

void Tile::centerText()
{
	//Set the position
	sf::FloatRect rect = letter.getLocalBounds();
	letter.setOrigin(rect.left, rect.top);
	letter.setPosition({ size.x / 2 - rect.width / 2,
		size.y / 2 - rect.height / 2 });
}

bool Tile::isMouseOver(sf::Vector2i mouse)
{
	sf::FloatRect bounds(getPosition().x, getPosition().y, size.x, size.y);
	return bounds.contains(static_cast<sf::Vector2f>(mouse));
}

const Tile::State Tile::getState() const
{
	return state;
}

const sf::Vector2i Tile::getMatrixPos() const
{
	return matrixPos;
}

const char Tile::getCharacter() const
{
	return letter.getString()[0];
}

void Tile::setMatrixPos(const sf::Vector2i pos)
{
	matrixPos = pos;
}

void Tile::setState(Tile::State newState)
{
	state = newState;

	if (state == Tile::State::Fixed)
		letter.setColor(sf::Color::Black);
}

void Tile::setColor(const sf::Color color)
{
	shape.setFillColor(color);
}

void Tile::setCharacter(const char c)
{
	letter.setString(c);
	centerText();
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape, states);
	target.draw(letter, states);
}
