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
		auto Brick = this->bricks.begin();

		while(Brick != this->bricks.end())
		{
			if ((*Brick).isDestroy())
			{
				player_score += (*Brick).getPoints();
				Brick = this->bricks.erase(Brick);//?
				this->tot_bricks--;
			}
			else {
				Brick++;
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