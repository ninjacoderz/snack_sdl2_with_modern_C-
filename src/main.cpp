#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scorefile.h"

int main() {
  std::cout << "Player name: ";
  std::string name;
  std::cin >> name;
  
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  
  int numberBlocks = 5;
  Game game(kGridWidth, kGridHeight, numberBlocks);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  int score = game.GetScore();
  int size = game.GetSize();
  ScoreFile* scoreHandler = new ScoreFile();
  scoreHandler->WriteToFile(name, score, size);
  
  std::cout << "Score: " << score << "\n";
  std::cout << "Size: " << size << "\n";
  return 0;
}