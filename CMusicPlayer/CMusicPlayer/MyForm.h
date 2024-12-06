#pragma once

#include "../framework/Win32/Framework.h"
#include "MusicPlayer.h"


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

		MusicPlayer mp;
		int songId = 0;
	private: System::Windows::Forms::Button^ Pause;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::HScrollBar^ hScrollBar1;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ Add;
	private: System::Windows::Forms::Button^ Save;
	private: System::Windows::Forms::Button^ Load;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;


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
				delete components;
			}
		}
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Button^ playButton;
	private: System::Windows::Forms::Button^ stopButton;
	private: System::ComponentModel::IContainer^ components;


	protected:

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->Pause = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->hScrollBar1 = (gcnew System::Windows::Forms::HScrollBar());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->Add = (gcnew System::Windows::Forms::Button());
			this->Save = (gcnew System::Windows::Forms::Button());
			this->Load = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
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
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// hScrollBar1
			// 
			this->hScrollBar1->LargeChange = 1;
			this->hScrollBar1->Location = System::Drawing::Point(3, 199);
			this->hScrollBar1->Maximum = 10;
			this->hScrollBar1->Name = L"hScrollBar1";
			this->hScrollBar1->Size = System::Drawing::Size(272, 17);
			this->hScrollBar1->TabIndex = 1;
			this->hScrollBar1->Value = 2;
			this->hScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MyForm::hScrollBar1_Scroll);
			// 
			// listView1
			// 
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(84, 12);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(156, 162);
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listView1_SelectedIndexChanged);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// Add
			// 
			this->Add->Location = System::Drawing::Point(3, 12);
			this->Add->Name = L"Add";
			this->Add->Size = System::Drawing::Size(75, 23);
			this->Add->TabIndex = 3;
			this->Add->Text = L"Add";
			this->Add->UseVisualStyleBackColor = true;
			this->Add->Click += gcnew System::EventHandler(this, &MyForm::Add_Click);
			// 
			// Save
			// 
			this->Save->Location = System::Drawing::Point(3, 41);
			this->Save->Name = L"Save";
			this->Save->Size = System::Drawing::Size(75, 23);
			this->Save->TabIndex = 4;
			this->Save->Text = L"Save";
			this->Save->UseVisualStyleBackColor = true;
			this->Save->Click += gcnew System::EventHandler(this, &MyForm::Save_Click);
			// 
			// Load
			// 
			this->Load->Location = System::Drawing::Point(3, 70);
			this->Load->Name = L"Load";
			this->Load->Size = System::Drawing::Size(75, 23);
			this->Load->TabIndex = 5;
			this->Load->Text = L"Load";
			this->Load->UseVisualStyleBackColor = true;
			this->Load->Click += gcnew System::EventHandler(this, &MyForm::Load_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Enabled = false;
			this->richTextBox1->Location = System::Drawing::Point(84, 12);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(156, 171);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog1_FileOk);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(117, 186);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Volume";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(3, 127);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Previous";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(3, 156);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Next";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(3, 98);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 10;
			this->button4->Text = L"Clear";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->Load);
			this->Controls->Add(this->Save);
			this->Controls->Add(this->Add);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->hScrollBar1);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->flowLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

			mp.ChangeVolume(this->hScrollBar1->Value / 10.f);
		}
#pragma endregion

	public: System::Void UpdateSoundTextBox()
	{
		for (size_t i = 0; i < mp.GetSoundBank().GetSounds().size(); i++)
		{
			String^ filename = gcnew String(mp.GetSoundBank().GetSounds()[i].name.data());
			richTextBox1->AppendText(filename + "\n");
		}
	}


	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		mp.Stop();
	}
	private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{

		mp.Stop();
		Play();

	}

	private: System::Void Pause_Click(System::Object^ sender, System::EventArgs^ e)
	{
		mp.Pause();
		if (this->Pause->Text == L"PAUSE")
		{
			this->Pause->Text = L"RESUME";
		}
		else
		{
			this->Pause->Text = L"PAUSE";
		}
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		mp.UpdateOgg();
	}
	private: System::Void hScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e)
	{
		mp.ChangeVolume(this->hScrollBar1->Value / 10.f);
	}
	private: System::Void Add_Click(System::Object^ sender, System::EventArgs^ e)
	{

		System::IO::Stream^ myStream;
		openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "audio files (*.wav)|*.wav|audio files (*.ogg)|*.ogg";
		openFileDialog1->FilterIndex = 2;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if ((myStream = openFileDialog1->OpenFile()) != nullptr)
			{
				std::string path = MusicPlayer::ManagedStringToStdString(openFileDialog1->FileName);
				std::string name = MusicPlayer::ManagedStringToStdString(openFileDialog1->SafeFileName);
				String^ filename = openFileDialog1->FileName;
				FILE_EXTENSION ext;
				filename->Contains(".wav") ? ext = WAW : ext = OGG;
				SoundData dt = SoundData(path, name, ext);
				mp.GetSoundBank().AddSound(dt);

				richTextBox1->AppendText(openFileDialog1->SafeFileName + "\n");
				// Insert code to read the stream here.
				myStream->Close();
			}
		}
	}

	private:
		void Play()
		{
			if (richTextBox1->Lines->Length > 0)
			{
				const SoundData& sound = mp.GetSoundBank().GetCurrentSound();

				if (sound.extension == WAW)
				{
					mp.PlayWav(sound.path);
				}
				else
				{
					mp.PlayOggFile(sound.path);
				}
				this->Pause->Text = L"PAUSE";
			}
		}
	private: System::Void Save_Click(System::Object^ sender, System::EventArgs^ e) {
		System::IO::Stream^ myStream;
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
		saveFileDialog1->Filter = "txt files (*.txt)|*.txt";
		saveFileDialog1->FilterIndex = 1;
		saveFileDialog1->RestoreDirectory = true;
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			mp.GetSoundBank().SaveBank(MusicPlayer::ManagedStringToStdString(saveFileDialog1->FileName));
		}
	}
	private: System::Void Load_Click(System::Object^ sender, System::EventArgs^ e)
	{
		System::IO::Stream^ myStream;
		openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "../Save";
		openFileDialog1->Filter = "text file (*.txt)|*.txt";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			mp.GetSoundBank().LoadBank(MusicPlayer::ManagedStringToStdString(openFileDialog1->FileName));

			for (size_t i = 0; i < mp.GetSoundBank().GetSounds().size(); i++)
			{
				String^ filename = gcnew String(mp.GetSoundBank().GetSounds()[i].name.data());
				richTextBox1->AppendText(filename + "\n");
			}
		}
	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void saveFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//songId = (songId - 1 + richTextBox1->Lines->Length -1) % (richTextBox1->Lines->Length -1);
		mp.GetSoundBank().Previous();
		mp.Stop();
		Play();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		//songId = (songId + 1) % (richTextBox1->Lines->Length -1);
		mp.GetSoundBank().Next();
		mp.Stop();
		Play();
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		richTextBox1->Text = "";
		songId = 0;
	}
	};
}
