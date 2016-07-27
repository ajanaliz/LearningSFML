#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <sstream>
#define WIDTH 800 
#define HEIGHT 600
#define PADWIDTH 50 
#define PADHEIGHT 100
#define BALLWIDTH 50 
#define BALLHEIGHT 50


int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Game");
	bool running = true;
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	sf::Event event;

	
	//fonts
	sf::Font myFont;
	if (myFont.loadFromFile("res/fonts/arial.ttf") == 0)
	{
		return 1;
	}
	
	//text
	sf::Text score;
	score.setFont(myFont);
	score.setCharacterSize(30);
	score.setString("0 : 0");
	score.setPosition(sf::Vector2f(380, 10));
	score.setColor(sf::Color::Red);

	//images
	sf::Texture background;
	sf::Texture pad;
	sf::Texture ball;
	if (background.loadFromFile("res/images/background.png") == false
		|| ball.loadFromFile("res/images/ball.png") == false
		|| pad.loadFromFile("res/images/rect.png") == false)
	{
		return -1;
	}
	//states
	bool up = false, down = false;

	//variables
	int pad1VelY = 0;
	int ballVelX = -3;
	int ballVelY = -3;
	int pad2VelY = 0;
	int pad1Score = 0, pad2Score = 0;

	//shapes
	sf::RectangleShape backgroundRect;
	backgroundRect.setSize(sf::Vector2f(WIDTH,HEIGHT));
	backgroundRect.setPosition(sf::Vector2f(0, 0));
	backgroundRect.setTexture(&background);
	sf::RectangleShape pad1;
	sf::RectangleShape pad2;
	pad1.setSize(sf::Vector2f(PADWIDTH, PADHEIGHT));
	pad1.setPosition(sf::Vector2f(50, 200));
	pad1.setTexture(&pad);
	pad2.setSize(sf::Vector2f(PADWIDTH, PADHEIGHT));
	pad2.setPosition(sf::Vector2f(700, 200));
	pad2.setTexture(&pad);
	sf::RectangleShape ballRect;
	ballRect.setSize(sf::Vector2f(BALLWIDTH, BALLHEIGHT));
	ballRect.setPosition(sf::Vector2f(400, 225));
	ballRect.setTexture(&ball);


	//sound
	sf::SoundBuffer mySoundBuffer;
	if (mySoundBuffer.loadFromFile("res/sounds/Explosion.wav") == 0)
	{
		return 1;
	}
	sf::Sound explosion;
	explosion.setBuffer(mySoundBuffer);
	explosion.setVolume(50);

	//music
	sf::Music music;
	if (music.openFromFile("res/sounds/mainmenu.wav") == 0)
	{
		return 1;
	}
	music.setLoop(true);

	while (running)
	{
		//EVENT HANDLER
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
				up = true;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
				down = true;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
				up = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
				down = false;
		}

		//LOGIC
		if (up)
			pad1VelY = -5;
		if (down)
			pad1VelY = 5;
		if ((up && down) || (!up && !down))
			pad1VelY = 0;
		pad1.move(0, pad1VelY);

		//out of bounds check
		if (pad1.getPosition().y < 0)
		{
			pad1.setPosition(50, 0);
		}
		else if (pad1.getPosition().y + PADHEIGHT > HEIGHT)
		{
			pad1.setPosition(50, HEIGHT - PADHEIGHT);
		}

		//basic A.I for Pad2
		if (ballRect.getPosition().y < pad2.getPosition().y)
		{
			pad2VelY = -2;
		}
		else
		{
			pad2VelY = 2;
		}
		pad2.move(0, pad2VelY);
		//ball
		ballRect.move(ballVelX, ballVelY);
		//out of bounds check
		if (ballRect.getPosition().y < 0 || ballRect.getPosition().y + BALLHEIGHT > HEIGHT)
		{
			ballVelY *= -1;
		}
		//collision
		if (ballRect.getGlobalBounds().intersects(pad1.getGlobalBounds())
			|| ballRect.getGlobalBounds().intersects(pad2.getGlobalBounds()))
		{
			explosion.play();
			ballVelX *= -1;
		}
		if (ballRect.getPosition().x < -50)
		{
			pad2Score++;
			ballRect.setPosition(sf::Vector2f(300, 200));
		}
		else if (ballRect.getPosition().x > 800)
		{
			pad1Score++;
			ballRect.setPosition(sf::Vector2f(300, 200));
		}
			

		//RENDERING
		window.clear();
		window.draw(backgroundRect);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ballRect);
		//score
		std::stringstream text;
		text << pad1Score << " : " << pad2Score;
		score.setString(text.str());
		window.draw(score);
		window.display();
	}
	window.close();
	return 0;
}
