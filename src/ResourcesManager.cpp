#include "ResourcesManager.h"
#include "Exceptions.h"

sf::Music& ResourcesManager::getMusic(const std::string name)
{
	auto it = m_music.find(name);

	if (it == m_music.end())
		throw ResourceNotFoundException("Music not found: " + name);

	return *(it->second);
}

sf::SoundBuffer& ResourcesManager::getSound(const std::string name)
{
	auto it = m_sounds.find(name);

	if (it == m_sounds.end())
		throw ResourceNotFoundException("Sound not found: " + name);

	return it->second;
}

ResourcesManager::ResourcesManager()
{
	try {
		loadTextures();
		loadFont();
		setSounds();
		setMusic();
		setIconImage();
	}
	catch (const std::exception& e) {
		throw ResourceLoadException("Failed to initialize ResourcesManager: " + std::string(e.what()));
	}
}

void ResourcesManager::loadTextures()
{
    std::vector<std::pair<std::string, std::string>> textures =
	{
		{"OpenningBackground", "OpenningBackground.jpg"},
		{"StartOfGameCover", "StartOfGameCover.png"},
		{"Hall", "Hall.png"},
		{"StartOfHallExplosion", "StartOfHallExplosion.png"},
		{"BerryDead", "BerryDead.png"},
		{"BerryHit", "BerryHit.png"},
		{"BerryWalking", "BerryWalking.png"},
		{"Flame", "Flame.png"},
		{"Coin", "Coin.png"},
		{"LaserBeam", "LaserBeam.png"},
		{"LaserHead", "LaserHead.png"},
		{"WallLamp", "WallLamp.png"},
		{"Missile", "Missile.png"},
		{"FirstAlarmWarning", "FirstAlarmWarning.png"},
		{"SecondAlarmWarning", "SecondAlarmWarning.png"},
		{"upsideDownState", "upsideDownState.png"},
		{ "RobotState", "RobotState.png" },
		{ "PowerUpBox", "PowerUpBox.png" },
		{ "Chicken", "Chicken.png" },
		{ "Egg", "Egg.png"},
		{ "Bat", "Bat.png" },
		{ "Waves", "Waves.png" },
		{ "GasTank", "GasTank.png" },
		{ "BirdFlying", "BirdFlying.png"},
		{ "DinoWalking", "DinoWalking.png"},
		{ "DinoJumping", "DinoJumping.png"},
		{ "Sparkle", "Sparkle.png"},
		{ "Scientist", "Scientist.png"},
		{ "Dollar", "Dollar.png"},
		{ "Meat", "Meat.png"},
		{ "DinoFire", "DinoFire.png"},
		{ "DinoWings", "DinoWings.png"},
		{ "Wave", "Wave.png"},
		{ "Surfing", "Surfing.png"},
		{ "Bubble", "Bubble.png"},
		{ "Shell", "Shell.png"},
		{ "Pearl", "Pearl.png"},
		{"GameMenu", "GameMenu.png"},
		{"GameSettingButton","GameSettingButton.png"},
		{"HelpOff","HelpOff.png"},
		{"HelpOn", "HelpOn.png"},
		{"PlayGameOff", "PlayGameOff.png"},
		{"PlayGameOn", "PlayGameOn.png"},
		{"Crab","Crab.png"},
		{"Fish1","Fish1.png"},
		{"Fish2","Fish2.png"},
		{"JellyFish1","JellyFish1.png"},
		{"JellyFish2","JellyFish2.png"},
		{"Squid1", "Squid1.png"},
		{"Squid2","Squid2.png"},
		{"Shark","Shark.png"},
		{"TrophyButton","TrophyButton.png"},
		{ "Pearl", "Pearl.png"},
		{ "Piranha", "Piranha.png"},
		{ "Light", "Light.png"},
		{ "QuitOff", "QuitOff.png"},
		{ "QuitOn", "QuitOn.png"},
		{ "MuteOn", "MuteOn.png"},
		{ "MuteOff", "MuteOff.png"},
		{ "ArrowButton", "ArrowButton.png"},
		{ "HelpPage1", "HelpPage1.png"},
		{ "HelpPage2", "HelpPage2.png"},
		{ "HelpPage3", "HelpPage3.png"},
		{ "HelpPage4", "HelpPage4.png"},
		{ "HelpPage5", "HelpPage5.png"},
		{ "ReturnToMenuButton", "ReturnToMenuButton.png"},
		{ "RetryButton", "RetryButton.png"},
		{ "ResumeButton", "ResumeButton.png"},
		{ "QuitButton", "QuitButton.png"},
		{ "Hourglass", "Hourglass.png"},
		{ "KingBarry", "KingBarry.png"},
		{ "ScientistSwim", "ScientistSwim.png"},
		{ "GameIcon", "GameIcon.png"}
	};

	for (const auto& [name, path] : textures)
	{
		sf::Texture t;

		if (!t.loadFromFile(path))
			throw ResourceLoadException("Failed to load texture: " + path);

		m_textures[name] = t;
	}
}

void ResourcesManager::loadFont()
{
	if (!m_font.loadFromFile("Jetpackia.ttf"))
		throw ResourceLoadException("Failed to load font: Jetpackia.ttf");
}

void ResourcesManager::setSounds()
{
	std::vector<std::pair<std::string, std::string>> sounds =
	{
		{"ButtonSound", "ButtonSound.ogg"},
		{"HoverButtonSound", "HoverButtonSound.ogg"},
		{"RegularStateRunSound", "RegularStateRunSound.ogg"},
		{"EngineSound", "EngineSound.ogg"},
		{"Coin", "Coin.ogg"},
		{"ZapperSound", "ZapperSound.ogg"},
		{"EggSound", "EggSound.ogg"},
		{"BatSound", "BatSound.ogg"},
		{"MissileAlarm", "MissileAlarm.ogg"},
		{"MissileExplode", "MissileExplode.ogg"},
		{"MissileLaunch","MissileLaunch.ogg"},
		{"PowerUpSound", "PowerUpSound.ogg"},
		{"RobotEngineSound", "RobotEngineSound.ogg"},
		{"RobotRunSound", "RobotRunSound.ogg"},
		{"SpecialGiftSound", "SpecialGiftSound.ogg"},
		{"DinoRoar", "DinoRoar.ogg"},
		{"DinoWalkSound", "DinoWalkSound.ogg"},
		{"DinoWingsSound", "DinoWingsSound.ogg"},
		{"ShellSound", "ShellSound.ogg"},
		{"FlipDown", "FlipDown.ogg"},
		{"FlipUp", "FlipUp.ogg"},
		{"BirdFlap", "BirdFlap.ogg"},
		{"BirdLanding", "BirdLanding.ogg"},
		{"BirdSlide", "BirdSlide.ogg"},
		{"BirdYippie", "BirdYippie.ogg"},
		{"ChickenSound", "ChickenSound.ogg"},
		{"StartingExplosion", "StartingExplosion.ogg"},
		{"DinoJump", "DinoJump.ogg"},
		{ "CrabSound", "CrabSound.ogg" },
		{ "PiranhaSound", "PiranhaSound.ogg" },
		{ "SwimSound", "SwimSound.ogg" },
		{ "Jaws", "Jaws.ogg" },
		{ "BiteSound", "BiteSound.ogg" },
		{ "BubbleSound", "BubbleSound.ogg" },
		{ "SparkleSound", "SparkleSound.ogg" },
		{ "JumpToWaterSound", "JumpToWaterSound.ogg" },
		{ "HitSound", "HitSound.ogg" },
		{ "OuchSound", "OuchSound.ogg" }
	};

	for (const auto& [name, path] : sounds)
	{
		sf::SoundBuffer s;

		if (!s.loadFromFile(path))
			throw ResourceLoadException("Failed to load sound: " + path);

		m_sounds[name] = s;
	}
}

void ResourcesManager::setMusic()
{
	std::vector<std::pair<std::string, std::string>> music =
	{
		{"HelpMusic", "HelpMusic.ogg"},
		{"MenuMusic", "MenuMusic.ogg"},
		{"ScoreBoardMusic", "ScoreBoardMusic.ogg"},
		{"JetpackJoyrideMusic", "JetpackJoyrideMusic.ogg"},
		{"SeaWaves", "SeaWaves.ogg"},
		{"SeaStateSound", "SeaStateSound.ogg"},
		{"GameOverMusic", "GameOverMusic.ogg"}
	};

	for (const auto& [name, path] : music)
	{
		auto m = std::make_unique<sf::Music>();

		if (!m->openFromFile(path))
			throw ResourceLoadException("Failed to load music: " + path);

		m_music[name] = std::move(m);
	}
}

void ResourcesManager::setIconImage()
{
	if (!m_iconImage.loadFromFile("GameIcon.png"))
		throw ResourceLoadException("Failed to load window icon: GameIcon.png");
}

ResourcesManager& ResourcesManager::getInstance()
{
	static ResourcesManager inst;

	return inst;
}

const sf::Texture& ResourcesManager::getTexture(const std::string name) const
{
	auto it = m_textures.find(name);

	if (it == m_textures.end())
		throw ResourceNotFoundException("Texture not found: " + name);

	return it->second;
}

const sf::Font& ResourcesManager::getFont() const
{
	return m_font;
}

const sf::Image& ResourcesManager::getIconImage() const
{
	return m_iconImage;
}
