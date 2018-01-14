#pragma once
#include "FuzzyModel/MamdaniAlgorithm.h"
#include <msclr\marshal_cppstd.h>

namespace ShipIS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing; 
	using namespace System::Text;

	using namespace fuzzy;
	/// <summary>
	/// Summary for FuzzyLogicForm
	/// </summary>
	public ref class FuzzyLogicForm : public System::Windows::Forms::Form
	{
	public:
		FuzzyLogicForm( MamdaniAlgorithm* algorithm, InputParams* params )
			: m_Algorithm( algorithm ), m_Params(params)
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
		~FuzzyLogicForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  generate_button;
	private: System::Windows::Forms::ListBox^  rules_listbox;

		InputParams* m_Params;
		MamdaniAlgorithm* m_Algorithm;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->generate_button = ( gcnew System::Windows::Forms::Button() );
			this->rules_listbox = ( gcnew System::Windows::Forms::ListBox() );
			this->SuspendLayout();
			// 
			// generate_button
			// 
			this->generate_button->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->generate_button->Location = System::Drawing::Point( 133, 268 );
			this->generate_button->Name = L"generate_button";
			this->generate_button->Size = System::Drawing::Size( 111, 40 );
			this->generate_button->TabIndex = 0;
			this->generate_button->Text = L"Generate rules";
			this->generate_button->UseVisualStyleBackColor = true;
			this->generate_button->Click += gcnew System::EventHandler( this, &FuzzyLogicForm::generate_button_Click );
			// 
			// rules_listbox
			// 
			this->rules_listbox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom )
				| System::Windows::Forms::AnchorStyles::Left )
				| System::Windows::Forms::AnchorStyles::Right ) );
			this->rules_listbox->Font = ( gcnew System::Drawing::Font( L"MS Reference Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>( 204 ) ) );
			this->rules_listbox->FormattingEnabled = true;
			this->rules_listbox->ItemHeight = 16;
			this->rules_listbox->Location = System::Drawing::Point( 12, 12 );
			this->rules_listbox->Name = L"rules_listbox";
			this->rules_listbox->Size = System::Drawing::Size( 364, 212 );
			this->rules_listbox->TabIndex = 1;
			// 
			// FuzzyLogicForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF( 6, 13 );
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size( 384, 341 );
			this->Controls->Add( this->rules_listbox );
			this->Controls->Add( this->generate_button );
			this->MaximizeBox = false;
			this->MinimumSize = System::Drawing::Size( 400, 380 );
			this->Name = L"FuzzyLogicForm";
			this->Text = L"Fuzzy Logic";
			this->Load += gcnew System::EventHandler( this, &FuzzyLogicForm::FuzzyLogicForm_Load );
			this->ResumeLayout( false );

		}
#pragma endregion

	private: System::Void generate_button_Click( System::Object^  sender, System::EventArgs^  e )
	{
		RulesBaseGeneratorForIceThickness rules_generator = RulesBaseGeneratorForIceThickness( m_Params );
		RulesBasePtr rules_base = rules_generator.GenerateRulesBaseForIceThickness();
		m_Algorithm->SetRules( rules_base );
		m_Algorithm->SetParams( m_Params );
		FillListBoxByRules( rules_base );
	}

	private: System::Void FillListBoxByRules( RulesBasePtr rules_base )
	{
		msclr::interop::marshal_context context;
		rules_listbox->Items->Clear();
		for ( fuzzy::Rule rule : rules_base->GetRules() )
		{
			System::Text::StringBuilder rule_str;
			rule_str.Append( "IF " );
			bool first = true;
			for ( Condition condition : rule.GetConditions() )
			{
				if ( !first )
					rule_str.Append( " AND " );
				auto text = context.marshal_as<System::String^>( condition.ToStr().c_str() );
				rule_str.Append( text );
				first = false;
			}
			rule_str.Append( " THEN " );
			first = true;
			for ( Conclusion conclusion : rule.GetConclusions() )
			{
				if ( !first )
					rule_str.Append( " AND " );
				auto text = context.marshal_as<System::String^>( conclusion.ToStr().c_str() );
				rule_str.Append( text );
				first = false;
			}
			rule_str.Append( "\n" );
			rules_listbox->Items->Add( rule_str.ToString() );
		}
	}
	private: System::Void FuzzyLogicForm_Load( System::Object^  sender, System::EventArgs^  e )
	{
		FillListBoxByRules( m_Algorithm->GetRulesBase() );
	}
};
}
