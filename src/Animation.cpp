#include "Animation.h"
#include "GameState.h"

Animation::Animation(sf::Sprite& sprite, const GameObjectParams& params)
	: m_givenFrameTime(params._frameTime), m_loop(params._loop),
	  m_sprite(sprite), m_startFrame(params._startFrame),
	  m_endFrame(params._endFrame), m_curFrameNum(params._startFrame),
	  m_totalFrameCount(params._countFrames)
{
	m_actualFrameCount = m_endFrame - m_startFrame + 1;

	m_frameWidth = m_sprite.getTexture()->getSize().x / m_totalFrameCount;

	m_frameHeight = m_sprite.getTexture()->getSize().y;

	updateFrame();
}

void Animation::update(const float deltaTime)
// Updates the animation frame based on elapsed time and handles looping or stopping.
{
	if (!m_playing) return;

	m_elapsedTime += deltaTime;

	if (m_elapsedTime >= m_givenFrameTime)
	{
		m_elapsedTime = 0.f;

		m_curFrameNum++;

		if (m_curFrameNum >= m_actualFrameCount)
		{
			if (m_loop)
				m_curFrameNum = m_startFrame;
			else
			{
				m_curFrameNum = m_endFrame;

				m_playing = false;
			}
		}

		updateFrame();
	}
}

void Animation::setAnimation(const GameObjectParams& params)
// Sets a new animation configuration and resets frame data.
{
	auto& inst = ResourcesManager::getInstance();

	m_sprite.setTexture(inst.getTexture(params._textureName));

	m_givenFrameTime = params._frameTime;
	m_loop = params._loop;
	m_playing = true;

	m_startFrame = params._startFrame;
	m_endFrame = params._endFrame;
	m_curFrameNum = params._startFrame;

	m_totalFrameCount = params._countFrames;
	m_actualFrameCount = m_endFrame - m_startFrame + 1;

	m_frameWidth = m_sprite.getTexture()->getSize().x / m_totalFrameCount;
	m_frameHeight = m_sprite.getTexture()->getSize().y;

	updateFrame();
}

void Animation::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

bool Animation::isPlaying() const
{
	return m_playing;
}

void Animation::play()
{
	m_playing = true;
}

void Animation::stop()
{
	m_playing = false;
}

void Animation::reset()
{
	m_curFrameNum = m_startFrame;
	m_elapsedTime = 0.0f;
	updateFrame();
}

void Animation::setFrameTime(const float frameTime)
{
	m_elapsedTime = 0.0f;
	m_givenFrameTime = frameTime;
}

int Animation::getCurFrameNum() const
{
	return m_curFrameNum;
}

bool Animation::isAtLastFrame() const
{
	return (m_curFrameNum == m_endFrame);
}

void Animation::updateFrame()
{
	m_sprite.setTextureRect(sf::IntRect(m_curFrameNum * m_frameWidth,
										0, m_frameWidth, m_frameHeight));
}
