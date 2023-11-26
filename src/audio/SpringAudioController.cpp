#include "../include/SpringAudioController.h"

SpringAudioController::SpringAudioController()
{
  _sound = Buffer::get()->addSoundEffect("resources/audio/boing_poing.wav");
}

void SpringAudioController::Play()
{
  _source.Play(_sound);
}
