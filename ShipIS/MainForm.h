#pragma once
#include "TrainNetworkForm.h"
#include "FuzzyLogicForm.h"
#include "GraphsComprasionForm.h"
#include "GraphBlock.h"
#include "GraphDataGenerator.h"

using namespace ZedGraph;
const int _capacity = 100;
using namespace neural;
using namespace fuzzy;

namespace ShipIS
{

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Globalization;
/// <summary>
/// Summary for MainForm
/// </summary>

public ref class MainForm : public System::Windows::Forms::Form
{
public:
	MainForm( void )
	{
		m_GraphDataGenerator = gcnew GraphDataGenerator();
		InitializeComponent();
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~MainForm()
	{
		if ( components )
		{
			delete components;
		}
		delete m_GraphBlock1;
		delete m_GraphBlock2;
		delete m_GraphBlock3;
		delete m_GraphBlock4;
		delete m_GraphDataGenerator;
	}

private: System::ComponentModel::IContainer^  components;

private: System::Windows::Forms::Timer^  timer_ice_thick;
private: System::Windows::Forms::Button^  buttonNeuralNetwork;
private: System::Windows::Forms::Button^  buttonFuzzySet;
private: System::Windows::Forms::Button^  buttonShowGraphsComprasion;
private: System::Windows::Forms::GroupBox^  input_box;
private: System::Windows::Forms::GroupBox^  tools_box;
private: System::Windows::Forms::TextBox^  interval_tb;
private: System::Windows::Forms::TextBox^  max_velocity_tb;
private: System::Windows::Forms::TextBox^  max_ice_thick_tb;
private: System::Windows::Forms::TextBox^  avg_ice_thick_tb;
private: System::Windows::Forms::Label^  interval_lbl;
private: System::Windows::Forms::Label^  max_velocity_lbl;
private: System::Windows::Forms::Label^  max_ice_thick_lbl;
private: System::Windows::Forms::Label^  avg_ice_thick_lbl;
private: System::Windows::Forms::Button^  button_start;
private: System::Windows::Forms::Button^  button_stop;

		 GraphBlock^ m_GraphBlock1;
		 GraphBlock^ m_GraphBlock2;
		 GraphBlock^ m_GraphBlock3;
		 GraphBlock^ m_GraphBlock4;
		 GraphDataGenerator^ m_GraphDataGenerator;

#pragma region Windows Form Designer generated code
		 /// <summary>
		 /// Required method for Designer support - do not modify
		 /// the contents of this method with the code editor.
		 /// </summary>
		 void InitializeComponent( void )
		 {
			 this->components = ( gcnew System::ComponentModel::Container() );
			 this->timer_ice_thick = ( gcnew System::Windows::Forms::Timer( this->components ) );
			 this->buttonNeuralNetwork = ( gcnew System::Windows::Forms::Button() );
			 this->buttonFuzzySet = ( gcnew System::Windows::Forms::Button() );
			 this->buttonShowGraphsComprasion = ( gcnew System::Windows::Forms::Button() );
			 this->input_box = ( gcnew System::Windows::Forms::GroupBox() );
			 this->tools_box = ( gcnew System::Windows::Forms::GroupBox() );
			 this->interval_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->max_velocity_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->max_ice_thick_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->avg_ice_thick_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->interval_lbl = ( gcnew System::Windows::Forms::Label() );
			 this->max_velocity_lbl = ( gcnew System::Windows::Forms::Label() );
			 this->max_ice_thick_lbl = ( gcnew System::Windows::Forms::Label() );
			 this->avg_ice_thick_lbl = ( gcnew System::Windows::Forms::Label() );
			 this->button_start = ( gcnew System::Windows::Forms::Button() );
			 this->button_stop = ( gcnew System::Windows::Forms::Button() );
			 this->m_GraphBlock1 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 22 ) );
			 this->m_GraphBlock2 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 218 ) );
			 this->m_GraphBlock3 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 414 ) );
			 this->m_GraphBlock4 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 610 ) );
			 this->input_box->SuspendLayout();
			 this->tools_box->SuspendLayout();
			 this->SuspendLayout();

			 // 
			 // timer_ice_thick
			 // 
			 this->timer_ice_thick->Tick += gcnew System::EventHandler( this, &MainForm::timer_ice_thick_Tick );
			 // 
			 // buttonNeuralNetwork
			 // 
			 this->buttonNeuralNetwork->Location = System::Drawing::Point( 20, 20 );
			 this->buttonNeuralNetwork->Name = L"buttonNeuralNetwork";
			 this->buttonNeuralNetwork->Size = System::Drawing::Size( 120, 40 );
			 this->buttonNeuralNetwork->TabIndex = 1;
			 this->buttonNeuralNetwork->Text = L"Neural network";
			 this->buttonNeuralNetwork->UseVisualStyleBackColor = true;
			 this->buttonNeuralNetwork->Click += gcnew System::EventHandler( this, &MainForm::buttonNeuralNetwork_Click );
			 // 
			 // buttonFuzzySet
			 // 
			 this->buttonFuzzySet->Location = System::Drawing::Point( 150, 20 );
			 this->buttonFuzzySet->Name = L"buttonFuzzySet";
			 this->buttonFuzzySet->Size = System::Drawing::Size( 120, 40 );
			 this->buttonFuzzySet->TabIndex = 1;
			 this->buttonFuzzySet->Text = L"Fuzzy model";
			 this->buttonFuzzySet->UseVisualStyleBackColor = true;
			 this->buttonFuzzySet->Click += gcnew System::EventHandler( this, &MainForm::buttonFuzzySet_Click );
			 // 
			 // buttonShowGraphsComprasion
			 // 
			 this->buttonShowGraphsComprasion->Location = System::Drawing::Point( 20, 80 );
			 this->buttonShowGraphsComprasion->Name = L"buttonShowGraphsComprasion";
			 this->buttonShowGraphsComprasion->Size = System::Drawing::Size( 120, 40 );
			 this->buttonShowGraphsComprasion->TabIndex = 1;
			 this->buttonShowGraphsComprasion->Text = L"Compare graphs";
			 this->buttonShowGraphsComprasion->UseVisualStyleBackColor = true;
			 this->buttonShowGraphsComprasion->Click += gcnew System::EventHandler( this, &MainForm::buttonShowGraphsComprasion_Click );
			 // 
			 // input_box
			 // 
			 this->input_box->Controls->Add( this->interval_tb );
			 this->input_box->Controls->Add( this->max_velocity_tb );
			 this->input_box->Controls->Add( this->max_ice_thick_tb );
			 this->input_box->Controls->Add( this->avg_ice_thick_tb );
			 this->input_box->Controls->Add( this->interval_lbl );
			 this->input_box->Controls->Add( this->max_velocity_lbl );
			 this->input_box->Controls->Add( this->max_ice_thick_lbl );
			 this->input_box->Controls->Add( this->avg_ice_thick_lbl );

			 this->input_box->Location = System::Drawing::Point( 45, 30 );
			 this->input_box->Name = L"input_box";
			 this->input_box->Size = System::Drawing::Size( 240, 200 );
			 this->input_box->TabIndex = 4;
			 this->input_box->TabStop = false;
			 this->input_box->Text = L"Input Data";
			 // 
			 // tools_box
			 // 
			 this->tools_box->Controls->Add( this->buttonNeuralNetwork );
			 this->tools_box->Controls->Add( this->buttonFuzzySet );
			 this->tools_box->Controls->Add( this->buttonShowGraphsComprasion );
			 this->tools_box->Location = System::Drawing::Point( 20, 300 );
			 this->tools_box->Name = L"tools_box";
			 this->tools_box->Size = System::Drawing::Size( 290, 140 );
			 this->tools_box->TabIndex = 4;
			 this->tools_box->TabStop = false;
			 this->tools_box->Text = L"Tools";
			 // 
			 // interval_tb
			 // 
			 this->interval_tb->Location = System::Drawing::Point( 125, 122 );
			 this->interval_tb->Name = L"interval_tb";
			 this->interval_tb->Size = System::Drawing::Size( 90, 20 );
			 this->interval_tb->TabIndex = 2;
			 this->interval_tb->Text = L"100";
			 // 
			 // max_velocity_tb
			 // 
			 this->max_velocity_tb->Location = System::Drawing::Point( 125, 96 );
			 this->max_velocity_tb->Name = L"max_velocity_tb";
			 this->max_velocity_tb->Size = System::Drawing::Size( 90, 20 );
			 this->max_velocity_tb->TabIndex = 1;
			 this->max_velocity_tb->Text = L"20";
			 // 
			 // max_ice_thick_tb
			 // 
			 this->max_ice_thick_tb->Location = System::Drawing::Point( 125, 44 );
			 this->max_ice_thick_tb->Name = L"max_ice_thick_tb";
			 this->max_ice_thick_tb->Size = System::Drawing::Size( 90, 20 );
			 this->max_ice_thick_tb->Text = (1.5).ToString();
			 // 
			 // avg_ice_thick_tb
			 // 
			 this->avg_ice_thick_tb->Location = System::Drawing::Point( 125, 70 );
			 this->avg_ice_thick_tb->Name = L"avg_ice_thick_tb";
			 this->avg_ice_thick_tb->Size = System::Drawing::Size( 90, 20 );
			 this->avg_ice_thick_tb->Text = (1.0).ToString();
			 // 
			 // interval_lbl
			 // 
			 this->interval_lbl->AutoSize = true;
			 this->interval_lbl->Location = System::Drawing::Point( 15, 124 );
			 this->interval_lbl->Name = L"interval_lbl";
			 this->interval_lbl->Size = System::Drawing::Size( 35, 13 );
			 this->interval_lbl->Text = L"Interval,(ms):";
			 // 
			 // max_velocity_lbl
			 // 
			 this->max_velocity_lbl->AutoSize = true;
			 this->max_velocity_lbl->Location = System::Drawing::Point( 15, 98 );
			 this->max_velocity_lbl->Name = L"max_velocity_lbl";
			 this->max_velocity_lbl->Size = System::Drawing::Size( 35, 13 );
			 this->max_velocity_lbl->Text = L"Max velocity,(kn):";
			 // 
			 // max_ice_thick_lbl
			 // 
			 this->max_ice_thick_lbl->AutoSize = true;
			 this->max_ice_thick_lbl->Location = System::Drawing::Point( 15, 46 );
			 this->max_ice_thick_lbl->Name = L"max_ice_thick_lbl";
			 this->max_ice_thick_lbl->Size = System::Drawing::Size( 35, 13 );
			 this->max_ice_thick_lbl->TabIndex = 0;
			 this->max_ice_thick_lbl->Text = L"Max ice thickness,(m):";
			 // 
			 // avg_ice_thick_lbl
			 // 
			 this->avg_ice_thick_lbl->AutoSize = true;
			 this->avg_ice_thick_lbl->Location = System::Drawing::Point( 15, 72 );
			 this->avg_ice_thick_lbl->Name = L"avg_ice_thick_lbl";
			 this->avg_ice_thick_lbl->Size = System::Drawing::Size( 35, 13 );
			 this->avg_ice_thick_lbl->TabIndex = 0;
			 this->avg_ice_thick_lbl->Text = L"Avg ice thickness,(m):";
			 // 
			 // button_start
			 // 
			 this->button_start->Location = System::Drawing::Point( 45, 240 );
			 this->button_start->Name = L"button_start";
			 this->button_start->Size = System::Drawing::Size( 120, 40 );
			 this->button_start->TabIndex = 5;
			 this->button_start->Text = L"Start Emulation";
			 this->button_start->UseVisualStyleBackColor = true;
			 this->button_start->Click += gcnew System::EventHandler( this, &MainForm::button_start_Click );
			 // 
			 // button_stop
			 // 
			 this->button_stop->Location = System::Drawing::Point( 166, 240 );
			 this->button_stop->Name = L"button_stop";
			 this->button_stop->Size = System::Drawing::Size( 120, 40 );
			 this->button_stop->TabIndex = 6;
			 this->button_stop->Text = L"Stop Emulation";
			 this->button_stop->UseVisualStyleBackColor = true;
			 this->button_stop->Click += gcnew System::EventHandler( this, &MainForm::button_stop_Click );

			 // 
			 // MainForm
			 // 
			 this->AutoScaleDimensions = System::Drawing::SizeF( 6, 13 );
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			 this->ClientSize = System::Drawing::Size( 984, 800 );
			 this->MaximizeBox = false;
			 this->DoubleBuffered = true;

			 this->Controls->Add( this->button_stop );
			 this->Controls->Add( this->button_start );
			 this->Controls->Add( this->input_box );
			 this->Controls->Add( this->tools_box );


			 this->Controls->Add( this->m_GraphBlock1->GetZedGraph() );
			 this->Controls->Add( this->m_GraphBlock2->GetZedGraph() );
			 this->Controls->Add( this->m_GraphBlock3->GetZedGraph() );
			 this->Controls->Add( this->m_GraphBlock4->GetZedGraph() );

			 this->Controls->Add( this->m_GraphBlock1->GetComboBoxGraphType() );
			 this->Controls->Add( this->m_GraphBlock2->GetComboBoxGraphType() );
			 this->Controls->Add( this->m_GraphBlock3->GetComboBoxGraphType() );
			 this->Controls->Add( this->m_GraphBlock4->GetComboBoxGraphType() );

			 this->Controls->Add( this->m_GraphBlock1->GetComboBoxGraphColor() );
			 this->Controls->Add( this->m_GraphBlock2->GetComboBoxGraphColor() );
			 this->Controls->Add( this->m_GraphBlock3->GetComboBoxGraphColor() );
			 this->Controls->Add( this->m_GraphBlock4->GetComboBoxGraphColor() );

			 this->Name = L"MainForm";
			 this->Text = L"MainForm";
			 this->Load += gcnew System::EventHandler( this, &MainForm::MainForm_Load );
			 this->tools_box->ResumeLayout( false );
			 this->tools_box->PerformLayout();
			 this->input_box->ResumeLayout( false );
			 this->input_box->PerformLayout();
			 this->ResumeLayout( false );

		 }
#pragma endregion
private: System::Void MainForm_Load( System::Object^  sender, System::EventArgs^  e )
{
	SetInputParams();
	m_GraphBlock1->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
	m_GraphBlock2->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
	m_GraphBlock3->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
	m_GraphBlock4->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );

}
private: System::Void timer_ice_thick_Tick( System::Object^  sender, System::EventArgs^  e )
{
	m_GraphDataGenerator->GenerateNext();

	m_GraphBlock1->DrawGraphBlock( m_GraphDataGenerator, _capacity );
	m_GraphBlock2->DrawGraphBlock( m_GraphDataGenerator, _capacity );
	m_GraphBlock3->DrawGraphBlock( m_GraphDataGenerator, _capacity );
	m_GraphBlock4->DrawGraphBlock( m_GraphDataGenerator, _capacity );

	m_GraphDataGenerator->DeleteOverData( _capacity );
}

private: System::Void buttonNeuralNetwork_Click( System::Object^  sender, System::EventArgs^ e )
{
	//button_stop_Click(sender, e);
	TrainNetworkForm^ frm = gcnew TrainNetworkForm( m_GraphDataGenerator->GetParams(), m_GraphDataGenerator->GetNeuralNetwork() );
	frm->Show();
}

private: System::Void buttonFuzzySet_Click( System::Object^  sender, System::EventArgs^ e )
{
	//button_stop_Click(sender, e);
	FuzzyLogicForm^ frm = gcnew FuzzyLogicForm( m_GraphDataGenerator->GetFuzzyAlgorithm(), m_GraphDataGenerator->GetParams() );
	frm->Show();
}
private: System::Void buttonShowGraphsComprasion_Click( System::Object^  sender, System::EventArgs^ e )
{
	//button_stop_Click(sender, e);
	GraphsComprasionForm^ frm = gcnew GraphsComprasionForm( m_GraphDataGenerator, _capacity );
	frm->Show();
}
private: System::Void button_start_Click( System::Object^  sender, System::EventArgs^  e )
{
	if ( SetInputParams() )
	{
		m_GraphBlock1->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
		m_GraphBlock2->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
		m_GraphBlock3->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
		m_GraphBlock4->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );

		m_GraphDataGenerator->CreateIceGenerator();
		timer_ice_thick->Interval = m_GraphDataGenerator->GetParams()->interval;
		timer_ice_thick->Enabled = true;
	}
}

private: System::Void button_stop_Click( System::Object^  sender, System::EventArgs^  e )
{
	timer_ice_thick->Enabled = false;
}

private: bool SetInputParams()
{
	try
	{
		double max_ice = Double::Parse( max_ice_thick_tb->Text );
		double avg_ice = Double::Parse( avg_ice_thick_tb->Text );
		double max_velocity = Double::Parse( max_velocity_tb->Text );
		int interval = Int32::Parse( interval_tb->Text );
		m_GraphDataGenerator->SetParams( new InputParams( max_ice, avg_ice, max_ice / 3.0, max_velocity, interval ) );
		return true;
	}
	catch (Exception^ e)
	{
		MessageBox::Show( "Invalid input data!" );
	}
	return false;

}

};


}
