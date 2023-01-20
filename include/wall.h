/*!
\file
\brief Заголовочный файл  описанием класса Wall

Данный файл содержит в себе определение класса Wall
*/

/*!
\brief Класс для генерации блоков и отслеживания их состояний
*/


class Wall {
private:
	int w = 580;
	int h = 220;
	std::vector<Brick> bricks;
	short tot_bricks = 0;

public:
	/*!
	\brief Метод для генерации блоков
	*/
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
	/*!
	\brief Метод для генерации сетки блоков
	*/
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
	/*!
	\brief Метод для проверки столкновения
	*/
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
	/*!
	\brief Метод для проверки уничтожения и удаления блока
	*/
	void removeDestroyed(unsigned int& player_score)
	{
		auto Brick = this->bricks.begin();

		while(Brick != this->bricks.end())
		{
			if ((*Brick).isDestroy())
			{
				player_score += (*Brick).getPoints();
				Brick = this->bricks.erase(Brick);
				this->tot_bricks--;
			}
			else {
				Brick++;
			}
		}
	}
	/*!
	\brief Метод для получения вектора блоков
	*/
	std::vector<Brick> getBricksVector()
	{
		return this->bricks;
	}
	/*!
	\brief Метод для получения количества блоков
	*/
	int get_total_bricks()
	{
		return this->tot_bricks;
	}
	/*!
	\brief Метод для установки вектора блоков
	*/
	void setBricksVector(std::vector<Brick> bv)
	{
		this->bricks = bv;
	}
	/*!
	\brief Метод для отчистки вектора блоков
	*/
	void clear()
	{
		this->bricks.clear();
	}
	/*!
	\brief Метод для подсчета количества блоков
	*/
	void count_total_bricks()
	{
		for (auto& Brick : this->bricks)
			if (Brick.getResistance() != 0)
				this->tot_bricks += 1;
	}
	/*!
	\brief Метод для сброса количества блоков
	*/
	void reset_total_bricks()
	{
		this->tot_bricks = 0;
	}
	/*!
	\brief Метод для рисования сетки блоков в окне
	*/
	void draw(sf::RenderWindow& window)
	{
		for (auto& Brick : this->bricks)
			Brick.draw(window);
	}
};