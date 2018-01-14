#pragma once

namespace ShipIS
{

ref class GraphDataGenerator;
enum GraphType
{
	NOTHING,
	ICE,
	MATH,
	NEURAL,
	FUZZY,
	PREFER
};
enum GraphColor
{
	RED,
	GREEN,
	AQUA,
	BROWN,
	YELLOW,
	BLUE
};
ref class GraphBlock
{

public:
	GraphBlock( ZedGraphControl^, ComboBox^, ComboBox^, Point);
	System::Void DrawGraphBlock( GraphDataGenerator^ generator, int capacity );
	System::Void SetDefaultXAxis( const double& x_min, const double& x_max );

	ZedGraphControl^ GetZedGraph();
	System::Windows::Forms::ComboBox^ GetComboBoxGraphType();
	System::Windows::Forms::ComboBox^ GetComboBoxGraphColor();


private: ZedGraph::ZedGraphControl^  m_ZedGraph;
private: System::Windows::Forms::ComboBox^  m_ComboBoxGraphType;
private: System::Windows::Forms::ComboBox^  m_ComboBoxGraphColor;

		 std::map<std::string, int>* m_GraphTypes;
		 std::map<std::string, int>* m_GraphColors;
};
}