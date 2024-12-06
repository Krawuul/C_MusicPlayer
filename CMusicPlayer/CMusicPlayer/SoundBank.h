#pragma once

#include <string>
#include <vector>

public enum FILE_EXTENSION
{
	WAW = 0,
	OGG = 1,
};

struct SoundData 
{
	SoundData(const std::string& _path, const std::string& _name, FILE_EXTENSION _extension)
		: path(_path),
		name(_name),
		extension(_extension)
	{
	}

	inline const std::string& GetPath() { return path; }
	inline const std::string& GetName() { return name; }
	inline const FILE_EXTENSION GetExtension() { return extension; }

	std::string path = "";
	std::string name = "";
	FILE_EXTENSION extension;
};

class SoundBank
{
public:

	SoundBank();
	~SoundBank();

	void AddSound(SoundData& _sound);
	void RemoveSound(SoundData& _sound);

	const SoundData& GetCurrentSound();
	void Next();
	void Previous();
	const std::vector<SoundData>& GetSounds();

	void SaveBank(const std::string& _path);
	void LoadBank(const std::string& _path);
	bool OnStartLoad();

private:

	int CheckLoop(int _id);

private:
	std::vector<SoundData> sounds;
	int playIndex;
};
