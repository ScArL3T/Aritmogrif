#pragma once

#define BOARD_SIZE 25

#include "Tile.h"

class Board : private sf::NonCopyable
{
public:
	explicit Board(sf::RenderWindow &window);
	~Board();

	bool getGameOver();

	void handleEvent(const sf::Event &event);
	void update();
	void draw();

private:
	void readFile();
	void placeMainWord();
	void placeWord(const std::string &string, int row);
	void checkWord(int line);
	void centerText(sf::Text &text);

	sf::RenderWindow &window;

	bool gameOver;
	char matrix[BOARD_SIZE][BOARD_SIZE];
	std::string mainWord;

	std::vector<sf::Text> text;
	std::vector<std::string> words;
	std::vector<Tile> tiles;
	Tile *selectedTile;
	sf::Font font;
	int minim, maxim;
	int CORRECT_LINES;
};

