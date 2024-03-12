#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class AudioManager
{
public:
	static AudioManager* getInstance();

	void playMusic(std::string fileName);
	void playSFX(std::string fileName);

	void setMusicVolume(float newVolume);
	void setSFXVolume(float newVolume);
	float getMusicVolume() { return _musicVolume; }
	float getSFXVolume() { return _sfxVolume; }
private:
	static AudioManager* _instance;

	float _musicVolume=0.1f, _sfxVolume=0.1f;

	int _bgmID;
};

#endif // !__AUDIO_MANAGER_H__