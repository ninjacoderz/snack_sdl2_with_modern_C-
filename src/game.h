#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "roadblock.h"
#include <memory>
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int init_num_blocks);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  
  void PlaceBlock();
  void InsertBlock(std::unique_ptr<RoadBlock>& , int, int);
  void DeleteBlock(std::unique_ptr<RoadBlock>& , int, int);

  std::unique_ptr<RoadBlock> road_blocks;
  bool DetectCollision(std::unique_ptr<RoadBlock>&, int, int);
};

#endif