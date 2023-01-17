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
			double ex = rand() % 3 + 1;
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