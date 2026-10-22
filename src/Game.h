
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
  void dragsprite(sf::Sprite* sprite);
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

  sf::Sprite* accepted;
  sf::Sprite* rejected;
  sf::Texture* accepted_texture;
  sf::Texture* rejected_texture;

  sf::Sprite* acceptbutton;
  sf::Sprite* rejectbutton;
  sf::Texture* acceptbutton_texture;
  sf::Texture* rejectbutton_texture;

  bool openselection = false;
  bool stamped = false;
  int correctanimals;
  int incorrectanimals;

  sf::Sprite* dragged = nullptr;
  bool should_accept;
};

#endif // SFML_GAME_H
