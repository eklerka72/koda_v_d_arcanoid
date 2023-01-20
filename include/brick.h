/*!
\file
\brief Заголовочный файл с описанием класса Brick
Данный файл содержит в себе определение класса Brick
*/

/*!
\brief Класс для разработки сбиваемого блока
*/

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
	/*!
	\brief Метод для получения глобального прямоугольника, ограничивающего объект
	*/
	sf::FloatRect getGlobalBounds()
	{
		return _brick.getGlobalBounds();
	}
	/*!
	\brief Метод, показывающий. что произошел удар по блоку
	*/
	void hit()
	{
		this->resistance -= 1;
		if (this->resistance <= 0)
			this->destroyed = true;
	}
	/*!
    \brief Метод для получения позиции по х
    */
	int  getX()
	{
		return _brick.getPosition().x;
	}
	/*!
	\brief Метод для получения позиции по у
	*/
	int  getY()
	{
		return _brick.getPosition().y;
	}
	/*!
	\brief Метод для получения размера по х
	*/
	int getSizeX()
	{
		return _brick.getSize().x;
	}
	/*!
	\brief Метод для получения размера по у
	*/
	int getSizeY()
	{
		return _brick.getSize().y;
	}
	/*!
	\brief Метод для определения сопротивления (количества оставшихся жизней блока)
	*/
	void setResistance()
	{
		if (this->resistance < 3)
			this->resistance += 1;
		else
			this->resistance = 0;
	}
	/*!
	\brief Метод для обновления цвета блока в зависмости от сопротивления
	*/
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
	/*!
	\brief Метод для определения уничтожен ли блок
	*/
	bool isDestroy()
	{
		if (this->destroyed)
			return true;
		if (!this->destroyed)
			return false;
	}
	/*!
	\brief Метод, возвращающий сопротивления блока
	*/
	int getResistance()
	{
		return this->resistance;
	}
	/*!
	\brief Метод, возвращающий количество баллов
	*/
	int getPoints()
	{
		return this->points;
	}
	/*!
	\brief Метод для рисования блока в окне
	*/
	void draw(sf::RenderWindow& window)
	{
		window.draw(_brick);
	}

};