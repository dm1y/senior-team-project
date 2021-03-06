#ifndef __SOUNDCHUNK_H
#define __SOUNDCHUNK_H

#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <string>
#include <stdexcept>




class SoundChunk
{
public:
	SoundChunk(Mix_Chunk* c);
	SoundChunk(std::string path);
	~SoundChunk();
	void fadeIn(int ms, bool repeat);
	void fadeOut(int ms);
	void play();
protected:
	Mix_Chunk* mChunk;
	int mCurrentChanel;
};



class SoundBank {
public:
	static void shutdown();
	static SoundBank* getInstance();

	void setup();
	void play(std::string id);
	void addSound(SoundChunk* s, std::string id, int index);
	void removeSound(std::string id);
	void openFile(std::string path, std::string id, int index);
	void free();
	void fadeIn(std::string id, int ms, bool repeat);
    void fadeOut(std::string id, int ms);
	bool getEnableSound() { return mSoundEnabled; }
	void setEnableSound(bool newVal) { mSoundEnabled = newVal; }
	int getVolume() { return mVolume;}
	void setVolume(int newVol);
	int getCurrentIndex() { return mSoundIndex; }
	void setCurrentIndex(int newIndex) {if (newIndex < mNumSounds) mSoundIndex = newIndex; }



private:
	std::vector<std::map<std::string, SoundChunk*>> mChunks;
	static SoundBank* instance;
	SoundBank();
	~SoundBank();
	bool mHasBeenSetup;
	bool mSoundEnabled;
	int mVolume;
	int mSoundIndex;
	int mNumSounds;
	bool mSoundAvailable;
};

#endif