#pragma once

#include "./Window.h"
#include "./Flipper.h"

/**
 * Controla el comportamiento de un Flipper
 * según las teclas J (izquierdo) y K (derecho)
 */
class FlipperKeyController
{
  public:
    FlipperKeyController(Window* window);
    void Handle(Flipper *flipper, float dt);
  private:
    Window* _window;
};
