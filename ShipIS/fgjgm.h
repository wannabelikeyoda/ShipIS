#pragma once

namespace ShipIS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for fgjgm
	/// </summary>
	public ref class fgjgm : public System::Windows::Forms::Form
	{
	public:
		fgjgm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~fgjgm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::CheckedListBox^  checkedListBox1;


	private: System::Windows::Forms::ComboBox^  comboBox1;

	protected:
	private: System::ComponentModel::IContainer^  components;

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
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"ghe", L"rhfdh", L"fdhfh", L"dfhdfh" });
			this->checkedListBox1->Location = System::Drawing::Point(37, 119);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(120, 94);
			this->checkedListBox1->TabIndex = 1;
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Ice thickness", L"Math velocity", L"Neural velocity",
					L"Fuzzy velocity"
			});
			this->comboBox1->Location = System::Drawing::Point(227, 82);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(141, 21);
			this->comboBox1->TabIndex = 3;
			// 
			// fgjgm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(468, 355);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->checkedListBox1);
			this->Name = L"fgjgm";
			this->Text = L"fgjgm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
