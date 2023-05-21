#pragma once

namespace platform {

class Window {
 public:
  static void Initialize(int width, int height);

  static void Finalize();

  static bool Continue();

  static void BeginDraw();

  static void DrawRectangle(float x, float y, float r);

  static void EndDraw();
};

}  // namespace platform