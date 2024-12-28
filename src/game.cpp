#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int init_num_blocks)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
	road_blocks = new RoadBlock(grid_width, grid_height);
    for (int i = 0; i < init_num_blocks; i++)
        PlaceBlock();
  	PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, road_blocks);
	
    // Detect Collision by snale head
    int head_x = static_cast<int>(snake.head_x);
    int head_y = static_cast<int>(snake.head_y);

    if (DetectCollision(road_blocks, head_x, head_y))
    {
      snake.alive = false;
      DeleteBlock(road_blocks, head_x, head_y);
    }
    
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::PlaceBlock() {
    int x, y;
    while (true)
    {
        x = random_w(engine);
        y = random_h(engine);

        int snake_head_x = static_cast<int>(snake.head_x);
        int snake_head_y = static_cast<int>(snake.head_y);
        if (!snake.SnakeCell(x, y) && !DetectCollision(road_blocks, x, y)
        && abs(x - snake_head_x) > 2 && abs(y - snake_head_y) > 2)
        {
            InsertBlock(road_blocks, x, y);
            return;
        }
    }
}

bool Game::DetectCollision(RoadBlock* root, int x, int y)
{

    if (root == nullptr || root->count == 0)
        return false;

    if (root->right - root->left == 1 && root->ceiling - root->floor == 1) 
    {

        if (x == root->left && y == root->floor)
        {
            snake.alive = false;
            return true;
        }

    }

    int mid_x = (root->left + root->right) / 2;
    int mid_y = (root->floor + root->ceiling) / 2;

    if (x < mid_x && y < mid_y)
        DetectCollision(root->upper_left, x, y);

    if (x < mid_x && y >= mid_y)
        DetectCollision(root->lower_left, x, y);

    if (x >= mid_x && y < mid_y)
        DetectCollision(root->upper_right, x, y);

    if (x >= mid_x && y >= mid_y)
        DetectCollision(root->lower_right, x, y);

    return false;
}

void Game::InsertBlock(RoadBlock* root, int x, int y)
{
    if (root == nullptr)
        return;

    if (root->right - root->left == 1 && root->ceiling - root->floor == 1)
    {
        root->count = 1;
        return;
    }

    int mid_x = (root->left + root->right) / 2;
    int mid_y = (root->floor + root->ceiling) / 2;

    if (x < mid_x && y < mid_y)
    {
        if (root->upper_left == nullptr)
            root->upper_left = new RoadBlock(root->left, mid_x, root->floor, mid_y);
        InsertBlock(root->upper_left, x, y);
    }

    if (x < mid_x && y >= mid_y)
    {
        if (root->lower_left == nullptr)
            root->lower_left = new RoadBlock(root->left, mid_x, mid_y, root->ceiling);
        InsertBlock(root->lower_left, x, y);
    }

    if (x >= mid_x && y < mid_y)
    {
        if (root->upper_right == nullptr)
            root->upper_right = new RoadBlock(mid_x, root->right, root->floor, mid_y);
        InsertBlock(root->upper_right, x, y);
    }

    if (x >= mid_x && y >= mid_y)
    {
        if (root->lower_right == nullptr)
            root->lower_right = new RoadBlock(mid_x, root->right, mid_y, root->ceiling);
        InsertBlock(root->lower_right, x, y);
    }

    root->UpdateCount();
}


void Game::DeleteBlock(RoadBlock* root, int x, int y)
{
    if (root == nullptr || root->count == 0)
        return;

    if (root->right - root->left == 1 && root->ceiling - root->floor == 1) {
        root->count = 0;
        return;
    }

    int mid_x = (root->left + root->right) / 2;
    int mid_y = (root->floor + root->ceiling) / 2;

    if (x < mid_x && y < mid_y)
        DeleteBlock(root->upper_left, x, y);

    if (x < mid_x && y >= mid_y)
        DeleteBlock(root->lower_left, x, y);

    if (x >= mid_x && y < mid_y)
        DeleteBlock(root->upper_right, x, y);

    if (x >= mid_x && y >= mid_y)
        DeleteBlock(root->lower_right, x, y);

    root->UpdateCount();
}

