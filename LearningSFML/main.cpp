#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");
	bool running = true;
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	sf::Event event;
	//states for buttons/events
	bool aPressed = false;
	bool aReleased = false;
	bool space = false;
	bool leftClick = false;
	
	//Variables
	int clicks = 0;
	int mouseX = 0, mouseY = 0;
	sf::Vector2f* rectPosition = new sf::Vector2f(0, 0);
	sf::Vector2f* circlePosition = new sf::Vector2f(0, 0);
	float circleRadius = 50;

	//Render shapes
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100, 50));
	rect.setPosition(sf::Vector2f(400, 300));
	rect.setFillColor(sf::Color::Green);
	sf::CircleShape circle;
	circle.setRadius(circleRadius);
	circle.setPosition(*circlePosition);
	circle.setFillColor(sf::Color::Magenta);

	while (running)
	{
		//EVENT HANDLER
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
				aPressed = true;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
				aReleased = true;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				space = true;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
				space = false;
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				leftClick = true;
			if (event.type == sf::Event::MouseMoved)
			{
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
			}
		}

		//LOGIC
		if (aPressed)
		{
			std::cout << "the A Key has been Pressed" << std::endl;
			aPressed = false;
		}
		if (aReleased)
		{
			std::cout << "the A Key has been Released" << std::endl;
			aReleased = false;
		}
//		if (space)
//		{
//			std::cout << "SPACE" << std::endl;
//		}
//		else
//		{
//			std::cout << "NOT SPACE" << std::endl;
//		}
		if (leftClick)
		{
			clicks++;
			leftClick = false;
			std::cout << "number of clicks so far: " << clicks << std::endl;
			std::cout << "mouse X: " << mouseX << " mouse Y: " << mouseY << std::endl;
			(*rectPosition).x = mouseX;
			(*rectPosition).y = mouseY;
			(*circlePosition).x = mouseX + 50;
			(*circlePosition).y = mouseY + 150;

		}
		rect.setPosition(*rectPosition);
		circle.setPosition(*circlePosition);

		//RENDERING
		window.clear();
		window.draw(circle);
		window.draw(rect);
		window.display();
	}
	delete rectPosition;
	window.close();
	return 0;
}
