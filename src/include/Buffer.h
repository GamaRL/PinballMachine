#pragma once
#include <AL/al.h>
#include <vector>

class Buffer
{
public:
	static Buffer* get();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);

private:
	Buffer();
	~Buffer();

  static ALenum toALFormat(short channels, short samples);

	std::vector<ALuint> _soundBuffers;
};
