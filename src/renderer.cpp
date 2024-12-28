#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <mutex>
#include "renderer.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::RenderBlock(std::unique_ptr<RoadBlock>& root, SDL_Rect *block)
{
    if (root == nullptr || root->count == 0)
        return;

    // Nếu là khối lá (leaf node), render nó
    if (root->right - root->left == 1 && root->ceiling - root->floor == 1)
    {
        block->x = root->left * block->w;
        block->y = root->floor * block->h;

        SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 255, 255); // Blue color for blocks
        SDL_RenderFillRect(sdl_renderer, block);
        return;
    }

    // Gọi đệ quy cho các khối con (không sử dụng std::move ở đây)
    RenderBlock(root->lower_left, block);
    RenderBlock(root->lower_right, block);
    RenderBlock(root->upper_left, block);
    RenderBlock(root->upper_right, block);
}

// Mutex để bảo vệ dữ liệu dùng chung nếu cần
std::mutex render_mutex;

void Renderer::Render(Snake const snake, SDL_Point const &food, std::unique_ptr<RoadBlock> &root) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Tạo promise và future để xử lý song song
    std::promise<void> snakePromise, roadBlockPromise;
    std::future<void> snakeFuture = snakePromise.get_future();
    std::future<void> roadBlockFuture = roadBlockPromise.get_future();

    // Thread 1: Render Snake
    std::thread snakeThread([&]() {
        std::lock_guard<std::mutex> lock(render_mutex); // Bảo vệ dữ liệu dùng chung nếu cần
        RenderSnake(snake, &block);
        snakePromise.set_value(); // Đánh dấu hoàn thành
    });

    // Thread 2: Render RoadBlock
    std::thread roadBlockThread([&]() {
        std::lock_guard<std::mutex> lock(render_mutex); // Bảo vệ dữ liệu dùng chung nếu cần
        RenderBlock(root, &block);
        roadBlockPromise.set_value(); // Đánh dấu hoàn thành
    });

    // Chờ cả hai thread hoàn thành
    snakeFuture.get();
    roadBlockFuture.get();

    // Render food (phần này xử lý ngay trong main thread)
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);

    // Join các thread
    if (snakeThread.joinable()) snakeThread.join();
    if (roadBlockThread.joinable()) roadBlockThread.join();
}
void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderSnake(Snake const &snake, SDL_Rect *block) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body) {
        block->x = point.x * block->w;
        block->y = point.y * block->h;
        SDL_RenderFillRect(sdl_renderer, block);
    }

    // Render snake's head
    block->x = static_cast<int>(snake.head_x) * block->w;
    block->y = static_cast<int>(snake.head_y) * block->h;
    if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, block);
}