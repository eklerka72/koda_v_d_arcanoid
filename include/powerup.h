/*!
\file
\brief Заголовочный файл с описанием класса Powerup
Данный файл содержит в себе определение класса Powerup
*/

/*!
\brief Класс для разработки бонусов и их описании
*/
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
	/*!
	\brief Метод для установки позиции
	*/
	void setPosition(int x, int y)
	{
		_power.setPosition(x, y);
	}
	/*!
	\brief Метод для перемещения бонуса
	*/
	void move()
	{
		_power.move(0, 0 + 2 * 0.09);
	}
	/*!
	\brief Метод для получения типа бонуса
	*/
	int getType()
	{
		return this->type;
	}
	/*!
	\brief Метод для получения глобального прямоугольника, ограничивающего объект
	*/
	sf::FloatRect getGlobalBounds()
	{
		return _power.getGlobalBounds();
	}
	/*!
	\brief Метод для обозначения, что бонус был взят
	*/
	void take()
	{
		this->_take = 1;
	}
	/*!
	\brief Метод для проверки на взятие бонуса
	*/
	bool isTake()
	{
		return this->_take;
	}
	/*!
	\brief Метод для рисования бонуса в окне
	*/
	void draw(sf::RenderWindow& window)
	{
		window.draw(_power);
	}
};