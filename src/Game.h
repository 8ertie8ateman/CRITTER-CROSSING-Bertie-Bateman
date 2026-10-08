
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

  //// Menu
  //sf::Font font;
  //sf::Text title_text;
  //sf::Text score_text;

  //bool in_menu = true;
  //sf::Text menu_text(font);
  //sf::Text play_option(font);
  //sf::Text quit_option(font);

  //sf::title_text

 //Sprites
  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

 private:
  sf::RenderWindow& window;
  
  sf::Texture background_texture;
  sf::Sprite background = sf::Sprite(background_texture);

};

#endif // SFML_GAME_H
