#include "../include/SpringAudioController.h"

SpringAudioController::SpringAudioController()
{
  _source.SetPosition(43.5f, 3.0f, 80.0f);
  _sound = Buffer::get()->addSoundEffect("resources/audio/boing_poing.wav");
}

void SpringAudioController::Play()
{
  _source.Play(_sound);
}
