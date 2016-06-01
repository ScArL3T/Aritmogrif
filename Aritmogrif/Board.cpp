#include "Board.h"

#include <fstream>
#include <iostream>

Board::Board(sf::RenderWindow &window)
	: window(window)
	, gameOver(false)
	, matrix()
	, minim(BOARD_SIZE)
	, maxim(0)
	, selectedTile(nullptr)
	, CORRECT_LINES(0)
{
	font.loadFromFile("font.ttf");

	readFile();

	for (unsigned int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
	{
		int row, column;
		row = i / BOARD_SIZE; column = i % BOARD_SIZE;

		if (matrix[row][column] != '\0')
		{
			tiles.emplace_back(font);
			tiles.back().setPosition({ static_cast<float>((column - minim) * 32 + 2 * (column - minim)), static_cast<float>(row * 32 + 2 * row) });
			tiles.back().setMatrixPos({ row, column });

			if (column == BOARD_SIZE / 2)
			{
				tiles.back().setState(Tile::State::Fixed);
				tiles.back().setCharacter(matrix[row][column]);
			}
		}
	}

	for (unsigned int i = 0; i < mainWord.length(); i++)
	{
		text[i].setFont(font);
		text[i].setColor(sf::Color::Black);
		text[i].setCharacterSize(15);
		centerText(text[i]);
		text[i].setPosition({ static_cast<float>(window.getSize().y / 2 + 270), static_cast<float>(i * 32 + 2 * i) });
	}
}


Board::~Board()
{
}

bool Board::getGameOver()
{
	return gameOver;
}

void Board::handleEvent(const sf::Event &event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		for (auto &tile : tiles)
		{
			if (tile.getState() == Tile::State::None)
			{
				if (tile.isMouseOver(mousePos))
					tile.setColor(sf::Color(230, 230, 230));
				else tile.setColor(sf::Color(190, 190, 190));
			}
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			int ok = 1;
			for (auto &tile : tiles)
			{
				if (tile.isMouseOver(mousePos))
				{
					ok = 0;
					if (tile.getState() == Tile::State::None)
					{
						if (selectedTile)
						{
							selectedTile->setState(Tile::State::None);
							selectedTile->setColor(sf::Color(190, 190, 190));
						}

						tile.setState(Tile::State::Selected);
						tile.setColor(sf::Color::Green);
						selectedTile = &tile;
					}
					else if (tile.getState() == Tile::State::Selected)
					{
						tile.setState(Tile::State::None);
						tile.setColor(sf::Color(190, 190, 190));
						selectedTile = nullptr;
					}
				}
			}
			if (ok && selectedTile)
			{
				selectedTile->setState(Tile::State::None);
				selectedTile->setColor(sf::Color(190, 190, 190));
				selectedTile = nullptr;
			}
		}
		break;
	case sf::Event::TextEntered:
		if (selectedTile)
		{
			if (((event.text.unicode >= 'A') && (event.text.unicode <= 'Z'))
				|| ((event.text.unicode >= 'a') && (event.text.unicode <= 'z')))
			{
				char c = static_cast<char>(event.text.unicode);
				if (c >= 'a' && c <= 'z') c -= 32;

				selectedTile->setCharacter(c);
				checkWord(selectedTile->getMatrixPos().x);
			}
		}
		break;
	default:
		break;
	}
}

void Board::update()
{
	if (CORRECT_LINES == mainWord.length())
		gameOver = true;
}

void Board::draw()
{
	for (const auto &tile : tiles)
		window.draw(tile);

	for (const auto &t : text)
		window.draw(t);
}

void Board::readFile()
{
	using namespace std;
	ifstream fin("aritmogrif.txt");

	fin >> mainWord;
	placeMainWord();

	for (int i = 0; i < mainWord.length(); i++)
	{
		std::string word;
		fin >> word;

		words.push_back(word);

		std::string descr;
		getline(fin, descr);

		sf::Text temp;
		temp.setString(descr);
		text.push_back(temp);

		placeWord(word, i);
	}

	fin.close();
}

void Board::placeMainWord()
{
	for (int i = 0; i < mainWord.length(); i++)
	{
		matrix[i][BOARD_SIZE / 2] = mainWord[i];
	}
}

void Board::placeWord(const std::string &string, int row)
{
	int pos = 0;
	for (int i = 0; i < string.length(); i++)
	{
		if (string[i] == mainWord[row])
		{
			pos = i;
			if (BOARD_SIZE / 2 - pos < minim)
				minim = BOARD_SIZE / 2 - pos;

			if (BOARD_SIZE / 2 + string.length() - pos - 1> maxim)
				maxim = BOARD_SIZE / 2 + string.length() - pos - 1;

			break;
		}
	}

	for (int i = 0; i < pos; i++)
	{
		matrix[row][BOARD_SIZE / 2 - pos + i] = string[i];
	}

	for (int i = pos + 1; i < string.length(); i++)
	{
		matrix[row][BOARD_SIZE / 2 - pos + i] = string[i];
	}
}

void Board::checkWord(int line)
{
	int i = 0, ok = 1;
	while (matrix[line][i] == '\0')
		i++;

	sf::Vector2i pos(line, i);
	
	while (matrix[line][pos.y])
	{
		for (auto &tile : tiles)
		{
			if (tile.getMatrixPos() == pos)
			{
				if (tile.getCharacter() == matrix[line][pos.y])
					break;
				else return;
			}
		}
		pos.y++;
	}

	pos.y = i;
	selectedTile = nullptr;

	while (matrix[line][pos.y])
	{
		for (auto &tile : tiles)
		{
			if (tile.getMatrixPos() == pos)
			{
				tile.setState(Tile::State::Fixed);
				tile.setColor(sf::Color::Green);
			}
		}
		pos.y++;
	}

	CORRECT_LINES++;
}

void Board::centerText(sf::Text &text)
{
	//Set the position
	sf::FloatRect rect = text.getLocalBounds();
	text.setOrigin(rect.left, rect.top - 10);
}