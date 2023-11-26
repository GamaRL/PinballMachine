#include "../include/Buffer.h"
#include <cstdio>
#include <cstdlib>
#include <audio/wave.h>
#include <AL/alext.h>

Buffer* Buffer::get()
{
	static Buffer* sndbuf = new Buffer();
	return sndbuf;
}

ALuint Buffer::addSoundEffect(const char* filename)
{
  WaveInfo *wave;
  char *bufferData;
  int ret;

  wave = WaveOpenFileForReading(filename);
  if (!wave)
  {
    fprintf(stderr, "failed to read wave file\n");
    return -1;
  }

  ret = WaveSeekFile(0, wave);
  if (ret)
  {
    fprintf(stderr, "failed to seek wave file\n");
    return -1;
  }

  bufferData = (char*)malloc(wave->dataSize);
  if (!bufferData)
  {
    perror("malloc");
    return -1;
  }

  ret = WaveReadFile(bufferData, wave->dataSize, wave);
  if (ret != wave->dataSize)
  {
    fprintf(stderr, "short read: %d, want: %d\n", ret, wave->dataSize);
    return -1;
  }
  ALuint buffer = 0;
  alGenBuffers(1, &buffer);

  alBufferData(buffer, toALFormat(wave->channels, wave->bitsPerSample),
      bufferData, wave->dataSize, wave->sampleRate);


  /* Check if an error occured, and clean up if so. */
  auto err = alGetError();
  if (err != AL_NO_ERROR)
  {
    fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
    if (buffer && alIsBuffer(buffer))
      alDeleteBuffers(1, &buffer);
    return 0;
  }
  free(bufferData);

  _soundBuffers.push_back(buffer);  // add to the list of known buffers

  return buffer;
}

ALenum Buffer::toALFormat(short channels, short samples)
{
  bool stereo = (channels > 1);

  switch (samples) {
    case 16:
      if (stereo)
        return AL_FORMAT_STEREO16;
      else
        return AL_FORMAT_MONO16;
    case 8:
      if (stereo)
        return AL_FORMAT_STEREO8;
      else
        return AL_FORMAT_MONO8;
    default:
      return -1;
  }
}

bool Buffer::removeSoundEffect(const ALuint& buffer)
{
  auto it = _soundBuffers.begin();
  while (it != _soundBuffers.end())
  {
    if (*it == buffer)
    {
      alDeleteBuffers(1, &*it);

      it = _soundBuffers.erase(it);

      return true;
    }
    else {
      ++it;
    }
  }
  return false;  // couldn't find to remove
}


Buffer::Buffer()
{
  _soundBuffers.clear();

}

Buffer::~Buffer()
{
  alDeleteBuffers(_soundBuffers.size(), _soundBuffers.data());

  _soundBuffers.clear();
}
