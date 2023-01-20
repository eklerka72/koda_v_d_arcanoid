/*!
\file
\brief Заголовочный файл с описанием класса Player
Данный файл содержит в себе определение класса Player
*/

/*!
\brief Класс для разработки подвижного блока и его управления
*/

class Player {

private:
	int orig_w = 0;
	int w = 0;
	int h = 0;
	int x = 0;
	int y = 0;
	short vel = 30;
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
	/*!
	\brief Метод для получения позиции по х
	*/
	int getX()
	{
		return _player.getPosition().x;
	}
	/*!
	\brief Метод для получения позиции по у
	*/
	int getY()
	{
		return _player.getPosition().y;
	}
	/*!
	\brief Метод для получения длины подвижного блока
	*/
	int getW()
	{
		return this->w;
	}
	/*!
	\brief Метод для перемещения подвижного блока влево
	*/
	void moveLeft()
	{
		_player.move(0 - this->vel * 0.012, 0);
	}
	/*!
	\brief Метод для получения глобального прямоугольника, ограничивающего объект
	*/
	sf::FloatRect getGlobalBounds()
	{
		return _player.getGlobalBounds();
	}
	/*!
	\brief Метод для перемещения подвижного блока вправо
	*/
	void moveRight()
	{
		_player.move(0 + this->vel * 0.012, 0);
	}
	/*!
	\brief Метод для увеличения длины подвижного блока
	*/
	void grow()
	{
		_player.setSize(sf::Vector2f(this->w += 10, this->h));
	}
	/*!
	\brief Метод для уменьшения длины подвижного блока
	*/
	void shrink()
	{
		if (this->w > 10)
			_player.setSize(sf::Vector2f(this->w -= 10, this->h));
	}
	/*!
	\brief Метод для увеличения скорости подвижного блока
	*/
	void increaseSpeed()
	{
		this->vel += 10;
	}
	/*!
	\brief Метод для уменьшения скорости подвижного блока
	*/
	void decreaseSpeed()
	{
		if (this->vel > 10)
			this->vel -= 10;
	}
	/*!
	\brief Метод для установления начальной скорости
	*/
	void resetSpeed() {
		this->vel = 30;
	}
	/*!
	\brief Метод для возращения начального размера блока
	*/
	void reset_w()
	{
		this->w = this->orig_w;
		_player.setSize(sf::Vector2f(this->w, this->h));
	}
	/*!
	\brief Метод для возвращения блока в начальную позицию
	*/
	void resetPosition()
	{
		_player.setPosition(this->x, this->y);
	}
	/*!
	\brief Метод для рисования блока в окне
	*/
	void draw(sf::RenderWindow& window)
	{
		window.draw(_player);
	}
};