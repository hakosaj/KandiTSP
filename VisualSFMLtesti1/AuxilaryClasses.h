



//Class for drawing sf lines
class sfLine : public sf::Drawable
{
public:
	sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2) :
		color(sf::Color::Black), thickness(2.f)
	{
		sf::Vector2f direction = point2 - point1;
		sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
		sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

		sf::Vector2f offset = (thickness / 2.f)*unitPerpendicular;

		vertices[0].position = point1 + offset;
		vertices[1].position = point2 + offset;
		vertices[2].position = point2 - offset;
		vertices[3].position = point1 - offset;

		for (int i = 0; i<4; ++i)
			vertices[i].color = color;
	}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(vertices, 4, sf::Quads);
	}
	 

private:
	sf::Vertex vertices[4];
	float thickness;
	sf::Color color;
};

class City {
public: float x, y;
		int id;

public: City(int num, float xval, float yval) {
	id = num;
	x = xval;
	y = yval;
}
};

class Tour {

public:	float dist;
		std::vector<City> cintour;


		Tour(std::vector<City> cts) {
			cintour = cts;
			dist = distance(cintour);
		}
	bool operator < (const Tour& tour2) const
	{
		return dist < tour2.dist;
	}

	float euclideanDistance(float x1, float x2, float y1, float y2)
	{
		float dist = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
		return dist;
	}

	float distance(std::vector<City> cits)
	{
		float currentDist = 0;


		for (int i = 0; i < dotcount - 1; i++)
		{
			currentDist += euclideanDistance(cits[i].x, cits[i + 1].x, cits[i].y, cits[i + 1].y);
		}
		currentDist += euclideanDistance(cits[0].x, cits[dotcount - 1].x, cits[0].y, cits[dotcount - 1].y);

		return currentDist;
	}

};





