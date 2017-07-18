
void debugPoint(sf::Vector2f &point, sf::RenderWindow& window)
{

  std::cout << "(" << point.x << ", " << point.y << "), ";
}

void debugTriangle(sf::Vector2f& a, sf::Vector2f& b, sf::Vector2f& c)
{
  std::cout << "Triangle: (" << a.x << ", " << a.y << "), ";
  std::cout << "(" << b.x << ", " << b.y << "), ";
  std::cout << "(" << c.x << ", " << c.y << ")" << std::endl;
}
