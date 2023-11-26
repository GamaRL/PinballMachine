#include "../include/Device.h"
#include <AL/al.h>
#include <iostream>

Device * Device::_instance = nullptr;

Device* Device::get()
{
  if (Device::_instance == nullptr)
    Device::_instance = new Device();

	return Device::_instance;
}

Device::Device()
{
	_device = alcOpenDevice(nullptr); // nullptr = get default device
	if (!_device)
		throw("failed to get sound device");

	_context = alcCreateContext(_device, nullptr);  // create context
	if(!_context)
		throw("Failed to set sound context");

	if (!alcMakeContextCurrent(_context))   // make context current
		throw("failed to make context current");

	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(_device, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(_device, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(_device) != AL_NO_ERROR)
		name = alcGetString(_device, ALC_DEVICE_SPECIFIER);
}

void Device::clean()
{
  delete Device::_instance;
  Device::_instance = nullptr;
}

Device::~Device()
{
	alcMakeContextCurrent(nullptr);
  alcDestroyContext(_context);
	alcCloseDevice(_device);
}
