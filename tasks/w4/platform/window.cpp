#include <platform/window.hpp>

#include <cmath>

#include <raylib.h>

namespace platform {

namespace detail {

float g_width;
float g_height;

Camera2D g_camera;

}  // namespace detail

void Window::Initialize(int width, int height) {
  InitWindow(width, height, "w4 networked MIPT");

  SetTargetFPS(60);

  detail::g_width = static_cast<float>(width);
  detail::g_height = static_cast<float>(height);

  detail::g_camera = { {0, 0}, {0, 0}, 0.f, 1.f };
  detail::g_camera.target = Vector2{ 0.f, 0.f };
  detail::g_camera.offset = Vector2{ width * 0.5f, height * 0.5f };
  detail::g_camera.rotation = 0.f;
  detail::g_camera.zoom = 1.f;
}

void Window::Finalize() {
  CloseWindow();
}

bool Window::Continue() {
  return !WindowShouldClose();
}

void Window::BeginDraw() {
  BeginDrawing();
  ClearBackground(BLUE);
  BeginMode2D(detail::g_camera);
}

void Window::DrawRectangle(float x, float y, float r) {
  Rectangle rectangle = {
    (x - 0.5f) * detail::g_width - r * 2 * std::sqrt(detail::g_width * detail::g_height),
    (y - 0.5f) * detail::g_height - r * 2 * std::sqrt(detail::g_width * detail::g_height) ,
    r * 4 * std::sqrt(detail::g_width * detail::g_height),
    r * 4 * std::sqrt(detail::g_width * detail::g_height)
  };
  DrawRectangleRec(rectangle, YELLOW);
}

void Window::EndDraw() {
  EndMode2D();
  EndDrawing();
}

}  // namespace platform