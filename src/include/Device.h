#pragma once
#include <AL/alc.h>

class Device
{
public:
	static Device* get();
  static void clean();

private:
	Device();
	~Device();

  static Device * _instance;

	ALCdevice* _device;
	ALCcontext* _context;
};
