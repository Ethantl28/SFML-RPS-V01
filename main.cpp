#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;

//Functions
void HandleInput(sf::Event evnt);
void HandleGameMenuInput(sf::Event evnt, sf::RectangleShape rock, sf::RectangleShape paper, sf::RectangleShape scissors, sf::RectangleShape back);
int RandomNumberGen();
void PlayGame();
void HandleMainMenuInput(sf::Event evnt, sf::RectangleShape start, sf::RectangleShape exit);

//Variables
int iconWidth = 200;
int iconHeight = 200;

int userChoice;
int enemyChoice;
string Choices[3] = { "Rock", "Paper", "Scissors" };
					   //Rock Paper Scissors
bool resultTable[3][3]{ { true, false, true}, //rock
					   {true, true, false}, //paper
					   {false, true, true} }; //scissors

bool mainMenuopen = true;
bool gameMenuOpen = false;

//Window
sf::RenderWindow window(sf::VideoMode(1280, 720), "Rock, Paper, Scissors", sf::Style::Close | sf::Style::Titlebar);

int main()
{
	//Objects
		//Shapes
			//Main Menu
	sf::RectangleShape start(sf::Vector2f(400, 200));
	sf::RectangleShape exit(sf::Vector2f(350, 200));
			//Game Menu
	sf::RectangleShape rock(sf::Vector2f(iconWidth, iconHeight));
	sf::RectangleShape paper(sf::Vector2f(iconWidth, iconHeight));
	sf::RectangleShape scissors(sf::Vector2f(iconWidth, iconHeight));
	sf::RectangleShape back(sf::Vector2f(100, 50));
		//Textures
			//Main Menu]
	sf::Texture startTexture;
	sf::Texture exitTexture;
			//Game Menu
	sf::Texture rockTexture;
	sf::Texture paperTexture;
	sf::Texture scissorsTexture;
	sf::Texture backTexture;

	startTexture.loadFromFile("Start.png");
	exitTexture.loadFromFile("Exit.png");
	rockTexture.loadFromFile("Rock.png");
	paperTexture.loadFromFile("Paper.png");
	scissorsTexture.loadFromFile("Scissors.png");
	backTexture.loadFromFile("Exit.png");

	start.setTexture(&startTexture);
	exit.setTexture(&exitTexture);
	rock.setTexture(&rockTexture);
	paper.setTexture(&paperTexture);
	scissors.setTexture(&scissorsTexture);
	back.setTexture(&backTexture);

	start.setOrigin(200, 100);
	exit.setOrigin(175, 100);
	rock.setOrigin(iconWidth / 2, iconHeight / 2);
	paper.setOrigin(iconWidth / 2, iconHeight / 2);
	scissors.setOrigin(iconWidth / 2, iconHeight / 2);
	back.setOrigin(50, 25);

	start.setPosition(1280 / 2, 720 / 3);
	exit.setPosition(1280 / 2, (720 / 3) * 2);
	rock.setPosition(1280 / 4, 720 / 2);
	paper.setPosition(1280 / 2, 720 / 2);
	scissors.setPosition((1280 / 4) * 3, 720 / 2);
	back.setPosition(50, 25);

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed: HandleInput(evnt); break;
			case sf::Event::MouseButtonPressed: 
				if (mainMenuopen)
					HandleMainMenuInput(evnt, start, exit);
				else if (gameMenuOpen)
					HandleGameMenuInput(evnt, rock, paper, scissors, back); 
				break;
			default:	break;
			}

		}

		window.clear(sf::Color::Black);

		if (mainMenuopen)
		{
			window.draw(start);
			window.draw(exit);
		}
		else if (gameMenuOpen)
		{
			window.draw(rock);
			window.draw(paper);
			window.draw(scissors);
			window.draw(back);
		}

		window.display();
	}

	return 0;
}

void HandleInput(sf::Event evnt)
{
	cout << "Keyboard Input" << endl;
}

void HandleGameMenuInput(sf::Event evnt, sf::RectangleShape rock, sf::RectangleShape paper, sf::RectangleShape scissors, sf::RectangleShape back)
{
	if (evnt.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos(evnt.mouseButton.x, evnt.mouseButton.y);
		sf::FloatRect rockBoundingBox = rock.getGlobalBounds();
		sf::FloatRect paperBoundingBox = paper.getGlobalBounds();
		sf::FloatRect scissorsBoundingBox = scissors.getGlobalBounds();
		sf::FloatRect backBoundingBox = back.getGlobalBounds();

		if (rockBoundingBox.contains(mousePos))
		{
			userChoice = 0;
			PlayGame();
		}
		else if(paperBoundingBox.contains(mousePos))
		{
			userChoice = 1;
			PlayGame();
		}
		else if (scissorsBoundingBox.contains(mousePos))
		{
			userChoice = 2;
			PlayGame();
		}
		else if (backBoundingBox.contains(mousePos))
		{
			mainMenuopen = true;
			gameMenuOpen = false;
		}
	}
}

int RandomNumberGen()
{
	srand(time(NULL));
	return rand() % 3;
}

void PlayGame()
{
	enemyChoice = RandomNumberGen();

	cout << "You chose " << Choices[userChoice] << "\nEnemy chose " << Choices[enemyChoice] << endl;

	if (userChoice == enemyChoice)
	{
		cout << "DRAW!" << endl;
	}
	else
	{
		if (resultTable[enemyChoice][userChoice])
		{
			cout << "YOU LOSE!" << endl;
		}
		else
		{
			cout << "YOU WIN!" << endl;
		}
	}
}

void HandleMainMenuInput(sf::Event evnt, sf::RectangleShape start, sf::RectangleShape exit)
{
	sf::Vector2f mousePos(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y));
	sf::FloatRect startBoundingBox = start.getGlobalBounds();
	sf::FloatRect exitBoundingBox = exit.getGlobalBounds();

	if (startBoundingBox.contains(mousePos))
	{
		gameMenuOpen = true;
		mainMenuopen = false;
	}
	else if (exitBoundingBox.contains(mousePos))
	{
		window.close();
	}
}
