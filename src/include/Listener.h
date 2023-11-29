#pragma once

class Listener
{
public:
  static Listener * get()
  {
    static Listener * listener = new Listener();

    return listener;
  }
  void SetPosition(float, float, float);
private:
  Listener();
};
