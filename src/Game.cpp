
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{

}

// We call this once after the game class is instantiated
bool Game::init()
{
	font.openFromFile("../Data/Fonts/open-sans/OpenSans-Regular.ttf");
	background_texture.loadFromFile("../Data/Images/WhackaMole Worksheet/background.png");
	std::string _menutext="Migration Immigration";
	std::string _menutext2 = "Press Q to quit, Space to start";

	menutext.setCharacterSize(60);
	menutext2.setCharacterSize(60);
	menutext.setString(_menutext);
	menutext2.setString(_menutext2);
	menutext.setFillColor(sf::Color::Blue);
	menutext2.setFillColor(sf::Color::Blue);
	menutext.setPosition(sf::Vector2f(260.0f,200.0f));
	menutext2.setPosition(sf::Vector2f(190.0f, 300.0f));

	currentstate = Gamestate::Menu;
  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	switch (currentstate)
	{
	 case Gamestate::Menu:
		window.draw(menutext);
		window.draw(menutext2);

	}
}

// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	switch (currentstate)
	{
	case Gamestate::Menu:
		window.draw(menutext);
		window.draw(menutext2);

	}
}

//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
	sf::Vector2i position = event->position;

	// You can tell which button was pressed by comparing it to SFML's definitions of mouse buttons
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was pressed
	}
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was released
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was pressed
	}
	if (event->scancode == sf::Keyboard::Scancode::Q)
	{
		window.close();
	}
	if (currentstate == Gamestate::Menu)
	{
		if (event->scancode == sf::Keyboard::Scancode::Space)
		{
			currentstate = Gamestate::Ingame;
		}
	}

}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{
	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}

}


