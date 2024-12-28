#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

// Destructor
Snake::~Snake() {
  // Do nothing because std::vector auto release resource
}

// Copy Constructor
Snake::Snake(const Snake &other)
    : grid_width(other.grid_width),
      grid_height(other.grid_height),
      head_x(other.head_x),
      head_y(other.head_y),
      body(other.body),
      direction(other.direction),
      speed(other.speed),
      size(other.size),
      alive(other.alive),
      growing(other.growing) {}

// Copy Assignment Operator
Snake &Snake::operator=(const Snake &other) {
  if (this == &other) {
    return *this;
  }

  // Sao chép dữ liệu
  grid_width = other.grid_width;
  grid_height = other.grid_height;
  head_x = other.head_x;
  head_y = other.head_y;
  body = other.body;  // std::vector hỗ trợ copy assignment.
  direction = other.direction;
  speed = other.speed;
  size = other.size;
  alive = other.alive;
  growing = other.growing;

  return *this;
}

// Move Constructor
Snake::Snake(Snake &&other) noexcept
    : grid_width(other.grid_width),
      grid_height(other.grid_height),
      head_x(other.head_x),
      head_y(other.head_y),
      body(std::move(other.body)),
      direction(other.direction),
      speed(other.speed),
      size(other.size),
      alive(other.alive),
      growing(other.growing) {
  // Đặt trạng thái của `other` về giá trị mặc định.
  other.head_x = 0.0f;
  other.head_y = 0.0f;
  other.size = 1;
  other.alive = true;
  other.growing = false;
}

// Move Assignment Operator
Snake &Snake::operator=(Snake &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  // Chuyển tài nguyên
  grid_width = other.grid_width;
  grid_height = other.grid_height;
  head_x = other.head_x;
  head_y = other.head_y;
  body = std::move(other.body);  // Di chuyển tài nguyên.
  direction = other.direction;
  speed = other.speed;
  size = other.size;
  alive = other.alive;
  growing = other.growing;

  // Đặt trạng thái của `other` về giá trị mặc định.
  other.head_x = 0.0f;
  other.head_y = 0.0f;
  other.size = 1;
  other.alive = true;
  other.growing = false;

  return *this;
}