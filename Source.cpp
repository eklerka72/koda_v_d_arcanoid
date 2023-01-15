#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include<fstream>
#include<math.h>
//#include<vector>
#include<ctime>
#include<string.h>
#include <sstream>
#include<stdio.h>

#define WIDTH 600
#define HEIGHT 600


class Player {

private:
	int orig_w = 0;
	int w = 0;
	int h = 0;
	int x = 0;
	int y = 0;
	short vel = 35;
	sf::RectangleShape _player;


public:
	Player(int w, int h, int x, int y)
	{
		this->orig_w = w;
		this->w = w;
		this->h = h;
		this->x = x;
		this->y = y;
		_player.setSize(sf::Vector2f(this->w, this->h));
		_player.setPosition(x, y);

	}
	int getX()
	{
		return _player.getPosition().x;
	}
	int getY()
	{
		return _player.getPosition().y;
	}
	int getW() 
	{
		return this->w;
	}
	void moveLeft()
	{
		_player.move(0 - this->vel * 0.012, 0);//?
	}
	sf::FloatRect getGlobalBounds()
	{
		return _player.getGlobalBounds();//?
	}
	void moveRight()
	{
		_player.move(0 + this->vel * 0.012, 0);
	}
	void grow()
	{
		_player.setSize(sf::Vector2f( this->w += 10, this->h));
	}
	void shrink()
	{
		if (this-> w > 10)
			_player.setSize(sf::Vector2f(this->w -= 10, this->h));
	}
	void increaseSpeed() 
	{
		this->vel += 10;
	}
	void decreaseSpeed()
	{
		if (this->vel > 10)
			this->vel -= 10;
	}
	void resetSpeed() {
		this->vel = 35;
	}
	void reset_w()
	{
		this->w = this->orig_w;
		_player.setSize(sf::Vector2f(this->w, this->h));
	}
	void resetPosition()
	{
		_player.setPosition(this->x, this->y);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(_player);
	}
};
class Ball {
private:
	short original_speed = 0;
	short speed = 0;
	double angle = 2.00;
	float time = 0.07;
	sf::CircleShape _ball;

public:
	Ball(int radius, int x, int y, short speed)
	{
		_ball.setRadius(radius);
		_ball.setPosition(x, y);
		_ball.setOutlineColor(sf::Color::Black);
		_ball.setOutlineThickness(1);
		this->original_speed = speed;
		this->speed = speed;
	}
	int getX()
	{
		return _ball.getPosition().x;
	}
	int getY()
	{
		return _ball.getPosition().y;
	}
	void move()
	{
		_ball.setPosition(_ball.getPosition().x + this->angle * time, _ball.getPosition().y - this->speed * time);
	}
	sf::FloatRect getGlobalBounds()
	{
		return _ball.getGlobalBounds();
	}
	void bounce()
	{
		if (_ball.getPosition().y <= 10)
		{
			this->original_speed = -this->original_speed;
			this->speed = this->original_speed;
		}
		else
		{
			double ex = rand() % 4 + 1;
			if (this->angle >= 0)
				this->angle = ex;
			else if (this->angle <= 0)
				this->angle = -ex;
			this->original_speed = -this->original_speed;
			this->speed = this->original_speed;
		}
	}
	void setPosition(int x, int y)
	{
		_ball.setPosition(x, y);
	}
	void wall_bounce()
	{
		this->angle = -this->angle;
	}
	void resetAngle()
	{
		this->angle = 0;
	}
	void resetSpeed()
	{
		this->time = 0.07;
	}
	void blink() 
	{
		_ball.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
	}
	void increaseSpeed()
	{
		this->time += 0.01;
	}
	void decreaseSpeed()
	{
		if (this->time > 0.01)
			this->time -= 0.01;
	}
	void resetColor()
	{
		_ball.setFillColor(sf::Color::White);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(_ball);
	}
};
class Brick {
private:
	short points = 0;
	short resistance = 0;
	bool destroyed = false;
	sf::RectangleShape _brick;
public:
	Brick(int widht, int hight, int x, int y, short resistance)
	{
		_brick.setSize(sf::Vector2f(widht, hight));
		_brick.setPosition(x, y);
		this->resistance = resistance;
		_brick.setOutlineColor(sf::Color::Black);
		_brick.setOutlineThickness(1);

		if (this->resistance == 0)
		{
			_brick.setFillColor(sf::Color::Black);
			_brick.setOutlineColor(sf::Color::White);
			_brick.setOutlineThickness(1);
		}

		if (this->resistance == 1)
		{
			_brick.setFillColor(sf::Color::Green);
			this->points = 1;
		}

		if (this->resistance == 2)
		{
			_brick.setFillColor(sf::Color::Blue);
			this->points = 2;
		}

		if (this->resistance == 3)
		{
			_brick.setFillColor(sf::Color::Red);
			this->points = 3;
		}
	}

	sf::FloatRect getGlobalBounds()
	{
		return _brick.getGlobalBounds();
	}
	void hit()
	{
		this->resistance -= 1;
		if (this->resistance <= 0)
			this->destroyed = true;
	}
	int  getX()
	{
		return _brick.getPosition().x;
	}
	int  getY()
	{
		return _brick.getPosition().y;
	}
	int getSizeX()
	{
		return _brick.getSize().x;
	}
	int getSizeY()
	{
		return _brick.getSize().y;
	}
	void setResistance()
	{
		if (this->resistance < 3)
			this->resistance += 1;
		else
			this->resistance = 0;
	}
	void updateStatus()
	{
		if (this->resistance == 3)
			_brick.setFillColor(sf::Color::Red);
		if (this->resistance == 2)
			_brick.setFillColor(sf::Color::Blue);
		if (this->resistance == 1)
			_brick.setFillColor(sf::Color::Green);
		if (this->resistance == 0)
		{
			_brick.setFillColor(sf::Color::Black);
			_brick.setOutlineColor(sf::Color::White);
			_brick.setOutlineThickness(1);
		}
	}
	bool isDestroy()
	{
		if (this->destroyed)
			return true;
		if (!this->destroyed)
			return false;
	}
	int getResistance()
	{
		return this->resistance;
	}
	int getPoints()
	{
		return this->points;
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(_brick);
	}
	
};
class Wall {
private:
	int w = 580;
	int h = 220;
	std::vector<Brick> bricks;
	short tot_bricks = 0;

public:
	void generateLevel()
	{
		for (int y = 50; y < this->h; y += 20)
		{
			for (int x = 20; x < this->w; x += 60)
			{
				if (rand() % 10 < 3)
				{
					Brick b(40, 10, x, y, rand() % 3 + 1);
					this->bricks.push_back(b);
					this->tot_bricks += 1;
				}
			}
		}
	}
	void generateGrid()
	{
		for (int y = 50; y < this->h; y += 20)
		{
			for (int x = 20; x < this->w; x += 60)
			{
				Brick b(40, 10, x, y, 0);
				this->bricks.push_back(b);
			}
		}
	}
	void checkCollisions(Ball& palla, int power_type)
	{
		for (auto& Brick : this->bricks)
			if (Brick.getGlobalBounds().intersects(palla.getGlobalBounds()))
			{
				Brick.hit();
				if (power_type != 1)
					palla.bounce();
				Brick.updateStatus();
			}
	}
	void removeDestroyed(unsigned int& player_score)
	{
		for (auto Brick = this->bricks.begin(); Brick != bricks.end(); ++Brick)
		{
			if ((*Brick).isDestroy())
			{
				player_score += (*Brick).getPoints();
				this->bricks.erase(Brick--);//?
				this->tot_bricks--;
			}
		}
	}
	std::vector<Brick> getBricksVector()
	{
		return this->bricks;
	}
	int get_total_bricks()
	{
		return this->tot_bricks;
	}
	void setBricksVector(std::vector<Brick> bv)
	{
		this->bricks = bv;
	}
	void clear()
	{
		this->bricks.clear();
	}
	void count_total_bricks()
	{
		for (auto& Brick : this->bricks)
			if (Brick.getResistance() != 0)
				this->tot_bricks += 1;
	}
	void reset_total_bricks()
	{
		this->tot_bricks = 0;
	}
	void draw(sf::RenderWindow& window)
	{
		for (auto& Brick : this->bricks)
			Brick.draw(window);
	}
};
class Powerup {
private:
	int type = 0;
	bool _take = 0;
	sf::Sprite _power;
public:
	Powerup(sf::Texture& texture, int type)
	{
		_power.setScale(_power.getScale().x / 20, _power.getScale().y / 20);
		_power.setTexture(texture);
		this->type = type;
	}
	void setPosition(int x, int y)
	{
		_power.setPosition(x, y);
	}
	void move() 
	{
		_power.move(0, 0 + 2 * 0.09);
	}
	int getType()
	{
		return this->type;
	}
	sf::FloatRect getGlobalBounds()
	{
		return _power.getGlobalBounds();
	}
	void take()
	{
		this->_take = 1;
	}
	bool isTake()
	{
		return this->_take;
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(_power);
	}
};



bool moveL = false;
bool moveR = false;

unsigned int player_score = 0;
short player_lives = 3;

bool start = true;
bool pause = false;
bool win = false;
bool loose = false;

sf::Clock chrono;

int tot_bricks = 0;
short power_type = 0;

std::vector<std::string> attributes;

int highScoreIO(std::string hscore, unsigned int score = 0, bool mode = 0)
{
	std::string Hscore;
	std::fstream fhandler;
	fhandler.open("HSCORE.txt", std::ios::out | std::ios::in);

	if (!mode && fhandler)
	{
		getline(fhandler, Hscore);
		//return Hscore;
	}
	if (mode)
		fhandler << score;

	fhandler.close();

	std::stringstream str(Hscore);
	int temp;
	str >> temp;
	return temp;
}
void load(std::vector<std::string>& attributes, std::vector<Brick>& bricks, std::string lv)
{
	int x = 0;
	int y = 0;
	int resistance = 0;

	std::ifstream loader(lv);
	std::string line;
	std::string delimiter = ",";
	char* current;

	while (getline(loader, line))
	{
		current = strtok((char*)line.c_str(), delimiter.c_str());
		while (current != NULL)
		{
			attributes.push_back(current);
			current = strtok(NULL, delimiter.c_str());
		}
	}

	loader.close();

	for (auto attribute = attributes.begin(); attribute != attributes.end(); ++attribute)
	{
		x = stoi(*attribute);
		attribute++;
		y = stoi(*attribute);
		attribute++;
		resistance = stoi(*attribute);

		Brick b(40, 10, x, y, resistance);
		bricks.push_back(b);
	}

}

void restart(bool& start, Ball& palla)
{
	start = false;
	palla.setPosition(WIDTH / 2, HEIGHT / 2 - 50);
	palla.resetAngle();
	palla.resetSpeed();
}

void generatePowers(std::vector<Powerup>& powers,
	sf::Texture& texture1,
	sf::Texture& texture2,
	sf::Texture& texture3,
	sf::Texture& texture4,
	sf::Texture& texture5,
	sf::Texture& texture6,
	sf::Texture& texture7,
	sf::Texture& texture8,
	sf::Texture& texture9,
	sf::Texture& texture10)
{
	if (rand() % 100000 == 0)
	{
		Powerup pow(texture1, 1);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 100000 == 1)
	{
		Powerup pow(texture2, 2);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 100000 == 2)
	{
		Powerup pow(texture3, 3);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 1000000 == 3)
	{
		Powerup pow(texture4, 4);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 100000 == 4)
	{
		Powerup pow(texture5, 5);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 100000 == 5)
	{
		Powerup pow(texture6, 6);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 100000 == 6)
	{
		Powerup pow(texture7, 7);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 500000 == 7)
	{
		Powerup pow(texture8, 8);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 100000 == 8)
	{
		Powerup pow(texture9, 9);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

	if (rand() % 100000 == 9)
	{
		Powerup pow(texture10, 10);
		pow.setPosition(rand() % (WIDTH - 50) + 1, rand() % HEIGHT / 2 + 1);
		powers.push_back(pow);
	}

}

int main(int argc, char** argv)
{

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "ARKANOID");
	srand(time(nullptr));

	sf::Font atari;
	atari.loadFromFile("font/AtariST8x16SystemFont.ttf");

	sf::Text hscore_ui;
	hscore_ui.setFont(atari);

	sf::Text hscore_txt;
	hscore_txt.setFont(atari);

	sf::Text score_txt;
	score_txt.setFont(atari);

	sf::Text score;
	score.setFont(atari);

	sf::Text lives_txt;
	lives_txt.setFont(atari);

	sf::Text lives;
	lives.setFont(atari);

	sf::Text end_msg;
	end_msg.setFont(atari);

	sf::Text press_space;
	press_space.setFont(atari);

	sf::Text pause;
	pause.setFont(atari);
	pause.setString("Pausa");
	pause.setPosition(WIDTH / 2 - 25, HEIGHT / 2);
	pause.setFillColor(sf::Color::White);

	sf::Texture pow1_texture;
	pow1_texture.loadFromFile("powers/power1.png");

	sf::Texture pow2_texture;
	pow2_texture.loadFromFile("powers/power2.png");

	sf::Texture pow3_texture;
	pow3_texture.loadFromFile("powers/power3.png");

	sf::Texture pow4_texture;
	pow4_texture.loadFromFile("powers/power4.png");

	sf::Texture pow5_texture;
	pow5_texture.loadFromFile("powers/power5.png");

	sf::Texture pow6_texture;
	pow6_texture.loadFromFile("powers/power6.png");

	sf::Texture pow7_texture;
	pow7_texture.loadFromFile("powers/power7.png");

	sf::Texture pow8_texture;
	pow8_texture.loadFromFile("powers/power8.png");

	sf::Texture pow9_texture;
	pow9_texture.loadFromFile("powers/power9.png");

	sf::Texture pow10_texture;
	pow10_texture.loadFromFile("powers/power10.png");

	hscore_txt.setString("H-SCORE");
	hscore_txt.setPosition(10, 5);
	hscore_txt.setCharacterSize(25);
	hscore_txt.setFillColor(sf::Color::Yellow);

	hscore_ui.setPosition(35, 28);
	hscore_ui.setFillColor(sf::Color::Red);
	hscore_ui.setCharacterSize(20);
	hscore_ui.setString(std::to_string(highScoreIO("HSCORE")));

	score_txt.setString("SCORE");
	score_txt.setPosition(WIDTH / 2, 5);
	score_txt.setCharacterSize(25);
	score_txt.setFillColor(sf::Color::White);

	score.setPosition(WIDTH / 2 + 25, 28);
	score.setCharacterSize(20);
	score.setFillColor(sf::Color::White);

	lives_txt.setString("PLAYER");
	lives_txt.setPosition(WIDTH - 100, 5);
	lives_txt.setCharacterSize(25);
	lives_txt.setFillColor(sf::Color::White);

	lives.setPosition(WIDTH - 100, 28);
	lives.setCharacterSize(20);
	lives.setFillColor(sf::Color::White);


	end_msg.setPosition(WIDTH / 2 - 75, HEIGHT / 2 - 100);
	end_msg.setCharacterSize(35);
	end_msg.setFillColor(sf::Color::White);

	press_space.setPosition(WIDTH / 2 - 200, HEIGHT / 2);
	press_space.setCharacterSize(35);
	press_space.setFillColor(sf::Color::Red);

	std::vector<Powerup> powers;

	Player p1(70, 10, WIDTH / 2, HEIGHT - 20);
	Ball palla(5, WIDTH / 2, (HEIGHT / 2) + 50, 4);
	Wall theWall;


	if (argv[1] && std::string(argv[1]) == "-load")
	{
		std::vector<Brick> wallMap = theWall.getBricksVector();
		std::string lv = argv[2];
		load(attributes, wallMap, lv);
		theWall.setBricksVector(wallMap);
		theWall.count_total_bricks();
		wallMap.clear();
	}

	else theWall.generateLevel();


	while (window.isOpen())
	{
		tot_bricks = theWall.get_total_bricks();

		if (player_lives == 0) 
			loose = true;
		if (tot_bricks == 0) 
			win = true;

		if (start)
			generatePowers(powers, pow1_texture, pow2_texture, pow3_texture, pow4_texture, pow5_texture, pow6_texture, pow7_texture, pow8_texture, pow9_texture, pow10_texture);

		if (chrono.getElapsedTime().asSeconds() < 5 && power_type != 4)
		{
			if (power_type == 1)
			{
				palla.blink();
			}

			if (power_type == 2)
			{
				p1.grow();
				power_type = 0;
				palla.resetColor();
			}

			if (power_type == 3)
			{
				p1.shrink();
				power_type = 0;
				palla.resetColor();
			}

			if (power_type == 5)
			{
				palla.increaseSpeed();
				palla.resetColor();
				power_type = 0;
			}

			if (power_type == 6)
			{
				palla.decreaseSpeed();
				palla.resetColor();
				power_type = 0;
			}

			if (power_type == 7)
			{
				player_lives += 1;
				palla.resetColor();
				power_type = 0;
			}

			if (power_type == 8)
			{
				player_lives -= 1;
				palla.resetColor();
				power_type = 0;
			}

			if (power_type == 9)
			{
				p1.increaseSpeed();
				palla.resetColor();
				power_type = 0;
			}

			if (power_type == 10)
			{
				p1.decreaseSpeed();
				palla.resetColor();
				power_type = 0;
			}
		}

		else
		{
			power_type = 0;
			palla.resetColor();
		}



		if (!loose && !win)
		{
			score.setString(std::to_string(player_score));
			lives.setString(std::to_string(player_lives));


			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) 
					window.close();

				if (event.type == sf::Event::KeyReleased)
				{
					if (sf::Keyboard::Left) 
						moveL = false;
					if (sf::Keyboard::Right) 
						moveR = false;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
					moveL = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
					moveR = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
					start = true;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					start = false;
			}

			if (start) 
				palla.move();

			theWall.checkCollisions(palla, power_type);
			theWall.removeDestroyed(player_score);

			for (auto power = powers.begin(); power != powers.end(); ++power)
			{
				if ((*power).isTake())
				{
					powers.erase(power--);
				}
			}


			if (start) 
				for (auto& power : powers) 
					power.move();

			for (auto& power : powers)
			{
				if (power.getGlobalBounds().intersects(p1.getGlobalBounds()))
				{
					chrono.restart();
					power.take();
					power_type = power.getType();
				}
			}


			if (palla.getX() <= 0 || palla.getX() >= WIDTH - 20) 
				palla.wall_bounce();
			if (palla.getY() <= 0) 			 
				palla.bounce(); 

			if (palla.getGlobalBounds().intersects(p1.getGlobalBounds())) 
				palla.bounce();
			if (palla.getY() > HEIGHT)
			{
				player_lives -= 1;
				restart(start, palla);
			}

			if (moveL && p1.getX() > 0 && start) p1.moveLeft();
			if (moveR && p1.getX() < WIDTH - p1.getW() && start) p1.moveRight();


			window.clear();

			window.draw(hscore_txt);
			window.draw(hscore_ui);
			window.draw(score_txt);
			window.draw(score);
			window.draw(lives_txt);
			window.draw(lives);
			theWall.draw(window);
			for (auto& power : powers) power.draw(window);
			p1.draw(window);
			palla.draw(window);
			if (!start) window.draw(pause);


			window.display();

		}

		if (loose)
		{
			end_msg.setString("GAME OVER");
			press_space.setString("PRESS SPACE TO RESTART");

			if (player_score > highScoreIO("HSCORE")) highScoreIO("HSCORE", player_score, 1);

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					player_lives = 3;
					player_score = 0;
					hscore_ui.setString(std::to_string(highScoreIO("HSCORE")));
					loose = false;
					theWall.clear();
					powers.clear();
					theWall.reset_total_bricks();
					power_type = 0;
					p1.reset_w();
					p1.resetPosition();
					p1.resetSpeed();
					theWall.generateLevel();
					restart(start, palla);

				}
			}

			window.clear();
			window.draw(end_msg);
			if (chrono.getElapsedTime().asSeconds() > 1) window.draw(press_space);
			if (chrono.getElapsedTime().asSeconds() > 2) chrono.restart();
			window.display();

		}

		if (win)
		{
			end_msg.setString("YOU WIN");
			press_space.setString("PRESS SPACE TO CONTINUE");

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) window.close();

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					win = false;
					theWall.clear();
					powers.clear();
					theWall.reset_total_bricks();
					theWall.generateLevel();
					p1.reset_w();
					p1.resetPosition();
					p1.resetSpeed();
					power_type = 0;
					restart(start, palla);
				}

			}

			window.clear();
			window.draw(end_msg);
			window.draw(press_space);
			window.display();

		}
	}
	return 0;
}




