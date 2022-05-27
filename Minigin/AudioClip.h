#pragma once
#include <SDL_mixer.h>
#include <thread>
#include <mutex>

class AudioClip
{
public:

	AudioClip() = default;
	AudioClip(std::string path, float volume, int loops = 0);
	AudioClip(const AudioClip& other)
	{
		m_Loaded = other.m_Loaded;
		m_Path = other.m_Path;
		m_Volume = other.m_Volume;
		m_File = other.m_File;
		m_Loops = other.m_Loops;
	}
	//AudioClip(AudioClip&& other) noexcept = delete;
	//AudioClip& operator=(const AudioClip& other) = delete;
	//AudioClip& operator=(AudioClip&& other) noexcept = delete;

	~AudioClip() = default;

	void Play();
	void SetVolume(const float vol);
	void CleanUp()
	{
		Mix_FreeChunk(m_File);
	}

private:
	bool m_Loaded = false;
	std::string m_Path = "";
	float m_Volume = 100;
	std::mutex m_Mutex;
	Mix_Chunk* m_File;
	int m_Loops = 0;
};
