#pragma once
#include "DiagramDrawer.h"
#include "NeuralNetwork/NeuralNetworkHelper.h"
#include "NeuralNetwork/IceThicknessGenerator.h"
#include "NeuralNetwork/InputParams.h"
#include "NeuralNetwork/MathVelocityCalculator.h"

namespace ShipIS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	/// <summary>
	/// Summary for TrainNetworkForm
	/// </summary>
	public ref class TrainNetworkForm : public System::Windows::Forms::Form
	{
	public:
		delegate void ReturningVoidDelegate();

		TrainNetworkForm(InputParams* params, NeuralNetwork* network)
		{
			InitializeComponent();
			m_Params = params;
			m_Generator = new IceThicknessGenerator(m_Params->max_ice_thick, m_Params->average_ice_thick);
			m_NetworkHelper = new NeuralNetworkHelper(network, 0.5);
			PrepareGraph(zedGraphError, 0, 1.0, 0, _capacity + 0.0);
			SetDefaultXAxis(zedGraphError, 0, _capacity + 0.0);
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
			if (components)
			{
				delete components;
			}
			delete m_Params;
			delete m_Generator;
			delete m_NetworkHelper;
		}

	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  timer;
	private: ZedGraph::ZedGraphControl^  zedGraphError;
	private: System::Windows::Forms::Button^  buttonStart;

			 InputParams* m_Params;
			 IceThicknessGenerator* m_Generator;
			 NeuralNetworkHelper* m_NetworkHelper;
			 List<double> m_EpochErrorData;
			 const int _capacity = 30;
			 const int _max_epoch_count = 100;
			 int m_EpochCount = -1;
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
				 this->timer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->zedGraphError = (gcnew ZedGraph::ZedGraphControl());
				 this->buttonStart = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 // 
				 // zedGraphError
				 // 
				 this->zedGraphError->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->zedGraphError->Location = System::Drawing::Point(0, 0);
				 this->zedGraphError->Name = L"zedGraphError";
				 this->zedGraphError->ScrollGrace = 0;
				 this->zedGraphError->ScrollMaxX = 0;
				 this->zedGraphError->ScrollMaxY = 0;
				 this->zedGraphError->ScrollMaxY2 = 0;
				 this->zedGraphError->ScrollMinX = 0;
				 this->zedGraphError->ScrollMinY = 0;
				 this->zedGraphError->ScrollMinY2 = 0;
				 this->zedGraphError->Size = System::Drawing::Size(800, 300);
				 this->zedGraphError->TabIndex = 3;
				 // 
				 // buttonStart
				 //
				 this->buttonStart->Location = System::Drawing::Point(60, 330);
				 this->buttonStart->Name = L"buttonStart";
				 this->buttonStart->Size = System::Drawing::Size(120, 40);
				 this->buttonStart->TabIndex = 1;
				 this->buttonStart->Text = L"Start";
				 this->buttonStart->UseVisualStyleBackColor = true;
				 this->buttonStart->Click += gcnew System::EventHandler(this, &TrainNetworkForm::buttonStart_Click);
				 // 
				 // timer
				 //
				 this->timer->Interval = 100;
				 this->timer->Tick += gcnew System::EventHandler(this, &TrainNetworkForm::timer_Tick);

				 this->components = gcnew System::ComponentModel::Container();
				 //this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &TrainNetworkForm::TrainNetworkForm_BeforeClosing);
				 this->Load += gcnew System::EventHandler(this, &TrainNetworkForm::TrainNetworkForm_Load);
				 this->Size = System::Drawing::Size(800, 500);
				 this->Text = L"TrainNetworkForm";
				 this->Controls->Add(this->zedGraphError);
				 this->Controls->Add(this->buttonStart);
				 this->Padding = System::Windows::Forms::Padding(0);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			 }
#pragma endregion
	private: System::Void TrainNetworkForm_Load(System::Object^ sender, System::EventArgs^  e)
	{

	}
	private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e)
	{
		GeneratorTrainingForIceThickness training_data(std::make_shared<IceThicknessGenerator>(*m_Generator), *m_Params);
		TTrainingDataVector data_vector;
		data_vector = training_data.GenerateTrainingVector(200);

		m_NetworkHelper->ChangeTrainingDataVector(data_vector);
		timer->Enabled = true;
		buttonStart->Enabled = false;
	}

	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^  e)
	{
		timer->Enabled = false;
		Threading::Thread^ thread_1 = gcnew Threading::Thread(gcnew Threading::ThreadStart(this, &TrainNetworkForm::DoBackgroundWork));
		thread_1->Start();
	}

	private: System::Void DoBackgroundWork()
	{
		double value = 1.0;
		value = m_NetworkHelper->TrainNetwork(0.0001, 1, true);
		if (value > 0.0001 && m_EpochCount < _max_epoch_count)
		{
			m_EpochErrorData.Add(value);
			DrawGraphError();
			m_EpochCount++;
		}
		else
		{
			m_EpochCount = 0;
			SetButtonEnabled();
		}
	}

	private: System::Void DrawGraphError()
	{
		if (zedGraphError->InvokeRequired)
		{
			if (this != nullptr)
			{
				ReturningVoidDelegate^ d =
					gcnew ReturningVoidDelegate(this, &TrainNetworkForm::DrawGraphError);
				this->Invoke(d);
			}
		}
		else
		{
			if (m_EpochErrorData.Count - 1 > _capacity)
			{
				m_EpochErrorData.RemoveAt(0);
				ChangeXAxis(zedGraphError, 1);
			}
			DrawGraph(zedGraphError, %m_EpochErrorData, Color::Red, 1);
			timer->Enabled = true;
		}
	}

	private: System::Void SetButtonEnabled()
	{
		if (this->InvokeRequired)
		{
			ReturningVoidDelegate^ d =
				gcnew ReturningVoidDelegate(this, &TrainNetworkForm::SetButtonEnabled);
			this->Invoke(d);
		}
		else
		{
			buttonStart->Enabled = true;
		}

	}

	};
}
