#pragma once

#include "al.h"
#include "alc.h"
#include "vorbis/vorbisfile.h"
#include "vorbis/codec.h"
#include <chrono>
#include <thread>
#include <vector>
#include <Framework.h>
#include <string>
#include "SoundBank.h"


#define AUDIO_PATH "..\\Sounds\\Ruisseau_Escattes_01.wav"
#define AUDIO_PATH2 "..\\Sounds\\Arsonist.ogg"
#define BUFFER_SIZE 4096
#define NUM_BUFFERS 3

ref class MusicPlayer
{
public:
	MusicPlayer()
	{
		ALFWInit();

		if (!ALFWInitOpenAL())
		{
			ALFWprintf("ALFW not initialized!");
			ALFWShutdown();
			return;
		}
		if (uiBuffer == nullptr) {
			uiBuffer = new ALuint();
		}
		if (uiSource == nullptr) {
			uiSource = new ALuint();
		}
		if (iState == nullptr) {
			iState = new ALint();
		}

		soundBank = new SoundBank();
		soundBank->OnStartLoad();
	}
private:
	ALuint* uiBuffer;
	ALuint* uiSource;
	ALint* iState;
	OggVorbis_File* Stream;
	FILE* File = NULL;
	ALenum         Format = 0;
	ALsizei        SampleRate = 0;
	bool canPlay = false;
	bool isOgg = false;
	ALuint* buffers;
	SoundBank* soundBank;

public: void PlayWav(const std::string& filepath)
{
	if ((*iState != AL_PLAYING) && (*iState != AL_PAUSED))
	{
		isOgg = false;
		*iState = AL_PLAYING;
		
		alGenBuffers(1, uiBuffer);

		if (!ALFWLoadWaveToBuffer(filepath.c_str(), *uiBuffer))
		{
			ALFWprintf("Sound not found! at : %s", filepath);
		}

		alGenSources(1, uiSource);

		alSourcei(*uiSource, AL_BUFFER, *uiBuffer);

		alSourcePlay(*uiSource);
		ALFWprintf("Playing source!");


		canPlay = false;
	}
}



public:
	bool OpenOgg(const std::string& Filename)
	{
		// Ouverture du fichier
		File = fopen(Filename.c_str(), "rb");
		if (!File)
			return false;

		// On ouvre un flux ogg-vorbis à partir du fichier que l'on vient d'ouvrir
		int Error = ov_open(File, Stream, NULL, 0);
		if (Error < 0)
			return false;

		// Récupération des informations du son
		vorbis_info* Infos = ov_info(Stream, -1);
		Format = Infos->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		SampleRate = Infos->rate;

		return true;
	}
	void CloseOgg()
	{
		// Fermeture du flux ogg-vorbis
		ov_clear(Stream);

		// Fermeture du fichier
		fclose(File);
	}
public:
	void ReadOgg(ALuint Buffer, ALsizei NbSamples)
	{
		// Tableau qui va recevoir les échantillons lus
		std::vector<ALshort> Samples(NbSamples);

		// Définition de variables utiles à la lecture
		ALsizei TotalRead = 0;
		ALsizei TotalSize = NbSamples * sizeof(ALshort);
		char* SamplesPtr = reinterpret_cast<char*>(&Samples[0]);

		// Tant qu'on n'a pas atteint la taille voulue, on lit
		while (TotalRead < TotalSize)
		{
			// Lecture des échantillons à partir du flux ogg-vorbis
			ALsizei Read = ov_read(Stream, SamplesPtr + TotalRead, TotalSize - TotalRead, 0, 2, 1, NULL);

			if (Read > 0)
			{
				// La lecture a réussi, on avance du nombre d'octets lus
				TotalRead += Read;
			}
			else
			{
				// La lecture a échoué, on arrête de lire
				break;
			}
		}

		// Remplissage du tampon avec les données lues
		if (TotalRead > 0)
			alBufferData(Buffer, Format, &Samples[0], TotalRead, SampleRate);
	}
public:void PlayOggFile(const std::string& filename)
{
	
	isOgg = true;
	//ALCdevice* device = alcOpenDevice(nullptr); // Ouvrir le périphérique audio
	//ALCcontext* context = alcCreateContext(device, nullptr);
	//alcMakeContextCurrent(context);
	Stream = new OggVorbis_File;
	OpenOgg(filename);
	// Création de la source qui jouera le son



	alGenSources(1, uiSource);

	buffers = new ALuint[NUM_BUFFERS];
	alGenSources(1, uiSource);
	alGenBuffers(NUM_BUFFERS, buffers);

	for (int i = 0; i < NUM_BUFFERS; i++)
	{
		ReadOgg(buffers[i], 44100);

	}
	alSourceQueueBuffers(*uiSource, NUM_BUFFERS, buffers);


	alSourcePlay(*uiSource);

	canPlay = true;


	// Streaming continu


}
	  static std::string ManagedStringToStdString(System::String^ _managedString)
	  {
		  std::string unmanagedString = "";
		  for (int i = 0; i < _managedString->Length; i++)
		  {
			  unmanagedString.push_back(_managedString[i]);
		  }
		  return  unmanagedString;
	  }

	 

public:   void UpdateOgg()
{
	if (!canPlay)return;
	// On récupère le nombre de tampons qui ont été traités (i.e. qui sont prêts à être réutilisés)
	ALint NbProcessed;
	alGetSourcei(*uiSource, AL_BUFFERS_PROCESSED, &NbProcessed);

	// On les re-remplit et on les réinjecte dans la file
	for (ALint i = 0; i < NbProcessed; ++i)
	{
		// On sort le tampon de la file
		ALuint Buffer;
		alSourceUnqueueBuffers(*uiSource, 1, &Buffer);

		// On le remplit avec les données du fichier
		ReadOgg(Buffer, 44100);

		// On le réinjecte dans la file
		alSourceQueueBuffers(*uiSource, 1, &Buffer);
	}

	// On récupère l'état de la source
	alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);
	if (*iState == AL_STOPPED)
	{
		canPlay = false;
	}
	else
	{
		return;
	}


}
public:
	void ChangeVolume(float volume)
	{
		if (uiSource != nullptr)
		{
			alListenerf(AL_GAIN, volume);
		}
	}

public:void Stop()
{
	if (uiSource == nullptr) return;
	if (uiBuffer == nullptr) return;

	alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);

	if ((*iState == AL_PLAYING) || (*iState == AL_PAUSED) || (*iState == AL_INITIAL))
	{
		alSourceStop(*uiSource);
		ALint  NbQueued;
		ALuint Buffer;


		

		if (isOgg)
		{
			ALint  NbQueued;
			ALuint Buffer;
			alGetSourcei(*uiSource, AL_BUFFERS_QUEUED, &NbQueued);
			for (ALint i = 0; i < NbQueued; ++i)
				alSourceUnqueueBuffers(*uiSource, 1, &Buffer);
			alSourcei(*uiSource, AL_BUFFER, 0);
			alDeleteBuffers(NUM_BUFFERS, buffers);
			alDeleteSources(1, uiSource);
		}
		else
		{
			alSourcei(*uiSource, AL_BUFFER, 0);
			// On détruit la source
			alDeleteSources(1, uiSource);

			alDeleteBuffers(1, uiBuffer);
		}


		*iState = AL_STOPPED;
		canPlay = false;
		isOgg = false;

	}
}

public: bool Pause()
{
	if (uiSource == nullptr) return false;
	if (uiBuffer == nullptr) return false;

	alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);
	if (*iState == AL_PAUSED)
	{
		alSourcePlay(*uiSource);
		return true;

	}
	else if (*iState == AL_PLAYING)
	{
		alSourcePause(*uiSource);

		return true;
	}
	return false;
}

	  public: SoundBank& GetSoundBank() { return *soundBank; }
};

