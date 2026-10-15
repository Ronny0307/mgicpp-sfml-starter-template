
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);

  void newAnimal();

 private:
  sf::RenderWindow& window;
  sf::Font font;
  sf::Texture* background_texture;
  sf::Sprite* background;
  sf::Text menutext{ font };
  sf::Text menutext2{ font };
  enum Gamestate { Ingame, Menu, Inspection };
  Gamestate currentstate;

  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Texture* animals;
  sf::Texture* passports;
  bool should_accept;
};

#endif // SFML_GAME_H
