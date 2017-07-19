#include "GraphNode.h"
#include "../Application/Application.h"
#include "../Util/Rect2D.h"
#include "../SceneManager/SceneManager.h"
#include "../GameEntity/BaseGameEntity.h"
#include <cassert>

/// <summary>Method that return the position in relation to the game world</summary>
/// <returns>The position in relation to the game world</returns>
Point2D GraphNode::GetPositionOnSimulator()
{
	Rect2D rect=SimulatorSceneManager->GetActivityZone();
	Point2D pos=m_position - Point2D(rect.left, rect.top);

	assert(rect.Width()!=0);
	assert(rect.Height()!=0);

	pos=Point2D(
		pos.GetX() * (Simulator->GetWidth() - Simulator->GetInsetH() * 2) / rect.Width(), 
		pos.GetY() * (Simulator->GetHeight() - Simulator->GetInsetV() * 2) / rect.Height()
		);

	pos+=Simulator->GetTopLeft();
	pos+=Point2D(Simulator->GetInsetH(), Simulator->GetInsetV());

	return pos;
}

/// <summary>Constructor method</summary>
/// \param[in] id the id of the graph node
GraphNode::GraphNode(int id) : m_pEntity(NULL), m_id(id)
{

}

/// <summary>Destructor method</summary>
GraphNode::~GraphNode()
{
	std::vector<GraphEdge*>::iterator pos;
	for(pos=m_edges.begin(); pos!=m_edges.end(); ++pos)
	{
		delete (*pos);
	}
	m_edges.clear();
	m_pEntity=NULL;
}

/// <summary>Method that forms the edge with another node</summary>
/// \param[in] pNode another node to connect with
void GraphNode::Connect2(GraphNode* pNode)
{
	GraphEdge* pEdge=new GraphEdge(m_id, pNode->GetID());
	Point2D disp=m_position - pNode->GetPosition();
	float cost=disp.Length();
	pEdge->SetCost(cost);

	m_edges.push_back(pEdge);
}

/// <summary>Method that sets a game agent as the representation of the node in the game world</returns>
/// \param[in] pEntity the game agemt that sits on the graph node
void GraphNode::ConnectEntity(BaseGameEntity* pEntity)
{
	m_pEntity=pEntity;
}
