#pragma once
#include "DiagramDrawer.h"
#include "NeuralNetwork/NeuralNetworkHelper.h"
#include "IceThicknessGenerator.h"
#include "InputParams.h"
#include "MathVelocityCalculator.h"

using namespace fuzzy;
using namespace neural;

namespace ShipIS
{

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;
using namespace System::Globalization;
/// <summary>
/// Summary for TrainNetworkForm
/// </summary>
public ref class TrainNetworkForm : public System::Windows::Forms::Form
{
public:
	delegate void ReturningVoidDelegate();

	TrainNetworkForm( InputParams* params, NeuralNetwork* network )
	{
		InitializeComponent();
		m_Params = params;
		m_Generator = new IceThicknessGenerator( m_Params->max_ice_thick, m_Params->average_ice_thick );
		m_NetworkHelper = new NeuralNetworkHelper( network );
		m_TrainigDataGenerator = new GeneratorTrainingForIceThickness( std::make_shared<IceThicknessGenerator>( *m_Generator ), *m_Params );
		PrepareGraph( zedGraphError, 0, 1.0, 0, _capacity + 0.0 );
		SetDefaultXAxis( zedGraphError, 0, _capacity + 0.0 );
		GraphPane^ pane = zedGraphError->GraphPane;
		pane->YAxis->Scale->MaxAuto = true;
		m_EpochCount = 0;
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~TrainNetworkForm()
	{
		if ( components )
		{
			delete components;
		}
	}

private: System::ComponentModel::IContainer^  components;
private: System::Windows::Forms::Timer^  timer;
private: ZedGraph::ZedGraphControl^  zedGraphError;
private: System::Windows::Forms::Button^  buttonStart;
private: System::Windows::Forms::Button^ buttonStop;
private: System::Windows::Forms::GroupBox^  input_box;
private: System::Windows::Forms::TextBox^  min_error_tb;
private: System::Windows::Forms::TextBox^  epoch_count_tb;
private: System::Windows::Forms::Label^  min_error_lbl;
private: System::Windows::Forms::Label^  epoch_count_lbl;


		 InputParams* m_Params;
		 IceThicknessGenerator* m_Generator;
		 NeuralNetworkHelper* m_NetworkHelper;
		 GeneratorTrainingForIceThickness* m_TrainigDataGenerator;
		 List<double> m_EpochErrorData;
		 const int _capacity = 30;
		 int m_EpochCount = -1;
		 /// <summary>
		 /// Required designer variable.
		 /// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		 void InitializeComponent( void )
		 {
			 this->components = ( gcnew System::ComponentModel::Container() );
			 this->timer = ( gcnew System::Windows::Forms::Timer( this->components ) );
			 this->zedGraphError = ( gcnew ZedGraph::ZedGraphControl() );
			 this->input_box = ( gcnew System::Windows::Forms::GroupBox() );
			 this->buttonStart = ( gcnew System::Windows::Forms::Button() );
			 this->buttonStop = ( gcnew System::Windows::Forms::Button() );
			 this->min_error_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->epoch_count_tb = ( gcnew System::Windows::Forms::TextBox() );
			 this->min_error_lbl = ( gcnew System::Windows::Forms::Label() );
			 this->epoch_count_lbl = ( gcnew System::Windows::Forms::Label() );
			 this->input_box->SuspendLayout();
			 this->SuspendLayout();
			 // 
			 // input_box
			 // 
			 this->input_box->Controls->Add( this->min_error_tb );
			 this->input_box->Controls->Add( this->epoch_count_tb );
			 this->input_box->Controls->Add( this->min_error_lbl );
			 this->input_box->Controls->Add( this->epoch_count_lbl );

			 this->input_box->Location = System::Drawing::Point( 60, 310 );
			 this->input_box->Name = L"input_box";
			 this->input_box->Size = System::Drawing::Size( 240, 110 );
			 this->input_box->TabIndex = 4;
			 this->input_box->TabStop = false;
			 this->input_box->Text = L"Training Constants";
			 // 
			 // zedGraphError
			 // 
			 this->zedGraphError->Cursor = System::Windows::Forms::Cursors::Hand;
			 this->zedGraphError->Location = System::Drawing::Point( 5, 5 );
			 this->zedGraphError->Name = L"zedGraphError";
			 this->zedGraphError->ScrollGrace = 0;
			 this->zedGraphError->ScrollMaxX = 0;
			 this->zedGraphError->ScrollMaxY = 0;
			 this->zedGraphError->ScrollMaxY2 = 0;
			 this->zedGraphError->ScrollMinX = 0;
			 this->zedGraphError->ScrollMinY = 0;
			 this->zedGraphError->ScrollMinY2 = 0;
			 this->zedGraphError->Size = System::Drawing::Size( 800, 300 );
			 this->zedGraphError->TabIndex = 3;
			 // 
			 // min_error_tb
			 // 
			 this->min_error_tb->Location = System::Drawing::Point( 125, 56 );
			 this->min_error_tb->Name = L"min_error_tb";
			 this->min_error_tb->Size = System::Drawing::Size( 90, 20 );
			 this->min_error_tb->Text = L"0.0001";
			 // 
			 // epoch_count_tb
			 // 
			 this->epoch_count_tb->Location = System::Drawing::Point( 125, 30 );
			 this->epoch_count_tb->Name = L"epoch_count_tb";
			 this->epoch_count_tb->Size = System::Drawing::Size( 90, 20 );
			 this->epoch_count_tb->Text = L"100";
			 // 
			 // min_error_lbl
			 // 
			 this->min_error_lbl->AutoSize = true;
			 this->min_error_lbl->Location = System::Drawing::Point( 15, 58 );
			 this->min_error_lbl->Name = L"min_error_lbl";
			 this->min_error_lbl->Size = System::Drawing::Size( 35, 13 );
			 this->min_error_lbl->Text = L"Min Error:";
			 // 
			 // interval_lbl
			 // 
			 this->epoch_count_lbl->AutoSize = true;
			 this->epoch_count_lbl->Location = System::Drawing::Point( 15, 32 );
			 this->epoch_count_lbl->Name = L"epoch_count_lbl";
			 this->epoch_count_lbl->Size = System::Drawing::Size( 35, 13 );
			 this->epoch_count_lbl->Text = L"Count epochs:";
			 // 
			 // buttonStart
			 //
			 this->buttonStart->Location = System::Drawing::Point( 600, 350 );
			 this->buttonStart->Name = L"buttonStart";
			 this->buttonStart->Size = System::Drawing::Size( 120, 40 );
			 this->buttonStart->TabIndex = 1;
			 this->buttonStart->Text = L"Start";
			 this->buttonStart->UseVisualStyleBackColor = true;
			 this->buttonStart->Click += gcnew System::EventHandler( this, &TrainNetworkForm::buttonStart_Click );
			 // 
			 // buttonStop
			 //
			 this->buttonStop->Location = System::Drawing::Point( 600, 400 );
			 this->buttonStop->Name = L"buttonStop";
			 this->buttonStop->Size = System::Drawing::Size( 120, 40 );
			 this->buttonStop->TabIndex = 1;
			 this->buttonStop->Text = L"Stop";
			 this->buttonStop->UseVisualStyleBackColor = true;
			 this->buttonStop->Click += gcnew System::EventHandler( this, &TrainNetworkForm::buttonStop_Click );
			 // 
			 // timer
			 //
			 this->timer->Interval = 100;
			 this->timer->Tick += gcnew System::EventHandler( this, &TrainNetworkForm::timer_Tick );

			 this->components = gcnew System::ComponentModel::Container();
			 //this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &TrainNetworkForm::TrainNetworkForm_BeforeClosing);
			 this->Load += gcnew System::EventHandler( this, &TrainNetworkForm::TrainNetworkForm_Load );
			 this->Closed += gcnew System::EventHandler( this, &TrainNetworkForm::TrainNetworkForm_Closing );
			 this->Size = System::Drawing::Size( 830, 500 );
			 this->Text = L"TrainNetworkForm";
			 this->Controls->Add( this->zedGraphError );
			 this->Controls->Add( this->buttonStart );
			 this->Controls->Add( this->buttonStop );
			 this->Controls->Add( this->input_box );
			 this->Padding = System::Windows::Forms::Padding( 0 );
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			 this->input_box->ResumeLayout( false );
			 this->input_box->PerformLayout();
			 this->ResumeLayout( false );
		 }
#pragma endregion
private: System::Void TrainNetworkForm_Load( System::Object^ sender, System::EventArgs^  e )
{
	auto dataVector = m_TrainigDataGenerator->GenerateTrainingVector( 200 );
	m_NetworkHelper->ChangeTrainingDataVector( dataVector );
}
private: System::Void TrainNetworkForm_Closing( System::Object^ sender, System::EventArgs^  e )
{
	timer->Enabled = false;
}

private: System::Void buttonStart_Click( System::Object^  sender, System::EventArgs^  e )
{

	timer->Enabled = true;
	buttonStart->Enabled = false;
}
private: System::Void buttonStop_Click( System::Object^  sender, System::EventArgs^  e )
{
	timer->Enabled = false;
	buttonStart->Enabled = true;
}

private: System::Void timer_Tick( System::Object^ sender, System::EventArgs^  e )
{
	timer->Enabled = false;
	DoBackgroundWork();
	//Threading::Thread^ thread_1 = gcnew Threading::Thread( gcnew Threading::ThreadStart( this, &TrainNetworkForm::DoBackgroundWork ) );
	//thread_1->Start();
}

private: System::Void DoBackgroundWork()
{
	double value = 1.0;
	double min_error = 0.0;
	double epoch_count = 0.0;
	try
	{
		min_error = Double::Parse( min_error_tb->Text, CultureInfo::InvariantCulture );
		epoch_count = Double::Parse( epoch_count_tb->Text, CultureInfo::InvariantCulture );
		value = m_NetworkHelper->TrainNetwork( min_error, 1, true );
		if ( value > min_error && m_EpochCount < epoch_count )
		{
			m_EpochErrorData.Add( value );
			DrawGraphError();
			m_EpochCount++;
		}
		else
		{
			m_NetworkHelper->ChangeTrainingDataVector( m_TrainigDataGenerator->GenerateTrainingVector( 200 ) );
			m_EpochCount = 0;
			SetButtonEnabled();
		}
	}
	catch ( Exception^ e )
	{
		MessageBox::Show( "Invalid input data!" );
		SetButtonEnabled();
	}
}

private: System::Void DrawGraphError()
{
	if ( zedGraphError->InvokeRequired )
	{
		if ( this != nullptr )
		{
			ReturningVoidDelegate^ d =
				gcnew ReturningVoidDelegate( this, &TrainNetworkForm::DrawGraphError );
			this->Invoke( d );
		}
	}
	else
	{
		if ( m_EpochErrorData.Count - 1 > _capacity )
		{
			m_EpochErrorData.RemoveAt( 0 );
			ChangeXAxis( zedGraphError, 1 );
		}
		DrawGraph( zedGraphError, %m_EpochErrorData, Color::Red, 1 );
		timer->Enabled = true;
	}
}

private: System::Void SetButtonEnabled()
{
	if ( this->InvokeRequired )
	{
		ReturningVoidDelegate^ d =
			gcnew ReturningVoidDelegate( this, &TrainNetworkForm::SetButtonEnabled );
		this->Invoke( d );
	}
	else
	{
		buttonStart->Enabled = true;
	}

}

};
}
