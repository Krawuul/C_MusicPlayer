#pragma once

#include "../framework/Win32/Framework.h"

#define AUDIO_PATH "Sounds/Ruisseau_Escattes_01.wav"

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

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
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
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->playButton);
			this->flowLayoutPanel1->Controls->Add(this->stopButton);
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
	private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
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

		alGenBuffers(1, uiBuffer);

		if (!ALFWLoadWaveToBuffer((char*)AUDIO_PATH, *uiBuffer))
		{
			ALFWprintf("Sound not found! at : %s", AUDIO_PATH);
		}

		alGenSources(1, uiSource);

		alSourcei(*uiSource, AL_BUFFER, *uiBuffer);

		alSourcePlay(*uiSource);
		ALFWprintf("Playing source!");
	}

	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (uiSource == nullptr) return;
		if (uiBuffer == nullptr) return;

		alGetSourcei(*uiSource, AL_SOURCE_STATE, iState);

		if (*iState == (AL_PLAYING | AL_PAUSED | AL_INITIAL))
		{
			alSourceStop(*uiSource);
			alDeleteSources(1, uiSource);
			alDeleteBuffers(1, uiBuffer);

			delete uiBuffer;
			delete uiSource;
			delete iState;
			uiSource = nullptr;
			uiBuffer = nullptr;
			iState = nullptr;
		}
	}
};
}
