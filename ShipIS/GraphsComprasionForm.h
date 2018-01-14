#pragma once
#include "DiagramDrawer.h"
#include "GraphDataGenerator.h"

namespace ShipIS
{

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for GraphsComprasionForm
/// </summary>
public ref class GraphsComprasionForm : public System::Windows::Forms::Form
{
public:
	GraphsComprasionForm( GraphDataGenerator^ generator, const int capacity )
		: m_GraphDataGenerator( generator ), m_Capacity( capacity )
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
	~GraphsComprasionForm()
	{
		if ( components )
		{
			delete components;
		}
	}

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
private: System::ComponentModel::IContainer^  components;
private: System::Windows::Forms::Timer^  timer;
private: ZedGraph::ZedGraphControl^  zedGraph;
private: System::Windows::Forms::Button^  buttonStart;
private: System::Windows::Forms::Button^  buttonStop;
private: System::Windows::Forms::CheckedListBox^  checkedListBox1;

		 GraphDataGenerator^ m_GraphDataGenerator;
		 const int m_Capacity;

#pragma region Windows Form Designer generated code
		 /// <summary>
		 /// Required method for Designer support - do not modify
		 /// the contents of this method with the code editor.
		 /// </summary>
		 void InitializeComponent( void )
		 {
			 this->components = ( gcnew System::ComponentModel::Container() );
			 this->timer = ( gcnew System::Windows::Forms::Timer( this->components ) );
			 this->zedGraph = ( gcnew ZedGraph::ZedGraphControl() );
			 this->buttonStart = ( gcnew System::Windows::Forms::Button() );
			 this->buttonStop = ( gcnew System::Windows::Forms::Button() );
			 this->checkedListBox1 = ( gcnew System::Windows::Forms::CheckedListBox() );
			 this->SuspendLayout();
			 // 
			 // timer
			 // 
			 this->timer->Tick += gcnew System::EventHandler( this, &GraphsComprasionForm::timer_Tick );
			 // 
			 // zedGraph
			 // 
			 this->zedGraph->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom )
				 | System::Windows::Forms::AnchorStyles::Left )
				 | System::Windows::Forms::AnchorStyles::Right ) );
			 this->zedGraph->Cursor = System::Windows::Forms::Cursors::Hand;
			 this->zedGraph->IsEnableHZoom = false;
			 this->zedGraph->Location = System::Drawing::Point( 0, 0 );
			 this->zedGraph->Name = L"zedGraph";
			 this->zedGraph->ScrollGrace = 0;
			 this->zedGraph->ScrollMaxX = 0;
			 this->zedGraph->ScrollMaxY = 0;
			 this->zedGraph->ScrollMaxY2 = 0;
			 this->zedGraph->ScrollMinX = 0;
			 this->zedGraph->ScrollMinY = 0;
			 this->zedGraph->ScrollMinY2 = 0;
			 this->zedGraph->Size = System::Drawing::Size( 810, 307 );
			 this->zedGraph->TabIndex = 3;
			 // 
			 // buttonStart
			 // 
			 this->buttonStart->Location = System::Drawing::Point( 668, 306 );
			 this->buttonStart->Name = L"buttonStart";
			 this->buttonStart->Size = System::Drawing::Size( 120, 40 );
			 this->buttonStart->TabIndex = 1;
			 this->buttonStart->Text = L"Start";
			 this->buttonStart->UseVisualStyleBackColor = true;
			 this->buttonStart->Click += gcnew System::EventHandler( this, &GraphsComprasionForm::buttonStart_Click );
			 // 
			 // buttonStop
			 // 
			 this->buttonStop->Location = System::Drawing::Point( 668, 352 );
			 this->buttonStop->Name = L"buttonStop";
			 this->buttonStop->Size = System::Drawing::Size( 120, 40 );
			 this->buttonStop->TabIndex = 1;
			 this->buttonStop->Text = L"Start";
			 this->buttonStop->UseVisualStyleBackColor = true;
			 this->buttonStop->Click += gcnew System::EventHandler( this, &GraphsComprasionForm::buttonStop_Click );
			 // 
			 // checkedListBox1
			 // 
			 this->checkedListBox1->FormattingEnabled = true;
			 this->checkedListBox1->Items->AddRange( gcnew cli::array< System::Object^  >( 4 )
			 {
				 L"Ice thickness", L"Math velocity", L"Neural velocity",
					 L"Fuzzy velocity"
			 } );
			 this->checkedListBox1->Location = System::Drawing::Point( 504, 306 );
			 this->checkedListBox1->Name = L"checkedListBox1";
			 this->checkedListBox1->Size = System::Drawing::Size( 144, 64 );
			 this->checkedListBox1->TabIndex = 4;
			 // 
			 // GraphsComprasionForm
			 // 
			 this->AutoScaleDimensions = System::Drawing::SizeF( 6, 13 );
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			 this->ClientSize = System::Drawing::Size( 810, 306 );
			 this->Controls->Add( this->zedGraph );
			 this->DoubleBuffered = true;
			 this->Name = L"GraphsComprasionForm";
			 this->Text = L"Velocity compration";
			 this->Load += gcnew System::EventHandler( this, &GraphsComprasionForm::GraphsComprasionForm_Load );
			 this->ResumeLayout( false );

		 }
#pragma endregion

private: System::Void GraphsComprasionForm_Load( System::Object^  sender, System::EventArgs^  e )
{
	timer->Interval = m_GraphDataGenerator->GetParams()->interval;
	timer->Enabled = true;
	ClearTitles( zedGraph );
	SetDefaultXAxis( zedGraph, 0, m_GraphDataGenerator->GetParams()->interval * m_Capacity );
}
private: System::Void buttonStart_Click( System::Object^  sender, System::EventArgs^  e )
{
	timer->Enabled = true;
}
private: System::Void buttonStop_Click( System::Object^  sender, System::EventArgs^  e )
{
	timer->Enabled = false;
}
private: System::Void timer_Tick( System::Object^ sender, System::EventArgs^  e )
{
	//TODO: change ice thickness to fuzzy logic
	ClearCurves( zedGraph );
	DrawCurve( zedGraph, m_GraphDataGenerator->GetMathVelocity(), Color::Blue, L"Math velocity", m_GraphDataGenerator->GetParams()->interval );
	DrawCurve( zedGraph, m_GraphDataGenerator->GetNeuralVelocity(), Color::Green, L"Neural velocity", m_GraphDataGenerator->GetParams()->interval );
	DrawCurve( zedGraph, m_GraphDataGenerator->GetFuzzyVelocity(), Color::Red, L"Fuzzy velocity", m_GraphDataGenerator->GetParams()->interval );
}

};
}
