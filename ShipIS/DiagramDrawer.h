#pragma once
using namespace ZedGraph;

namespace ShipIS
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	static System::Void PrepareGraph(ZedGraph::ZedGraphControl^ zedGraphControl, const double& y_min, const double& y_max, const double& x_min, const double& x_max)
	{
		GraphPane^ pane = zedGraphControl->GraphPane;

		int labelsFontSize = 25;

		pane->XAxis->Scale->FontSpec->Size = (float)labelsFontSize;
		pane->YAxis->Scale->FontSpec->Size = (float)labelsFontSize;

		pane->XAxis->Scale->MajorStep = x_max / 10.0;
		pane->XAxis->Scale->MinorStep = x_max / 50.0;

		pane->XAxis->MajorGrid->IsVisible = true;
		pane->YAxis->MajorGrid->IsVisible = true;

		pane->XAxis->Title->IsVisible = false;
		pane->YAxis->Title->IsVisible = false;
		pane->Legend->IsVisible = false;
		pane->Title->Text = " ";
		pane->Title->FontSpec->Size = 15;
		//pane->Title->IsVisible = false;

		//pane->XAxis->Scale->Min = x_min;
		//pane->XAxis->Scale->Max = x_max;

		pane->YAxis->Scale->Min = y_min;
		pane->YAxis->Scale->Max = y_max;
		pane->CurveList->Clear();
		zedGraphControl->AxisChange();
		zedGraphControl->Invalidate();
	}

	static System::Void ClearTitles( ZedGraph::ZedGraphControl^ zedGraphControl )
	{
		GraphPane^ pane = zedGraphControl->GraphPane;

		pane->XAxis->Title->IsVisible = false;
		pane->YAxis->Title->IsVisible = false;
		pane->Title->Text = " ";
		pane->Title->FontSpec->Size = 15;
		zedGraphControl->AxisChange();
		zedGraphControl->Invalidate();
	}

	static System::Void DrawGraph(ZedGraph::ZedGraphControl^ zedGraphControl, List<double>^ data, Color color, const double& interval)
	{
		GraphPane^ pane = zedGraphControl->GraphPane;

		PointPairList^ list = gcnew PointPairList();

		double curr_x = pane->XAxis->Scale->Min;
		for (int i = 0; i < data->Count; i++)
		{
			list->Add(curr_x, data[i]);
			curr_x += interval;
		}

		pane->CurveList->Clear();
		LineItem^ myCurve = pane->AddCurve("", list, color, SymbolType::None);
		myCurve->Line->Fill = gcnew ZedGraph::Fill(color);
		zedGraphControl->AxisChange();
		zedGraphControl->Invalidate();
	}

	static System::Void DrawCurve( ZedGraph::ZedGraphControl^ zedGraphControl, List<double>^ data, Color color, String^ name,  const double& interval )
	{
		GraphPane^ pane = zedGraphControl->GraphPane;

		PointPairList^ list = gcnew PointPairList();

		double curr_x = pane->XAxis->Scale->Min;
		for ( int i = 0; i < data->Count; i++ )
		{
			list->Add( curr_x, data[i] );
			curr_x += interval;
		}

		LineItem^ myCurve = pane->AddCurve( name, list, color, SymbolType::None );
		myCurve->Label->FontSpec = gcnew ZedGraph::FontSpec();
		myCurve->Label->FontSpec->Size = 20;
		myCurve->Line->Color = color;
		zedGraphControl->AxisChange();
		zedGraphControl->Invalidate();
	}

	static System::Void ClearCurves( ZedGraph::ZedGraphControl^ zedGraphControl )
	{
		GraphPane^ pane = zedGraphControl->GraphPane;
		pane->CurveList->Clear();
		zedGraphControl->AxisChange();
		zedGraphControl->Invalidate();
	}
	static System::Void ClearGraph(ZedGraph::ZedGraphControl^ zedGraphControl)
	{
		GraphPane^ pane = zedGraphControl->GraphPane;
		pane->CurveList->Clear();
		zedGraphControl->Invalidate();
	}

	static System::Void ChangeXAxis(ZedGraph::ZedGraphControl^ zedGraphControl, const double& interval)
	{
		GraphPane^ pane = zedGraphControl->GraphPane;

		pane->XAxis->Scale->Min += interval;
		pane->XAxis->Scale->Max += interval;
	}

	static System::Void SetDefaultXAxis(ZedGraph::ZedGraphControl^ zedGraphControl, const double& x_min, const double& x_max)
	{
		GraphPane^ pane = zedGraphControl->GraphPane;

		pane->XAxis->Scale->Min = x_min;
		pane->XAxis->Scale->Max = x_max;
	}
}
