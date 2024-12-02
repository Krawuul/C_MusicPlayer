#pragma once

#include "../framework/Win32/Framework.h"
#include "al.h"
#include "alc.h"
#include "vorbis/vorbisfile.h"
#include "vorbis/codec.h"
#include <chrono>
#include <thread>


#define AUDIO_PATH "..\\Sounds\\Ruisseau_Escattes_01.wav"
#define AUDIO_PATH2 "..\\Sounds\\Pouet.ogg"
#define BUFFER_SIZE 4096
#define NUM_BUFFERS 3

namespace CMusicPlayer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	public:
		ALuint* uiBuffer;
		ALuint* uiSource;
		ALint* iState;
		
	private: System::Windows::Forms::Button^ Pause;
	public:

	public:
	private: System::Windows::Forms::Button^ button2;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{



				delete iState;

				iState = nullptr;
				delete components;
			}
		}
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Button^ playButton;
	private: System::Windows::Forms::Button^ stopButton;


	protected:

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			if (uiBuffer == nullptr) {
				uiBuffer = new ALuint();
			}
			if (uiSource == nullptr) {
				uiSource = new ALuint();
			}
			if (iState == nullptr) {
				iState = new ALint();
			}
			ALFWInit();

			if (!ALFWInitOpenAL())
			{
				ALFWprintf("ALFW not initialized!");
				ALFWShutdown();
				return;
			}

			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->Pause = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->playButton);
			this->flowLayoutPanel1->Controls->Add(this->stopButton);
			this->flowLayoutPanel1->Controls->Add(this->Pause);
			this->flowLayoutPanel1->Controls->Add(this->button2);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 232);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(284, 29);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// playButton
			// 
			this->playButton->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->playButton->Location = System::Drawing::Point(3, 3);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(75, 23);
			this->playButton->TabIndex = 0;
			this->playButton->Text = L"PLAY";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->stopButton->Location = System::Drawing::Point(84, 3);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(75, 23);
			this->stopButton->TabIndex = 1;
			this->stopButton->Text = L"STOP";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MyForm::stopButton_Click);
			// 
			// Pause
			// 
			this->Pause->Location = System::Drawing::Point(165, 3);
			this->Pause->Name = L"Pause";
			this->Pause->Size = System::Drawing::Size(75, 23);
			this->Pause->TabIndex = 2;
			this->Pause->Text = L"PAUSE";
			this->Pause->UseVisualStyleBackColor = true;
			this->Pause->Click += gcnew System::EventHandler(this, &MyForm::Pause_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(3, 32);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->flowLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: void PlayWav()
	{
		if ((*iState != AL_PLAYING) && (*iState != AL_PAUSED))
		{


			alGenBuffers(1, uiBuffer);

			if (!ALFWLoadWaveToBuffer((char*)AUDIO_PATH, *uiBuffer))
			{
				ALFWprintf("Sound not found! at : %s", AUDIO_PATH);
			}

			alGenSources(1, uiSource);

			alSourcei(*uiSource, AL_BUFFER, *uiBuffer);

			alSourcePlay(*uiSource);
			ALFWprintf("Playing source!");


			this->Pause->Text = L"PAUSE";
		}
	}
	private:	   
	bool StreamOggData(ALuint source, ALuint buffers[], OggVorbis_File* oggFile,ALenum format,ALsizei freq)
	{
		char pcm[BUFFER_SIZE];
		int bitstream;
		long bytes;

		for (int i = 0; i < NUM_BUFFERS; i++)
		{
			int bitstream =0;
			bytes = ov_read(oggFile, pcm, BUFFER_SIZE, 0, 2, 1, &bitstream);
			if (bytes > 0)
			{
				alBufferData(buffers[i], format, pcm, bytes, freq);
				alSourceQueueBuffers(source, 1, &buffers[i]);
			}
			else if (bytes == 0)
			{
				// Fin du fichier
				return true;
			}
			else
			{
				
				return false;
			}
		}
		ov_clear(oggFile);
		return true;
	}
	private:void PlayOggFile(const char* filename)
	{
		//ALCdevice* device = alcOpenDevice(nullptr); // Ouvrir le périphérique audio
		//ALCcontext* context = alcCreateContext(device, nullptr);
		//alcMakeContextCurrent(context);

		
		ALuint buffers[NUM_BUFFERS];
		alGenSources(1, uiSource);
		alGenBuffers(NUM_BUFFERS, buffers);

		OggVorbis_File oggFile;
		if (ov_fopen(filename, &oggFile) != 0)
		{
			
			return;
		}
		vorbis_info* vi = ov_info(&oggFile, -1);
		ALenum format = (vi->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		ALsizei freq = vi->rate;

		// Charger les premiers buffers
		if (!StreamOggData(*uiSource, buffers, &oggFile,format,freq))
		{
			return;
		}

		alSourcePlay(*uiSource);

		// Streaming continu
		
		while (true) {
			ALint processed = 0;
			alGetSourcei(*uiSource, AL_BUFFERS_PROCESSED, &processed);

			while (processed--) {
				ALuint buffer;
				alSourceUnqueueBuffers(*uiSource, 1, &buffer);

				// Lire de nouvelles données pour le buffer
				StreamOggData(*uiSource, buffers, &oggFile, format, freq);

				alSourceQueueBuffers(*uiSource, 1, &buffer);
			}

			// Vérifier l'état de la source
			ALint state;
			alGetSourcei(*uiSource, AL_SOURCE_STATE, &state);
			if (state != AL_PLAYING) {
				alSourcePlay(*uiSource);  // Relancer si la source s'est arrêtée
			}

			// Pause pour éviter une boucle infinie trop rapide
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		// Nettoyage
		alSourceStop(*uiSource);
		alDeleteSources(1, uiSource);
		alDeleteBuffers(NUM_BUFFERS, buffers);

	
	}

	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (uiSource == nullptr) return;
		if (uiBuffer == nullptr) return;

		alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);

		if ((*iState == AL_PLAYING) || (*iState == AL_PAUSED) || (*iState == AL_INITIAL))
		{

			alSourceStop(*uiSource);
			alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);
			alDeleteSources(1, uiSource);
			alDeleteBuffers(1, uiBuffer);

		}
	}
	private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		PlayOggFile(AUDIO_PATH2);



	}

	private: System::Void Pause_Click(System::Object^ sender, System::EventArgs^ e) {
		if (uiSource == nullptr) return;
		if (uiBuffer == nullptr) return;

		alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);
		if (*iState == AL_PAUSED)
		{
			alSourcePlay(*uiSource);
			this->Pause->Text = L"PAUSE";

		}
		else if (*iState == AL_PLAYING)
		{
			alSourcePause(*uiSource);
			this->Pause->Text = L"RESUME";
		}
	}

	};
}
