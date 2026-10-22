
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  //seeds random number generator with the current time
}

Game::~Game()
{
	delete [] animals;
	delete [] passports; 
	delete character;
	delete passport; 

}
//comment
// We call this once after the game class is instantiated
bool Game::init()
{
	if (!font.openFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}

	menu_text = new sf::Text(font);
	in_menu == true;
	menu_text->setString("Critter Crossing");
	menu_text->setFont(font);
	menu_text->setCharacterSize(50);
	menu_text->setFillColor(sf::Color(255, 255, 255, 255));
	menu_text->setPosition({ 350, 200 });

	play_option = new sf::Text(font);
	play_option->setString("Play");
	play_option->setFont(font);
	play_option->setCharacterSize(30);
	play_option->setFillColor(sf::Color(255, 255, 255, 255));
	play_option->setPosition({ 500, 325 });

	quit_option = new sf::Text(font);
	quit_option->setString("Quit");
	quit_option->setFont(font);
	quit_option->setCharacterSize(30);
	quit_option->setFillColor(sf::Color(255, 255, 255, 255));
	quit_option->setPosition({ 500, 375 });

	

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (!animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png"))
	{
		std::cout << "Animal texture did not load \n";
	}
	if (!animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png"))
	{
		std::cout << "Animal texture did not load \n";
	}

	if (!animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png"))
	{
		std::cout << "Animal texture did not load \n";
	}
	character = new sf::Sprite(animals[0]);

	character->setTexture(animals[animal_index], true);
	character->setScale({ 1.8, 1.8 });
	character->setPosition(sf::Vector2f(window.getSize().x / 12, window.getSize().y / 12));
	
	if (!passports[0].loadFromFile("../Data/Images/Critter Crossing/elephant passport.png"))
	{
		std::cout << "Passport texture did not load \n";
	}
	if (!passports[1].loadFromFile("../Data/Images/Critter Crossing/moose passport.png"))
	{
		std::cout << "Passport texture did not load \n";
	}

	if (!passports[2].loadFromFile("../Data/Images/Critter Crossing/penguin passport.png"))
	{
		std::cout << "Passport texture did not load \n";
	}

	//background 
	if (!background_texture.loadFromFile("../Data/Images/WhackaMole Worksheet/background.png"))
	{
		std::cout << "Background texture did not load \n";
	}

	background.setTexture(background_texture);


	passport = new sf::Sprite(passports[0]);

	passport->setTexture(passports[passport_index]);
	passport->setScale({ 0.6, 0.6 });
	passport->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 3));

	acceptButton = new sf::Sprite(acceptButton_Texture);
	acceptButton->setScale({ 0.6, 0.6 });
	acceptButton->setPosition(sf::Vector2f(window.getSize().x  *0.8f, window.getSize().y *0.4f ));

	rejectButton = new sf::Sprite(rejectButton_Texture);
    rejectButton->setScale({ 0.6, 0.6 });
	rejectButton->setPosition(sf::Vector2f(window.getSize().x * 0.8f, window.getSize().y * 0.5f));

	rejectStamp = new sf::Sprite(rejectStamp_Texture);
	rejectStamp->setScale({ 0.6, 0.6 });
	rejectStamp->setPosition(sf::Vector2f(passport->getPosition().x + 130, passport->getPosition().y + 130));

	acceptStamp = new sf::Sprite(acceptStamp_Texture);
	acceptStamp->setScale({ 0.75, 0.6 });
	acceptStamp->setPosition(sf::Vector2f(passport->getPosition().x + 130, passport->getPosition().y + 130));

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

  return true;
}

void Game::newAnimal()
{

}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	dragSprite(dragged);
	acceptStamp->setPosition(sf::Vector2f(passport->getPosition().x + 130, passport->getPosition().y + 130));
	rejectStamp->setPosition(sf::Vector2f(passport->getPosition().x + 130, passport->getPosition().y + 130));

}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf /*- drag_offset*/;
		sprite->setPosition({ drag_position.x, drag_position.y });

	}
}

// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	if (in_menu == false)
	{
		window.draw(background);
		window.draw(*character);
		window.draw(*passport);
		window.draw(*acceptButton);
		window.draw(*rejectButton);

	}
	else
	{
		window.draw(*menu_text);
		window.draw(*play_option);
		window.draw(*quit_option);
	}
	if (accepted == true)
	{
		window.draw(*acceptStamp);
	}
	if (rejected == true)
	{
		window.draw(*rejectStamp);
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
		sf::Vector2f click = static_cast<sf::Vector2f>(event->position);
		if (passport->getGlobalBounds().contains(click))
		{
			dragged = passport;
		}
	
		if (acceptButton->getGlobalBounds().contains(click))
		{
			accepted = true;
		}
		if (rejectButton->getGlobalBounds().contains(click))
		{
			rejected = true;
		}
	}
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		dragged = nullptr;
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	/*if (
		(event.key.code == sf::Keyboard::Up) ||
		(event.key.code == sf::Keyboard::Down))
	{
		play_selected = !play_selected;
		if (play_selected)
		{
			play_option->setString("> Play <");
			quit_option->setString("Quit");
		}
		else
		{
			play_option->setString("Play");
			quit_option->setString("> Quit <");
		}
	}
	else if (event.key.code == sf::Keyboard::Enter)
	{
		if (play_selected)
		{
			in_menu = false;
		}
		else
		{
			window.close();
		}
	}
	if (event.key.code == sf::Keyboard::Escape)
	{
		in_menu = true;
	}*/

	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was pressed
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
