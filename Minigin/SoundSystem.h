#pragma once
#include <thread>

#include "AudioClip.h"
#include "SDL_mixer.h"

using soundId = unsigned short;

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const soundId, const float) {};
	virtual void StartSoundThread() {  };

protected:
	std::thread m_SoundThread;
};

class NullSoundSystem : public SoundSystem
{
	void Play(const soundId /*id*/, const float /*volume*/) override {}
};

class LoggingSoundSystem final : public SoundSystem
{
	SoundSystem* RealSS;
public:
	LoggingSoundSystem(SoundSystem* ss) : RealSS(ss) {}
	~LoggingSoundSystem() { delete RealSS; }

	void Play(const soundId id, const float volume) override { RealSS->Play(id, volume); };
};

class ServiceLocator final
{
	static SoundSystem* ssInstance;
	static NullSoundSystem defaultSS;

public:
	static SoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(SoundSystem* ss);
};

class SDLSoundSystem : public SoundSystem
{
public:
	void Play(const soundId id, const float volume) override;
	virtual void StartSoundThread() {
		m_SoundThread = std::thread(&SDLSoundSystem::Update, this);
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	};
	int AddAudioClip(std::string path, float volume);
	~SDLSoundSystem();
private:
	void Update();
	void StartUpdating();
	std::vector<AudioClip> m_AudioClips
	{
		AudioClip("Resources/Audio/sample.wav",100)
	};
	static const int m_MaxPending = 16;
	std::atomic<int> m_NrPending;
	int m_Pending[m_MaxPending];
	bool m_ThreadStarted = false;
	std::thread m_SoundThread;
};
