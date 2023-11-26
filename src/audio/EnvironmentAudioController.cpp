#include "../include/EnvironmentAudioController.h"
#include "../include/Listener.h"

EnvironmentAudioController::EnvironmentAudioController()
{
  _source.SetLoop(true);
  _sound = Buffer::get()->addSoundEffect("resources/audio/perry_song.wav");
}

void EnvironmentAudioController::Play()
{
  _source.Play(_sound);
}
