#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <thread>
#include <future>
#include <mutex>
#include "SDL.h"
#include "snake.h"
#include "roadblock.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  // Hàm public
  void Render(Snake const snake, SDL_Point const &food, std::unique_ptr<RoadBlock>& root);
  void UpdateWindowTitle(int score, int fps);

 private:
  // Cửa sổ và bộ render SDL
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  // Kích thước màn hình và lưới
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  // Hàm private cho các thành phần render
  void RenderSnake(Snake const &snake, SDL_Rect *block);
  void RenderBlock(std::unique_ptr<RoadBlock>& root, SDL_Rect *block);

  // Mutex để bảo vệ dữ liệu dùng chung
  std::mutex render_mutex;
};

#endif