
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
  void newAnimal();
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);

  /* Menu*/

 /* sf::Text score_text;*/
  /*sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;*/

  bool in_menu = true;



  bool should_accept = false;

 //Sprites
  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];


  sf::Sprite* acceptButton;
  sf::Texture acceptButton_Texture{ "../Data/Images/Critter Crossing/accept button.png" };
  sf::Sprite* rejectButton;
  sf::Texture rejectButton_Texture {"../Data/Images/Critter Crossing/reject button.png" };
  
 

 private:
  sf::RenderWindow& window;
  
  sf::Texture background_texture{ "../Data/Images/WhackaMole Worksheet/background.png" };
  sf::Sprite background{ background_texture };
  /*sf::Texture* background = new sf::Texture;*/


};

#endif // SFML_GAME_H
