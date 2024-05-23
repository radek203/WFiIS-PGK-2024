#include "sokoban_txt.h"
#include "sokoban_font.h"

#include <cmath>

#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <utility>

enum class Field { VOID, FLOOR, WALL, BOX, PARK, PLAYER };

class Utility {
	sf::Font main_font;
	sf::Texture main_texture;
	sf::Text main_text;
public:
	Utility(const sf::Font& font, const sf::Texture& texture, sf::Text text);
	std::map<Field, sf::Sprite> sprite_map;
	sf::Texture getMainTexture();
	sf::Font getMainFont();
	sf::Text getMainText();

	void drawTextOnCenter(sf::RenderTarget& target, std::string str);
};

class Sokoban : public sf::Drawable {
public:
	Sokoban(Utility);
	void LoadMapFromFile(std::string fileName);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void SetDrawParameters(sf::Vector2u draw_area_size);
	void Move_Player_Left();
	void Move_Player_Right();
	void Move_Player_Up();
	void Move_Player_Down();
	bool Is_Victory() const;

	void setSurrender();
	void startClock();
	bool Is_Surrender() const;
	sf::Clock getStartClock() const;
	double getTimeSaved() const;

private:
	mutable Utility utility;
	mutable double time_saved = -1;
	sf::Clock start_clock;
	bool end_surrender = false;
	std::vector<std::vector<Field>> map;
	sf::Vector2f shift;
	sf::Vector2i player_position, tile_size;
	std::vector<sf::Vector2i> park_positions;

	void move_player(int dx, int dy);
	void drawField(sf::RenderTarget& target, sf::Sprite sprite, int x, int y) const;
};

Sokoban::Sokoban(const Utility _utility) : utility(_utility) {

}

Utility::Utility(const sf::Font& font, const sf::Texture& texture, sf::Text text): main_font(font), main_texture(texture), main_text(std::move(text)) {

}

sf::Texture Utility::getMainTexture() {
	return main_texture;
}

sf::Font Utility::getMainFont() {
	return main_font;
}

sf::Text Utility::getMainText() {
	return main_text;
}

void Sokoban::LoadMapFromFile(std::string fileName) {
	std::string str;
	std::vector<std::string> vos;

	std::ifstream in(fileName.c_str());
	while (std::getline(in, str)) { vos.push_back(str); }
	in.close();

	map.clear();
	map.resize(vos.size(), std::vector<Field>(vos[0].size()));
	for (auto [row, row_end, y] = std::tuple{ vos.cbegin(), vos.cend(), 0 }; row != row_end; ++row, ++y)
	for (auto [element, end, x] = std::tuple{ row->begin(), row->end(), 0 }; element != end; ++element, ++x)
	switch (*element) {
		case 'X': map[y][x] = Field::WALL; break;
		case '*': map[y][x] = Field::VOID; break;
		case ' ': map[y][x] = Field::FLOOR; break;
		case 'B': map[y][x] = Field::BOX; break;
		case 'P': map[y][x] = Field::PARK; park_positions.push_back(sf::Vector2i(x,y));  break;
		case 'S': map[y][x] = Field::PLAYER; player_position = sf::Vector2i(x,y);  break;
	}
}

void Sokoban::startClock() {
	sf::Clock clock;
	start_clock = clock;
}

void Utility::drawTextOnCenter(sf::RenderTarget& target, std::string str) {
	main_text.setString(str);

	double textWidth = main_text.getLocalBounds().width;
	double textHeight = main_text.getLocalBounds().height;

	main_text.setPosition((target.getSize().x / 2.0) - (textWidth / 2.0), (target.getSize().y / 2.0) - (textHeight / 2.0));

	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(textWidth + 30.0,textHeight + 10.0));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(2.0f);
	rectangle.setPosition(sf::Vector2f((target.getSize().x / 2.0) - (textWidth / 2.0) - 15, (target.getSize().y / 2.0) - (textHeight / 2.0) + 5));
	target.draw(rectangle);
	target.draw(main_text);
}

void Sokoban::drawField(sf::RenderTarget& target, sf::Sprite sprite, int x, int y) const {
	float scaleX = tile_size.x / sprite.getGlobalBounds().width;
	float scaleY = tile_size.y / sprite.getGlobalBounds().height;
	sprite.setScale(scaleX, scaleY);
	sprite.setPosition(shift.x + x * tile_size.x, shift.y + y * tile_size.x);

	target.draw(sprite);
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == Field::BOX || map[y][x] == Field::PLAYER) {
				drawField(target, utility.sprite_map[Field::FLOOR], x, y);
				if (map[y][x] == Field::BOX) {
					drawField(target, utility.sprite_map[Field::BOX], x, y);
				} else if (map[y][x] == Field::PLAYER) {
					drawField(target, utility.sprite_map[Field::PLAYER], x, y);
				}
			} else {
				drawField(target, utility.sprite_map[map[y][x]], x, y);
			}
		}
	}

	if (Is_Victory()) {
		if (time_saved < 0) {
			time_saved = start_clock.getElapsedTime().asSeconds();
		}
		std::string str = "BRAWO! Twoj czas to: ";
		str.append(std::to_string((int)time_saved));
		str.append("s!");
		utility.drawTextOnCenter(target, str);
	} else if (end_surrender) {
		if (time_saved < 0) {
			time_saved = start_clock.getElapsedTime().asSeconds();
		}
		utility.drawTextOnCenter(target, "Tak latwo sie poddajesz?");
	} else {
        sf::Text text = utility.getMainText();
        std::string str = " Twoj czas: ";
        str.append(std::to_string((int)start_clock.getElapsedTime().asSeconds()));
        str.append("s");
        text.setString(str);
        text.setFillColor(sf::Color::Red);
        text.setPosition(0, 0);
        target.draw(text);
    }
}

void Sokoban::SetDrawParameters(sf::Vector2u draw_area_size) {
	this->tile_size = sf::Vector2i(
		std::min(std::floor((float)draw_area_size.x / (float)map[0].size()), std::floor((float)draw_area_size.y / (float)map.size())),
		std::min(std::floor((float)draw_area_size.x / (float)map[0].size()), std::floor((float)draw_area_size.y / (float)map.size()))
	);
	this->shift = sf::Vector2f(
		((float)draw_area_size.x - this->tile_size.x * map[0].size()) / 2.0f,
		((float)draw_area_size.y - this->tile_size.y * map.size()) / 2.0f
	);
}

void Sokoban::Move_Player_Left() {
	move_player(-1, 0);
}

void Sokoban::Move_Player_Right() {
	move_player(1, 0);
}

void Sokoban::Move_Player_Up() {
	move_player(0, -1);
}

void Sokoban::Move_Player_Down() {
	move_player(0, 1);
}

void Sokoban::move_player(int dx, int dy) {
	bool allow_move = false; // Pesymistyczne załóżmy, że gracz nie może się poruszyć.
	sf::Vector2i new_pp(player_position.x + dx,player_position.y + dy); //Potencjalna nowa pozycja gracza.
	Field fts = map[new_pp.y][new_pp.x]; //Element na miejscu na które gracz zamierza przejść.

	//Gracz może się poruszyć jeśli pole na którym ma stanąć to podłoga lub miejsce na skrzynki.
	if (fts == Field::FLOOR || fts == Field::PARK) allow_move = true;
	//Jeśli pole na które chce się poruszyć gracz zawiera skrzynkę to może się on poruszyć jedynie jeśli kolejne pole jest puste lub zawiera miejsce na skrzynkę  - bo wtedy może przepchnąć skrzynkę.
	if (fts == Field::BOX) {
		Field ftsa = map[new_pp.y + dy][new_pp.x + dx]; //Element na miejscu ZA miejscem na które gracz zamierza przejść. :-D
		if (ftsa == Field::FLOOR || ftsa == Field::PARK) {
			allow_move = true;
			//Przepychamy skrzynkę.
			map[new_pp.y + dy][new_pp.x + dx] = Field::BOX;
			//Oczywiście pole na którym stała skrzynka staje się teraz podłogą.
			map[new_pp.y][new_pp.x] = Field::FLOOR;
		}
	}

	if (allow_move) {
		//Przesuwamy gracza.
		map[player_position.y][player_position.x] = Field::FLOOR;
		player_position = new_pp;
		map[player_position.y][player_position.x] = Field::PLAYER;
	}

	//Niestety w czasie ruchu mogły „ucierpieć” miejsca na skrzynkę. ;-(
	for (auto park_position : park_positions) if (map[park_position.y][park_position.x] == Field::FLOOR) map[park_position.y][park_position.x] = Field::PARK;
}

bool Sokoban::Is_Victory() const
{
//Tym razem dla odmiany optymistycznie zakładamy, że gracz wygrał.
//No ale jeśli na którymkolwiek miejscu na skrzynki nie ma skrzynki to chyba założenie było zbyt optymistyczne... : -/
	for (auto park_position : park_positions) if (map[park_position.y][park_position.x] != Field::BOX) return false;
	return true;
}

void Sokoban::setSurrender() {
	end_surrender = true;
}


bool Sokoban::Is_Surrender() const {
	return end_surrender;
}

sf::Clock Sokoban::getStartClock() const {
	return start_clock;
}

double Sokoban::getTimeSaved() const {
	return time_saved;
}

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16.0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize, settings);
	sf::Texture texture;
	texture.setSmooth(true);
    texture.loadFromMemory(&(sokoban_texture[0]), sokoban_texture.size());

	sf::Font font;
	font.loadFromMemory(&(sokoban_font[0]), sokoban_font.size());

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color::White);

	Utility utility(font, texture, text);

	sf::IntRect rectSourceSprite = sf::IntRect(0, 0, 64, 64);
	sf::Sprite sprite = sf::Sprite(texture, rectSourceSprite);
	utility.sprite_map[Field::WALL] = sprite;

	rectSourceSprite = sf::IntRect(234, 0, 64, 64);
	sprite = sf::Sprite(texture, rectSourceSprite);
	utility.sprite_map[Field::FLOOR] = sprite;

	rectSourceSprite = sf::IntRect(128, 0, 64, 64);
	sprite = sf::Sprite(texture, rectSourceSprite);
	utility.sprite_map[Field::PARK] = sprite;

	rectSourceSprite = sf::IntRect(64, 0, 64, 64);
	sprite = sf::Sprite(texture, rectSourceSprite);
	utility.sprite_map[Field::BOX] = sprite;

	rectSourceSprite = sf::IntRect(192, 0, 42, 50);
	sprite = sf::Sprite(texture, rectSourceSprite);
	utility.sprite_map[Field::PLAYER] = sprite;

	rectSourceSprite = sf::IntRect(298, 0, 64, 64);
	sprite = sf::Sprite(texture, rectSourceSprite);
	utility.sprite_map[Field::VOID] = sprite;

	Sokoban sokoban(utility);

	sokoban.LoadMapFromFile("plansza.txt");
	sokoban.SetDrawParameters(window.getSize());

	sokoban.startClock();

	//window.setFramerateLimit(540);
	//window.setVerticalSyncEnabled(true);
	while (window.isOpen()) {
		window.clear(sf::Color::Black);
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {
				float width = static_cast<float>(event.size.width);
				float height = static_cast<float>(event.size.height);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				sokoban.SetDrawParameters(window.getSize());
			}
			if (sokoban.Is_Surrender()) {
				continue;
			}
			if (sokoban.Is_Victory()) {
				continue;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) sokoban.Move_Player_Left();
				if (event.key.code == sf::Keyboard::Right) sokoban.Move_Player_Right();
				if (event.key.code == sf::Keyboard::Up) sokoban.Move_Player_Up();
				if (event.key.code == sf::Keyboard::Down) sokoban.Move_Player_Down();
				if (event.key.code == sf::Keyboard::Escape) sokoban.setSurrender();
			}
		}
		if ((sokoban.Is_Surrender() || sokoban.Is_Victory()) && sokoban.getTimeSaved() > 0 && sokoban.getStartClock().getElapsedTime().asSeconds() - sokoban.getTimeSaved() >= 3) {
			window.close();
		}
		window.draw(sokoban);
		window.display();
	}

	return 0;
}