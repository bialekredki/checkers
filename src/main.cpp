#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "inc/Board.hpp"
#include "inc/Player.hpp"
#include <iostream>
#include <cmath>

#define BOARD_SIZE 10
#define NUMBER_OF_PAWNS 40

bool checkBoundaries(int x,sf::Vector2f boundaries);
bool isMousePositionOnBoard(sf::Vector2<int> mousePosition);
int  searchForTileClicked(sf::Vector2<int> mousePosition, float tileLength, std::vector<sf::Vector2f> tilesPositions);

void setupWindow(sf::RenderWindow& window);
void setupTiles(std::vector<sf::Vector2f>& tilesPositions,std::vector<sf::Vector2f>& tilesCenters,std::vector<sf::RectangleShape>& tiles, float tileLength);
void setupFont(sf::Font& font);
void setupText(sf::Text& text, sf::Font font);

int main()
{
int height = 800;
int width = 1000;
sf::RenderWindow window(sf::VideoMode(width,height), "Warcaby");
setupWindow(window);
sf::Font font;
setupFont(font);
sf::Text text;
text.setFont(font);
text.setPosition(800,0);
text.setCharacterSize(14);
text.setFillColor(sf::Color::White);

  while(window.isOpen()){
    Board b;
    Player p1(b,1);
    Player p2(b,2);

    float tileArea = height*height/(BOARD_SIZE*BOARD_SIZE);
    float tileLength = sqrt(tileArea);

    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::Vector2f> tilesPositions;
    std::vector<sf::Vector2f> tilesCenters;
    setupTiles(tilesPositions,tilesCenters, tiles, tileLength);

    std::vector<sf::CircleShape> pawns;
    float circleSize = sqrt(0.65*(tileArea)/3.14);
    for(int i = 0; i<NUMBER_OF_PAWNS ; ++i)
      pawns.push_back(sf::CircleShape(circleSize,2000));

    bool turn = false; // false turn P1 true turn P2
    int firstTilePressed = -1;
    int secondTilePressed = -1;
    int player = 0;
    bool onboard = false;
    bool wasMoveCorrect = false;
    bool isRunning = true;
    bool isWon = false;
    while(isRunning){
      b.console_Display();
      //check for winning conditions
      isWon = b.checkIfWon((int)(!turn));
      if(isWon){
        if(!turn) text.setString("Player 1(BLACK) won. \nLeft-click on board to play again.");
        else text.setString("Player 1(BLUE) won. \nLeft-click on board to play again.");
      }

      //movement logic on board
      else{
      //while(true){
      if(turn) text.setString("Player 2(BLUE)s turn.");
      else text.setString("Player 1(BLACK)s turn.");

      if(firstTilePressed == -1) text.setString(text.getString()+"\nChose pawn to move.");
      if(firstTilePressed != -1 && secondTilePressed == -1)  text.setString(text.getString()+"\nChose where to move pawn.");

      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if(isMousePositionOnBoard(mousePosition)){
          if(firstTilePressed == -1){
            firstTilePressed = searchForTileClicked(mousePosition,tileLength,tilesPositions);
            //std::cout << firstTilePressed << '\n';f
          }
          else{
            secondTilePressed = searchForTileClicked(mousePosition,tileLength,tilesPositions);
            //std::cout << secondTilePressed << '\n';

            if(turn)
              wasMoveCorrect = p2.move(firstTilePressed,secondTilePressed);
            else
              wasMoveCorrect = p1.move(firstTilePressed,secondTilePressed);
          }
        }
        else{
          if(firstTilePressed != -1)  firstTilePressed = -1;
          if(secondTilePressed != -1) secondTilePressed = -1;
        }
      }

      if(firstTilePressed != -1 && secondTilePressed != -1){
        firstTilePressed = -1;
        secondTilePressed = -1;
        if(wasMoveCorrect){
          if(turn) turn = false;
          else turn = true;
        }

      }
    //}
  }

    //event and drawing part
    sf::Event event;
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
        isRunning = false;
        window.close();
      }
    }

    window.clear(sf::Color::Black);

    for(const auto& rect : tiles)  window.draw(rect);

    int circle_number = 0;
    for(int i = 0; i < BOARD_SIZE*BOARD_SIZE; ++i){
      player = b.getTiles().at(i)->getPawnPlayer();
      if(player == 0) continue;
      onboard = b.getTiles().at(i)->getPawn()->isOnBoard();
      if(!onboard) continue;

      if(player == 1 && onboard){
        pawns.at(circle_number).setFillColor(sf::Color::Black);
      }
      else if(player == 2 && onboard)
        pawns.at(circle_number).setFillColor(sf::Color::Blue);


      pawns.at(circle_number).setPosition(tilesCenters.at(i));
      pawns.at(circle_number).setOrigin(pawns.at(circle_number).getRadius(),pawns.at(circle_number).getRadius());
      window.draw(pawns.at(circle_number));
      ++circle_number;
    }
    window.draw(text);
    window.display();
    while(isWon){
      if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        if(isMousePositionOnBoard){
          isRunning = false;
          break;
  }
}

}
}

}
}

bool checkBoundaries(int x,sf::Vector2f boundaries){
  if(x >= boundaries.x && x <= boundaries.y) return true;
  else return false;
}

bool isMousePositionOnBoard(sf::Vector2<int> mousePosition){
  if(checkBoundaries(mousePosition.x,sf::Vector2f(0,800)) && checkBoundaries(mousePosition.y,sf::Vector2f(0,800)))  return true;
  else return false;
}

int  searchForTileClicked(sf::Vector2<int> mousePosition, float tileLength, std::vector<sf::Vector2f>  tilesPositions){
  int counter = 0;
  for(const auto& tilePosition : tilesPositions){
    sf::Vector2f tileBoundariesX(tilePosition.x,tilePosition.x + tileLength);
    sf::Vector2f tileBoundariesY(tilePosition.y,tilePosition.y + tileLength);
    if(checkBoundaries(mousePosition.x,tileBoundariesX) && checkBoundaries(mousePosition.y, tileBoundariesY)) return counter;
    counter++;
  }
  return -1;
}

void setupWindow(sf::RenderWindow& window){
  window.setFramerateLimit(60);
}

void setupTiles(std::vector<sf::Vector2f>& tilesPositions,std::vector<sf::Vector2f>& tilesCenters,std::vector<sf::RectangleShape>& tiles, float tileLength){
  for(int i = 0; i < BOARD_SIZE; ++i){
    for(int j = 0; j < BOARD_SIZE; ++j )
    {
      tilesPositions.push_back(sf::Vector2f(j*tileLength,i*tileLength));
      tiles.push_back(sf::RectangleShape(sf::Vector2f(tileLength,tileLength)));
    }
  }
  int color_it = 0;
  int row = 1;
  float x = 0;
  float y = 0;
  for(auto& rect:tiles){
    /*if(color_it % 2 == 0 && row % 2 == 0)  rect.setFillColor(sf::Color::Red);
    else if(color_it % 2 == 1 && row % 2 == 0) rect.setFillColor(sf::Color::White);
    else if(color_it % 2 == 0 && row % 2 == 1)  rect.setFillColor(sf::Color::White);
    else if(color_it % 2 == 1 && row % 2 == 1) rect.setFillColor(sf::Color::Red);*/

    if(row % 2 == 1){
      if(color_it % 2 == 0) rect.setFillColor(sf::Color::White);
      else rect.setFillColor(sf::Color::Red);
    }
    else{
      if(color_it % 2 == 1) rect.setFillColor(sf::Color::White);
      else rect.setFillColor(sf::Color::Red);
    }

    rect.setPosition(tilesPositions.at(color_it));
    x = tilesPositions.at(color_it).x + tileLength/2;
    y = tilesPositions.at(color_it).y + tileLength/2;
    tilesCenters.push_back(sf::Vector2f(x,y));
    if((color_it + 1) % BOARD_SIZE == 0) row++;
    color_it++;

  }
}

void setupFont(sf::Font& font){
  std::string fontLocation = "data/fonts/arial.ttf";
  if(!font.loadFromFile(fontLocation)){
    std::cout << "Arial font TTF file missing." << '\n';
  }
}

void setupText(sf::Text& text, sf::Font font){ //inactive doesnt work for some reason fuck SFML and its text class
  text.setFont(font);
  text.setPosition(600,0);
  text.setCharacterSize(10);
  text.setFillColor(sf::Color::White);
}
