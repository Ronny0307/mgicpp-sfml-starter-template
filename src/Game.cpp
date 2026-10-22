
#include "Game.h"
#include <memory>
#include <vector>
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{
	delete[]animals;
	delete[]passports;
	delete[]character;
	delete[]passport;

}

// We call this once after the game class is instantiated
bool Game::init()
{
	background_texture = new sf::Texture();
	accepted_texture = new sf::Texture();
	rejected_texture = new sf::Texture();
	acceptbutton_texture = new sf::Texture();
	rejectbutton_texture = new sf::Texture();

	animals = new sf::Texture[3];
	passports = new sf::Texture[3];

	//animals[0]->
	animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");

	passports[0].loadFromFile("../Data/Images/Critter Crossing/elephant passport.png");
	passports[1].loadFromFile("../Data/Images/Critter Crossing/moose passport.png");
	passports[2].loadFromFile("../Data/Images/Critter Crossing/penguin passport.png");

	accepted_texture->loadFromFile("../Data/Images/Critter Crossing/accept.png");
	rejected_texture->loadFromFile("../Data/Images/Critter Crossing/reject.png");
	acceptbutton_texture->loadFromFile("../Data/Images/Critter Crossing/accept button.png");
	rejectbutton_texture->loadFromFile("../Data/Images/Critter Crossing/reject button.png");

	font.openFromFile("../Data/Fonts/open-sans/OpenSans-Regular.ttf");
	if(!background_texture->loadFromFile("../Data/Images/WhackaMole Worksheet/background.png"))
	{
		std::cout << "background texture not found";
		return 0;
	}
	
	background = new sf::Sprite(*background_texture);
	character = new sf::Sprite(animals[0]);
	passport = new sf::Sprite(passports[0]);


	std::string _menutext="Migration Immigration";
	std::string _menutext2 = "Press Q to quit, Space to start";
	std::string _menutext3 = "Pressing X ends game and reveals score";

	menutext.setCharacterSize(60);
	menutext2.setCharacterSize(40);
	menutext3.setCharacterSize(40);
	menutext.setString(_menutext);
	menutext2.setString(_menutext2);
	menutext3.setString(_menutext3);
	menutext.setFillColor(sf::Color::Blue);
	menutext2.setFillColor(sf::Color::Blue);
	menutext3.setFillColor(sf::Color::Blue);
	menutext.setPosition(sf::Vector2f(260.0f,200.0f));
	menutext2.setPosition(sf::Vector2f(250.0f, 300.0f));
	menutext3.setPosition(sf::Vector2f(200.0f, 400.0f));

	evaluation.setCharacterSize(60);
	evaluation.setFillColor(sf::Color::Yellow);
	evaluation.setPosition(sf::Vector2f(260.0f, 200.0f));
	
	score.setCharacterSize(60);
	score.setFillColor(sf::Color::Yellow);
	score.setPosition(sf::Vector2f(260.0f, 300.0f));
	

	acceptbutton = new sf::Sprite(*acceptbutton_texture);
	rejectbutton = new sf::Sprite(*rejectbutton_texture);
	accepted = new sf::Sprite(*accepted_texture);
	rejected = new sf::Sprite(*rejected_texture);
	acceptbutton->setPosition(sf::Vector2f(window.getSize().x / 2 - 200, window.getSize().y / 1.5));
	rejectbutton->setPosition(sf::Vector2f(window.getSize().x / 2 + 100, window.getSize().y / 1.5));

	currentstate = Gamestate::Menu;
	newAnimal();
  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	switch (currentstate)
	{
	 case Gamestate::Menu:
		break;
	 case Gamestate::Ingame:
		 dragsprite(dragged);
		 if (dragging == false)
		 {
			 returnpassport();
		 }
		 break;
	 case Gamestate::Inspection:
		 
		 break;
	}
}

void Game::newAnimal()
{
	int animal_index = rand() % 3;
	int	passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}
	

	character = new sf::Sprite(animals[animal_index]);
	passport = new sf::Sprite(passports[passport_index]);

	character->setTexture(animals[animal_index], true);
	character->setScale({ 1.6, 1.6 });
	character->setPosition(sf::Vector2f(window.getSize().x / 12, window.getSize().y / 9));

	passport->setTexture(passports[passport_index], true);
	passport->setScale({ 0.6, 0.6 });
	passport->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
}

void Game::dragsprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - sf::Vector2f{0,0};
		sprite->setPosition({drag_position.x,drag_position.y});
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
		window.draw(menutext3);
		break;
	case Gamestate::Ingame:
		window.draw(*background);
		window.draw(*character);
		window.draw(*passport);
		if (openselection)
		{
			window.draw(*acceptbutton);
			window.draw(*rejectbutton);
		}
		break;
	case Gamestate::Inspection:
		window.draw(evaluation);
		window.draw(score);
		break;
	}
}
void Game::returnpassport()
{
	//std::cout << dragging;
	//std::cout << stamped;
	if (dragging == false && stamped)
	{
		if (passport->getGlobalBounds().findIntersection({ character->getGlobalBounds() }))

		/*if (character->getPosition().x > passport->getPosition().x && character->getPosition().x < passport->getPosition().x
			+ passport->getGlobalBounds().size.x)*/
		{
			/*if (character->getPosition().y > passport->getPosition().y && character->getPosition().y < passport->getPosition().y
				+ passport->getGlobalBounds().size.y)*/

			{
				dragged = nullptr;
				dragging = false;
				passport->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
				nextanimal();
			}
		}
	}
}

void Game::nextanimal()
{
	stamped = false;
	newAnimal();
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
		sf::Vector2f click = static_cast<sf::Vector2f>(event->position);
		if (passport->getGlobalBounds().contains(click)&&dragging==false)
		{
			dragged = passport;
			dragging = true;
		}
		else if (dragging)
		{
			dragged = nullptr;
			dragging = false;
			
		}

		//Left mouse button was pressed
	}
	if (event->button == sf::Mouse::Button::Right)
	{
		switch(currentstate)
		{
		case Gamestate::Ingame:
			if (openselection == false && stamped==false)
			{
				openselection = true;
			}
			else if(stamped==false)
			{
				if (position.x > acceptbutton->getPosition().x && position.x < acceptbutton->getPosition().x + acceptbutton->getGlobalBounds().size.x)
				{
					if (
						position.y > acceptbutton->getPosition().y &&
						position.y < acceptbutton->getPosition().y + acceptbutton->getGlobalBounds().size.y)
					  {
						if (should_accept)
						{
							correctanimals++;
						}
						else
						{
							incorrectanimals++;
						}
						openselection = false;
						stamped = true;
				      }
				}
				else if(position.x > rejectbutton->getPosition().x && position.x < rejectbutton->getPosition().x + rejectbutton->getGlobalBounds().size.x)
				{
					if (position.y > rejectbutton->getPosition().y && position.y < rejectbutton->getPosition().y + rejectbutton->getGlobalBounds().size.y)
					{
						if (!should_accept)
						{
							correctanimals++;
						}
						else
						{
							incorrectanimals++;
						}
						openselection = false;
						stamped = true;
					}
				}
			}
			//std::cout << correctanimals;
			//std::cout << incorrectanimals;
			break;
		}
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
	if (event->scancode == sf::Keyboard::Scancode::X)
	{
		currentstate = Gamestate::Inspection;
		score.setString("Score: " + std::to_string((correctanimals - incorrectanimals) * 100));
		evaluation.setString("Correct: " + std::to_string(correctanimals) + " Incorrect: " + std::to_string(incorrectanimals));
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


