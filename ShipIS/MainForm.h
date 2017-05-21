#pragma once
#include "TrainNetworkForm.h"
#include "GraphBlock.h"
#include "GraphDataGenerator.h"

using namespace ZedGraph;
const int _capacity = 100;

namespace ShipIS
{

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
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
	}

private: System::ComponentModel::IContainer^  components;
//private: ZedGraph::ZedGraphControl^  zedGraph1;
//private: ZedGraph::ZedGraphControl^  zedGraph2;
//private: ZedGraph::ZedGraphControl^  zedGraph3;
//private: ZedGraph::ZedGraphControl^  zedGraph4;

private: System::Windows::Forms::Timer^  timer_ice_thick;
private: System::Windows::Forms::Button^  buttonTrainNetwork;
private: System::Windows::Forms::GroupBox^  input_box;
private: System::Windows::Forms::TextBox^  interval_tb;
private: System::Windows::Forms::TextBox^  max_velocity_tb;
private: System::Windows::Forms::TextBox^  max_ice_thick_tb;
private: System::Windows::Forms::Button^  button_start;
private: System::Windows::Forms::Button^  button_stop;

//private: System::Windows::Forms::ComboBox^  comboBoxGraphType1;
//private: System::Windows::Forms::ComboBox^  comboBoxGraphType2;
//private: System::Windows::Forms::ComboBox^  comboBoxGraphType3;
//private: System::Windows::Forms::ComboBox^  comboBoxGraphType4;
//
//private: System::Windows::Forms::ComboBox^  comboBoxGraphColor1;
//private: System::Windows::Forms::ComboBox^  comboBoxGraphColor2;
//private: System::Windows::Forms::ComboBox^  comboBoxGraphColor3;
//private: System::Windows::Forms::ComboBox^  comboBoxGraphColor4;
//
		 //not-managed members
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
			 this->buttonTrainNetwork = ( gcnew System::Windows::Forms::Button() );
			 this->input_box = ( gcnew System::Windows::Forms::GroupBox() );
			 this->interval_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->max_velocity_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->max_ice_thick_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->button_start = ( gcnew System::Windows::Forms::Button() );
			 this->button_stop = ( gcnew System::Windows::Forms::Button() );
			 this->m_GraphBlock1 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 22 ) );
			 this->m_GraphBlock2 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 218 ) );
			 this->m_GraphBlock3 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 414 ) );
			 this->m_GraphBlock4 = gcnew GraphBlock( gcnew ZedGraph::ZedGraphControl(), gcnew ComboBox(), gcnew ComboBox(), Point( 372, 610 ) );
			 this->input_box->SuspendLayout();
			 this->SuspendLayout();
			 // 
			 // timer_ice_thick
			 // 
			 this->timer_ice_thick->Tick += gcnew System::EventHandler( this, &MainForm::timer_ice_thick_Tick );
			 // 
			 // buttonTrainNetwork
			 // 
			 this->buttonTrainNetwork->Location = System::Drawing::Point( 194, 381 );
			 this->buttonTrainNetwork->Name = L"buttonTrainNetwork";
			 this->buttonTrainNetwork->Size = System::Drawing::Size( 120, 40 );
			 this->buttonTrainNetwork->TabIndex = 1;
			 this->buttonTrainNetwork->Text = L"Train Network";
			 this->buttonTrainNetwork->UseVisualStyleBackColor = true;
			 this->buttonTrainNetwork->Click += gcnew System::EventHandler( this, &MainForm::buttonTrainNetwork_Click );
			 // 
			 // input_box
			 // 
			 this->input_box->Controls->Add( this->interval_tb );
			 this->input_box->Controls->Add( this->max_velocity_tb );
			 this->input_box->Controls->Add( this->max_ice_thick_tb );
			 this->input_box->Location = System::Drawing::Point( 45, 30 );
			 this->input_box->Name = L"input_box";
			 this->input_box->Size = System::Drawing::Size( 241, 147 );
			 this->input_box->TabIndex = 4;
			 this->input_box->TabStop = false;
			 this->input_box->Text = L"Input Data";
			 // 
			 // interval_tb
			 // 
			 this->interval_tb->Location = System::Drawing::Point( 102, 96 );
			 this->interval_tb->Name = L"interval_tb";
			 this->interval_tb->Size = System::Drawing::Size( 107, 20 );
			 this->interval_tb->TabIndex = 2;
			 this->interval_tb->Text = L"100";
			 // 
			 // max_velocity_tb
			 // 
			 this->max_velocity_tb->Location = System::Drawing::Point( 102, 70 );
			 this->max_velocity_tb->Name = L"max_velocity_tb";
			 this->max_velocity_tb->Size = System::Drawing::Size( 107, 20 );
			 this->max_velocity_tb->TabIndex = 1;
			 this->max_velocity_tb->Text = L"20";
			 // 
			 // max_ice_thick_tb
			 // 
			 this->max_ice_thick_tb->Location = System::Drawing::Point( 102, 44 );
			 this->max_ice_thick_tb->Name = L"max_ice_thick_tb";
			 this->max_ice_thick_tb->Size = System::Drawing::Size( 107, 20 );
			 this->max_ice_thick_tb->TabIndex = 0;
			 this->max_ice_thick_tb->Text = L"1,5";
			 // 
			 // button_start
			 // 
			 this->button_start->Location = System::Drawing::Point( 45, 197 );
			 this->button_start->Name = L"button_start";
			 this->button_start->Size = System::Drawing::Size( 120, 40 );
			 this->button_start->TabIndex = 5;
			 this->button_start->Text = L"Start Emulation";
			 this->button_start->UseVisualStyleBackColor = true;
			 this->button_start->Click += gcnew System::EventHandler( this, &MainForm::button_start_Click );
			 // 
			 // button_stop
			 // 
			 this->button_stop->Location = System::Drawing::Point( 166, 197 );
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
			 this->Controls->Add( this->button_stop );
			 this->Controls->Add( this->button_start );
			 this->Controls->Add( this->input_box );
			 this->Controls->Add( this->buttonTrainNetwork );

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

private: System::Void buttonTrainNetwork_Click( System::Object^  sender, System::EventArgs^ e )
{
	//button_stop_Click(sender, e);
	TrainNetworkForm^ frm = gcnew TrainNetworkForm( m_GraphDataGenerator->GetParams(), m_GraphDataGenerator->GetNeuralNetwork() );
	frm->ShowDialog();
}

private: System::Void button_start_Click( System::Object^  sender, System::EventArgs^  e )
{
	SetInputParams();
	m_GraphBlock1->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
	m_GraphBlock2->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
	m_GraphBlock3->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );
	m_GraphBlock4->SetDefaultXAxis( 0, m_GraphDataGenerator->GetParams()->interval * _capacity );

	m_GraphDataGenerator->CreateIceGenerator();
	timer_ice_thick->Interval = m_GraphDataGenerator->GetParams()->interval;
	timer_ice_thick->Enabled = true;
}

private: System::Void button_stop_Click( System::Object^  sender, System::EventArgs^  e )
{
	timer_ice_thick->Enabled = false;
}

private: System::Void SetInputParams()
{
	double max_ice = Convert::ToDouble( max_ice_thick_tb->Text );
	double max_velocity = Convert::ToDouble( max_velocity_tb->Text );
	double interval = Convert::ToDouble( interval_tb->Text );

	m_GraphDataGenerator->SetParams( new InputParams( max_ice, 1.0, 1.0, max_velocity, interval ) );
}

};


}
