#include "Behavior_Station.h"
#include "../GameEntity/BaseGameEntity.h"
#include "../ImageManager/ImageManager.h"
#include "../SceneManager/SceneManager.h"
#include "../Application/Application.h"
#include "../PathFinding/GraphNode.h"
#include <cassert>

void thick_line(BITMAP *bmp, float x, float y, float x_, float y_,float thickness, int color)
{
        float dx = x - x_;
        float dy = y - y_;
        float d = sqrtf(dx * dx + dy * dy);
        if (!d)
        return;

        int v[4 * 2];

        /* left up */
        v[0] = x - thickness * dy / d;
        v[1] = y + thickness * dx / d;
        /* right up */
        v[2] = x + thickness * dy / d;
        v[3] = y - thickness * dx / d;
        /* right down */
        v[4] = x_ + thickness * dy / d;
        v[5] = y_ - thickness * dx / d;
        /* left down */
        v[6] = x_ - thickness * dy / d;
        v[7] = y_ + thickness * dx / d;

        polygon(bmp, 4, v, color);
}

/// <summary>Constructor method</summary>
/// \param[in] pOwner the station game agent
Behavior_Station::Behavior_Station(BaseGameEntity* pOwner) : m_pOwner(pOwner)
{
	m_pVehicle=new BaseGameEntity();
	m_pPathPlanner=new PathPlanner(pOwner);
}

/// <summary>Destructor method</summary>
Behavior_Station::~Behavior_Station()
{
	delete m_pVehicle;
	delete m_pPathPlanner;

	m_visited.clear();
	m_unvisited.clear();
}

/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time interval between two consecutive calls to the update method
void Behavior_Station::Update(float deltaTime)
{
	if(m_unvisited.empty() && m_CurrentPath.empty())
	{
		if(!m_CurrentFullPath.empty())
		{
			m_CurrentFullPath.clear();
		}
		return;
	}

	if(m_CurrentPath.empty())
	{
		BaseGameEntity* pStation=m_unvisited.front();
		m_pPathPlanner->PlanPath(*(SimulatorSceneManager->GetGraph()), pStation, m_CurrentPath);

		m_CurrentFullPath.clear();
		m_CurrentFullPath.assign(m_CurrentPath.begin(), m_CurrentPath.end());

		GraphNode* pNode=SimulatorSceneManager->GetGraph()->GetNode(m_CurrentPath.front()->GetFrom());
		m_pVehicle->SetPosition(pNode->GetPosition());

		m_visited.push_back(pStation);
		m_unvisited.pop_front();
	}
	
	assert(!m_CurrentPath.empty());

	GraphNode* pNode=SimulatorSceneManager->GetGraph()->GetNode(m_CurrentPath.front()->GetTo());

	Point2D disp=pNode->GetPosition() - m_pVehicle->GetPosition();
	float dist=disp.Length();

	float d=m_speed * deltaTime;
	if(d <= dist)
	{
		Point2D dir=disp.Normalize();
		m_pVehicle->SetPosition(m_pVehicle->GetPosition() + dir * d);

		m_angle=fixatan2(ftofix(disp.GetY()), ftofix(disp.GetX()));

	}
	else
	{
		m_pVehicle->SetPosition(pNode->GetPosition());
		m_CurrentPath.pop_front();
	}

}

/// <summary>Method that renders the images and drawings of the station agent</summary>
/// \param[in] buffer the image buffer onto which the images and drawings of the station agent are rendered and displayed using the double-buffer techniques
void Behavior_Station::Render(BITMAP* buffer)
{
	if(m_CurrentPath.empty())
	{
		return;
	}

	GraphNode* pNode=SimulatorSceneManager->GetGraph()->GetNode(m_CurrentPath.front()->GetTo());

	for(int i=0; i<m_CurrentFullPath.size(); i++)
	{
		GraphEdge* pEdge=m_CurrentFullPath[i];
		Point2D pos1=SimulatorSceneManager->GetGraph()->GetNode(pEdge->GetFrom())->GetPositionOnSimulator();
		Point2D pos2=SimulatorSceneManager->GetGraph()->GetNode(pEdge->GetTo())->GetPositionOnSimulator();

		//line(buffer, pos1.GetX()-2, pos1.GetY()-2, pos2.GetX()-2, pos2.GetY()-2, makecol(0, 255, 0));
		//line(buffer, pos1.GetX()+2, pos1.GetY()+2, pos2.GetX()+2, pos2.GetY()+2, makecol(0, 255, 0));
		thick_line(buffer, pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), 4, makecol(125, 125, 125));
	}

	for(int i=0; i<m_CurrentFullPath.size(); i++)
	{
		GraphEdge* pEdge=m_CurrentFullPath[i];
		Point2D pos1=SimulatorSceneManager->GetGraph()->GetNode(pEdge->GetFrom())->GetPositionOnSimulator();
		Point2D pos2=SimulatorSceneManager->GetGraph()->GetNode(pEdge->GetTo())->GetPositionOnSimulator();

		thick_line(buffer, pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), 2, makecol(200, 200, 200));
	}

	for(int i=0; i<m_CurrentFullPath.size(); i++)
	{
		GraphEdge* pEdge=m_CurrentFullPath[i];
		Point2D pos1=SimulatorSceneManager->GetGraph()->GetNode(pEdge->GetFrom())->GetPositionOnSimulator();
		Point2D pos2=SimulatorSceneManager->GetGraph()->GetNode(pEdge->GetTo())->GetPositionOnSimulator();

		line(buffer, pos1.GetX(), pos1.GetY(), pos2.GetX(), pos2.GetY(), makecol(125, 125, 125));
	}

	BITMAP* vbmp=SimulatorImageManager->GetImage("images\\cargo.bmp");

	float fw=Simulator->GetWidth() / (SimulatorSceneManager->GetSideCount()*5);
	float scale=fw / vbmp->w;

	//circle(buffer, m_pVehicle->GetPositionOnSimulator().GetX(), m_pVehicle->GetPositionOnSimulator().GetY(), 3, makecol(255, 0, 0));
	pivot_scaled_sprite(buffer, vbmp, m_pVehicle->GetPositionOnSimulator().GetX(), m_pVehicle->GetPositionOnSimulator().GetY(), vbmp->w/2, vbmp->h/2, m_angle, ftofix(scale));
}

/// <summary>Method that add the station agent visited by the vehicle from the station</summary>
/// \param[in] pStation the station agent added to the vehicle's route of the station
void Behavior_Station::RegisterStation(BaseGameEntity* pStation)
{
	m_unvisited.push_back(pStation);
}

/// <summary>Method that start the engine of the vehicle agent</summary>
void Behavior_Station::Start()
{
	while(!m_visited.empty())
	{
		m_unvisited.push_back(m_visited.front());
		m_visited.pop_front();
	}

	/*
	BaseGameEntity* pStation=m_unvisited.front();

	m_CurrentPath.clear();
	m_pPathPlanner->PlanPath(*(SimulatorSceneManager->GetGraph()), pStation, m_CurrentPath);

	m_CurrentFullPath.clear();
	m_CurrentFullPath.assign(m_CurrentPath.begin(), m_CurrentPath.end());

	GraphNode* pNode=SimulatorSceneManager->GetGraph()->GetNode(m_CurrentPath.front()->GetFrom());
	m_pVehicle->SetPosition(pNode->GetPosition());

	m_visited.push_back(pStation);
	m_unvisited.pop_front();
	*/


}
