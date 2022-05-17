#pragma once

class SoundScene
{
public:
	SoundScene();
	~SoundScene();
	SoundScene(const SoundScene& other) = delete;
	SoundScene(SoundScene&& other) noexcept = delete;
	SoundScene& operator=(const SoundScene& other) = delete;
	SoundScene& operator=(SoundScene&& other) noexcept = delete;

private:
};
