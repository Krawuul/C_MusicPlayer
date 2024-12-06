#include "SoundBank.h"

#include <fstream>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

SoundBank::SoundBank()
	: sounds(),
	playIndex(0)
{
}

SoundBank::~SoundBank()
{
	sounds.clear();
}

void SoundBank::AddSound(SoundData& _sound)
{
	for (SoundData& s : sounds) 
	{
		if (_sound.GetName() == s.GetName())
		{
			return;
		}
	}

	sounds.emplace_back(_sound);
}

void SoundBank::RemoveSound(SoundData& _sound)
{
}

const SoundData& SoundBank::GetCurrentSound()
{
	playIndex = CheckLoop(playIndex);
	return sounds[playIndex];
}

void SoundBank::Next()
{
	playIndex++;
	playIndex = CheckLoop(playIndex);
}

void SoundBank::Previous()
{
	playIndex--;
	playIndex = CheckLoop(playIndex);
}

const std::vector<SoundData>& SoundBank::GetSounds()
{
	return sounds;
}

void SoundBank::SaveBank(const std::string& _path)
{
	std::ofstream ofs(_path, std::ios::binary);
	if (!ofs) 
	{
		return;
	}

	size_t sNumb = sounds.size();
	ofs.write(reinterpret_cast<const char*>(&sNumb), sizeof(size_t));

	for (size_t i = 0; i < sounds.size(); i++)
	{
		size_t pSize = sounds[i].GetPath().size();
		size_t nSize = sounds[i].GetName().size();
		int ext = sounds[i].GetExtension();

		ofs.write(reinterpret_cast<const char*>(&pSize), sizeof(size_t));
		ofs.write(sounds[i].GetPath().data(), sizeof(char) * pSize);

		ofs.write(reinterpret_cast<const char*>(&nSize), sizeof(size_t));
		ofs.write(sounds[i].GetName().data(), sizeof(char) * nSize);

		ofs.write(reinterpret_cast<const char*>(&ext), sizeof(int));
	}

	ofs.close();
}

void SoundBank::LoadBank(const std::string& _path)
{
	std::ifstream ifs(_path, std::ios::binary);
	if (!ifs)
	{
		return;
	}

	size_t sNumb = 0;
	ifs.read(reinterpret_cast<char*>(&sNumb), sizeof(size_t));

	for (size_t i = 0; i < sNumb; i++)
	{
		size_t pSize = 0;
		size_t nSize = 0;
		int ext = 0;

		ifs.read(reinterpret_cast<char*>(&pSize), sizeof(size_t));
		std::string path(pSize, '\0');
		ifs.read(&path[0], sizeof(char) * pSize);

		ifs.read(reinterpret_cast<char*>(&nSize), sizeof(size_t));
		std::string name(nSize, '\0');
		ifs.read(&name[0], sizeof(char) * nSize);

		ifs.read(reinterpret_cast<char*>(&ext), sizeof(int));

		SoundData nsd = SoundData(path, name, (FILE_EXTENSION)ext);
		AddSound(nsd);
	}

	ifs.close();
}

bool SoundBank::OnStartLoad()
{
	for (const auto& entry : std::experimental::filesystem::directory_iterator("../Save/"))
	{
		LoadBank(entry.path().string());
		return true;
	}
	return false;
}

int SoundBank::CheckLoop(int _id)
{
	if (_id < 0) 
	{
		return sounds.size()-1;
	}
	else if (_id >= sounds.size()) 
	{
		return 0;
	}
	else 
	{
		return _id;
	}
}
