#include "GraphBlock.h"

namespace ShipIS
{

GraphBlock::GraphBlock( ZedGraphControl ^ zed_graph, ComboBox ^ combo_box_type, ComboBox ^ combo_box_color, Point begin_point )
{
	std::map<std::string, int> graph_types;
	graph_types["Nothing"] = NOTHING;
	graph_types["Ice thickness"] = ICE;
	graph_types["Math velocity"] = MATH;
	graph_types["Neural velocity"] = NEURAL;
	graph_types["Fuzzy velocity"] = FUZZY;
	graph_types["Prefer velocity"] = PREFER;
	m_GraphTypes = new std::map<std::string, int>( graph_types );

	std::map<std::string, int> graph_color;

	graph_color["Red"] = GraphColor::RED;
	graph_color["Green"] = GraphColor::GREEN;
	graph_color["Aqua"] = GraphColor::AQUA;
	graph_color["Brown"] = GraphColor::BROWN;
	graph_color["Yellow"] = GraphColor::YELLOW;
	graph_color["Blue"] = GraphColor::BLUE;

	m_GraphColors = new std::map<std::string, int>( graph_color );

	//
	//m_ComboBoxGraphType
	//
	this->m_ComboBoxGraphType = combo_box_type;
	this->m_ComboBoxGraphType->FormattingEnabled = true;
	this->m_ComboBoxGraphType->Location = begin_point;
	this->m_ComboBoxGraphType->Name = L"ComboBoxGraphType";
	this->m_ComboBoxGraphType->Items->AddRange( gcnew array<Object^>( 6 )
	{
		L"Nothing",
			L"Ice thickness",
			L"Math velocity",
			L"Neural velocity",
			L"Fuzzy velocity",
			L"Prefer velocity"
	}
	);
	this->m_ComboBoxGraphType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->m_ComboBoxGraphType->SelectedIndex = 0;
	this->m_ComboBoxGraphType->Size = System::Drawing::Size( 140, 21 );

	//
	//m_ComboBoxGraphColor
	//
	this->m_ComboBoxGraphColor = combo_box_color;
	this->m_ComboBoxGraphColor->FormattingEnabled = true;
	this->m_ComboBoxGraphColor->Location = Point( begin_point.X + m_ComboBoxGraphType->Size.Width + 10, begin_point.Y );
	this->m_ComboBoxGraphColor->Name = L"ComboBoxGraphColor";
	this->m_ComboBoxGraphColor->Items->AddRange( gcnew array<Object^>( 6 )
	{
		L"Red",
			L"Green",
			L"Aqua",
			L"Brown",
			L"Yellow",
			L"Blue"
	}
	);
	this->m_ComboBoxGraphColor->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->m_ComboBoxGraphColor->SelectedIndex = 0;
	this->m_ComboBoxGraphColor->Size = System::Drawing::Size( 140, 21 );

	//
	// m_ZedGraph
	// 
	this->m_ZedGraph = zed_graph;
	this->m_ZedGraph->Cursor = System::Windows::Forms::Cursors::Hand;
	this->m_ZedGraph->Location = Point( begin_point.X, begin_point.Y + m_ComboBoxGraphType->Size.Height + 10 );
	this->m_ZedGraph->Name = L"ZedGraph";
	this->m_ZedGraph->ScrollGrace = 0;
	this->m_ZedGraph->ScrollMaxX = 0;
	this->m_ZedGraph->ScrollMaxY = 0;
	this->m_ZedGraph->ScrollMaxY2 = 0;
	this->m_ZedGraph->ScrollMinX = 0;
	this->m_ZedGraph->ScrollMinY = 0;
	this->m_ZedGraph->ScrollMinY2 = 0;
	this->m_ZedGraph->Size = System::Drawing::Size( 600, 150 );
}

ZedGraphControl^ GraphBlock::GetZedGraph()
{
	return m_ZedGraph;
}

System::Windows::Forms::ComboBox^ GraphBlock::GetComboBoxGraphType()
{
	return m_ComboBoxGraphType;
}

System::Windows::Forms::ComboBox^ GraphBlock::GetComboBoxGraphColor()
{
	return m_ComboBoxGraphColor;
}

System::Void GraphBlock::DrawGraphBlock( GraphDataGenerator^ generator, int capacity )
{
	msclr::interop::marshal_context context;
	auto selected_graph = context.marshal_as<std::string>( m_ComboBoxGraphType->SelectedItem->ToString() );
	auto type = *m_GraphTypes;
	double y_max_value = 1;
	List<double>^ data = generator->GetIceThickness();

	if ( data->Count - 1 > capacity )
	{
		ChangeXAxis( m_ZedGraph, generator->GetParams()->interval );
	}

	switch ( type[selected_graph] )
	{
	case ICE:
		data = generator->GetIceThickness();
		y_max_value = generator->GetParams()->max_ice_thick;
		break;
	case MATH:
		data = generator->GetMathVelocity();
		y_max_value = generator->GetParams()->max_velocity;
		break;
	case NEURAL:
		data = generator->GetNeuralVelocity();
		y_max_value = generator->GetParams()->max_velocity;
		break;
	case FUZZY:
		data = generator->GetFuzzyVelocity();
		y_max_value = generator->GetParams()->max_velocity;
		break;
	case PREFER:
		data = generator->GetPreferVelocity();
		y_max_value = generator->GetParams()->max_velocity;
		break;
	case NOTHING:
		ClearGraph( m_ZedGraph );
		return;
	default:
		ClearGraph( m_ZedGraph );
		return;
	}
	auto selected_color = context.marshal_as<std::string>( m_ComboBoxGraphColor->SelectedItem->ToString() );
	auto color = *m_GraphColors;
	Color graph_col;
	switch ( color[selected_color] )
	{
	case RED:
		graph_col = Color::Red;
		break;
	case GREEN:
		graph_col = Color::Green;
		break;
	case AQUA:
		graph_col = Color::Aqua;
		break;
	case BROWN:
		graph_col = Color::Brown;
		break;
	case YELLOW:
		graph_col = Color::Yellow;
		break;
	case BLUE:
		graph_col = Color::Blue;
		break;
	default:
		return;
	}
	PrepareGraph( m_ZedGraph, 0, y_max_value, 0, generator->GetParams()->interval * capacity );
	DrawGraph( m_ZedGraph, data, graph_col, generator->GetParams()->interval );
}

System::Void GraphBlock::SetDefaultXAxis( const double & x_min, const double & x_max )
{
	ShipIS::SetDefaultXAxis( m_ZedGraph, x_min, x_max );
}

}
