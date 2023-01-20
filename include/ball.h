/**
\mainpage Игра Арканоид


Принцип работы программы:
 - Программа работает при помощи библиотеки SFML
 - Движение и взаимодействие каждого эелемента прописано в отдельных классах: ball.h, brick.h, player.h, powerup.h, wall.h


 Разработала: Кода Валерия Дмитриевна. Студентка 2-го курса группы БПМ-21-2
 */
/*!
\file
\brief Заголовочный файл с описанием класса Ball
Данный файл содержит в себе определение класса Ball
*/

/*!
\brief Класс для разработки летающего шара
*/
class Ball {
private:
	short original_speed = 0;
	short speed = 0;
	double angle = 2.00;
	float time = 0.05;
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
	/*!
	\brief Метод для получения позиции по х
	*/
	int getX()
	{
		return _ball.getPosition().x;
	}
	/*!
	\brief Метод для получения позиции по у
	*/
	int getY()
	{
		return _ball.getPosition().y;
	}
	/*!
	\brief Метод для перемещения шара
	*/
	void move()
	{
		_ball.setPosition(_ball.getPosition().x + this->angle * time, _ball.getPosition().y - this->speed * time);
	}
	/*!
	\brief Метод для получения глобального прямоугольника, ограничивающего объект
	*/
	sf::FloatRect getGlobalBounds()
	{
		return _ball.getGlobalBounds();
	}
	/*!
	\brief Метод для отпрыгивания шара
	*/
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
	/*!
	\brief Метод для установки позиции
	*/
	void setPosition(int x, int y)
	{
		_ball.setPosition(x, y);
	}
	/*!
	\brief Метод для отпрыгивания шара от стены
	*/
	void wall_bounce()
	{
		this->angle = -this->angle;
	}
	/*!
	\brief Метод для обнуления угла
	*/
	void resetAngle()
	{
		this->angle = 0;
	}
	/*!
	\brief Метод для возвращения скорости к начальному значению
	*/
	void resetSpeed()
	{
		this->time = 0.05;
	}
	/*!
	\brief Метод для изменения цвета шара на мигающий
	*/
	void blink()
	{
		_ball.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
	}
	/*!
	\brief Метод для увеличения скорости
	*/
	void increaseSpeed()
	{
		this->time += 0.005;
	}
	/*!
	\brief Метод для уменьшения скорости
	*/
	void decreaseSpeed()
	{
		if (this->time > 0.005)
			this->time -= 0.005;
	}
	/*!
	\brief Метод для возращения белого цвета
	*/
	void resetColor()
	{
		_ball.setFillColor(sf::Color::White);
	}
	/*!
	\brief Метод для рисования шара в окне
	*/
	void draw(sf::RenderWindow& window)
	{
		window.draw(_ball);
	}
};