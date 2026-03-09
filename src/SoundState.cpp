#include "SoundState.h"

SoundState::SoundState()
{
    m_sound.setVolume(60.f);
}

SoundState::SoundState(const std::string& soundName, bool shouldLoop, float pitch)
    : SoundState() // Call default constructor first
{
    setSound(soundName, shouldLoop, pitch);
}

void SoundState::setSound(const std::string& soundName, bool shouldLoop, float pitch)
{
    m_sound.setBuffer(ResourcesManager::getInstance().getSound(soundName));
    m_sound.setLoop(shouldLoop);
    m_sound.setPitch(pitch);

    // Track the current sound settings
    m_savedSoundName = soundName;
    m_savedShouldLoop = shouldLoop;
    m_savedPitch = pitch;
}

void SoundState::play()
{
    m_sound.play();
    m_wasPlaying = true;
}

void SoundState::stop()
{
    m_sound.stop();
}

void SoundState::pause()
{
    m_sound.pause();
}

void SoundState::saveState()
{
    m_wasPlaying = (m_sound.getStatus() == sf::Sound::Playing);
}

void SoundState::restoreState()
{
    if (m_wasPlaying && !m_savedSoundName.empty())
    {
        setSound(m_savedSoundName, m_savedShouldLoop, m_savedPitch);
        play();
    }
}

void SoundState::reset()
{
    stop();
    m_wasPlaying = false;
    m_savedSoundName = "";
    m_savedShouldLoop = false;
    m_savedPitch = 1.0f;
}

bool SoundState::wasPlaying() const
{
    return m_wasPlaying;
}

void SoundState::setVolume(const float amount)
{
    m_sound.setVolume(amount);
}
