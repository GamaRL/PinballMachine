#include "../include/BallAnimation.h"
#include <glm/detail/qualifier.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>

BallAnimation::BallAnimation(Ball *ball, Window *window)
{
  _ball = ball;
  _window = window;
  _isRunning = false;

  Reset();
}

void BallAnimation::HandleStart()
{
  if (_window->IsRightButtonPressed())
  {
    Reset();
    _isRunning = true;
  }
}

void BallAnimation::Reset()
{
  _position = glm::vec3(43.0f, 3.0f, 70.0f);
  _velocity = glm::vec3(0.0f, 0.0f, -150.0f);

  _states[0] = true;
  _states[1] = false;
  _states[2] = false;
  _states[3] = false;
  _states[4] = false;
  _states[5] = false;
  _states[6] = false;
}

void BallAnimation::Update(float dt)
{
  const int NUM_INTER = 10;
  const glm::vec3 gravity = glm::vec3(0.0f, 0.0f, 15.0f);
  if (_isRunning)
  {
    if (_states[0])
    {
      for (int i = 0; i < NUM_INTER; i++)
      {
        _position += _velocity * dt / static_cast<float>(NUM_INTER);
      }

      if (_position.z <= -42.0f)
      {
        _states[0] = false;
        _states[1] = true;
      }
    }
    else if (_states[1])
    {
      for (int i = 0; i < NUM_INTER; i++)
      {
        float ball_rot_acc = glm::pow(glm::length(_velocity), 2) / 37.0f;
        glm::vec3 acceleration = gravity + glm::normalize(glm::vec3(0.0f, 3.0f, -30.0f) - _position) * ball_rot_acc;
        if (_position.y >= 0)
          acceleration.y = -5.1; // Bajar pelota al nivel del suelo
        _velocity += acceleration * dt / static_cast<float>(NUM_INTER);
        _position += _velocity * dt / static_cast<float>(NUM_INTER);
      }

      if (_position.z > -42.0f)
      {
        float magnitude = glm::length(_velocity);
        _velocity = glm::normalize(glm::vec3(1.0f, 0.0f, -1.0f)) * magnitude * 0.15f;

        _states[1] = false;
        _states[2] = true;
      }
    }
    else if (_states[2])
    {
      for (int i = 0; i < NUM_INTER; i++)
      {
        glm::vec3 acceleration = gravity;
        _velocity += acceleration * dt / static_cast<float>(NUM_INTER);
        _position += _velocity * dt / static_cast<float>(NUM_INTER);
      }

      if (_position.x > 40.0f)
      {
        _velocity.x = 0.0f;
        _states[2] = false;
        _states[3] = true;
      }
    }
    else if (_states[3])
    {
      for (int i = 0; i < NUM_INTER; i++)
      {
        glm::vec3 acceleration = gravity;
        _velocity += acceleration * dt / static_cast<float>(NUM_INTER);
        _position += _velocity * dt / static_cast<float>(NUM_INTER);
      }

      if (_position.z > 40.0f)
      {
        float magnitude = glm::length(_velocity);
        _velocity = glm::normalize(glm::vec3(-1.0f, 0.0f, -0.5f)) * magnitude * 0.6f;

        _states[3] = false;
        _states[4] = true;
      }
    }
    else if (_states[4])
    {
      for (int i = 0; i < NUM_INTER; i++)
      {
        glm::vec3 acceleration = gravity;
        _velocity += acceleration * dt / static_cast<float>(NUM_INTER);
        _position += _velocity * dt / static_cast<float>(NUM_INTER);
      }

      if (_position.z > 48.0f)
      {
        float magnitude = glm::length(_velocity);
        _velocity = glm::normalize(glm::vec3(1.0f, 0.0f, -1.0f)) * magnitude * 0.5f;

        _velocity *= 0.8;
        _states[4] = false;
        _states[5] = true;
      }
    }
    else if (_states[5])
    {
      for (int i = 0; i < NUM_INTER; i++)
      {
        glm::vec3 acceleration = gravity;
        _velocity += acceleration * dt / static_cast<float>(NUM_INTER);
        _position += _velocity * dt / static_cast<float>(NUM_INTER);
      }

      if (_position.z > 82.5f)
      {
        _velocity = glm::vec3(10.0f, 0.0f, 0.0f);

        _velocity *= 0.8;
        _states[5] = false;
        _states[6] = true;
      }
    }
    else if (_states[6])
    {
      for (int i = 0; i < NUM_INTER; i++)
      {
        _position += _velocity * dt / static_cast<float>(NUM_INTER);
      }

      if (_position.x >= 40.0f)
      {
        _isRunning = false;
      }
    }
  }
  _ball->SetPosition(_position.x, _position.y, _position.z);
}
