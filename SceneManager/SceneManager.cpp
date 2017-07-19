#include "SceneManager.h"
#include "../Application/Application.h"
#include "../tinyxml/tinyxml.h"
#include "../Behavior/Behavior_Station.h"
#include "../ImageManager/ImageManager.h"
#include <cfloat>
#include <string>
#include <sstream>

/// <summary>Destructor method</summary>
SceneManager::SceneManager() :  m_StationIdVisible(true)
{
	m_pGraph=NULL;
	//m_CurrentActiveStationId=0;
	if(!Init("qap_gui.xml"))
	{
		Simulator->Quit();
	}
}

/// <summary>Private copy constructor</summary>
/// \param[in] rhs the object to be copied
SceneManager::SceneManager(const SceneManager& rhs)
{

}

/// <summary>Private assignment operator</summary>
/// \param[in] rhs the object to be copied
SceneManager& SceneManager::operator=(const SceneManager& rhs)
{
	return *this;
}

/// <summary>Method that returns the singleton instance of the class</summary>
/// <returns>The singleton instance of the class</returns>
SceneManager* SceneManager::Instance()
{
	static SceneManager theInstance;
	return &theInstance;
}

/// <summary>Destructor method</summary>
SceneManager::~SceneManager()
{
	std::vector<BaseGameEntity*>::iterator pos;
	for(pos=m_assignments.begin(); pos!=m_assignments.end(); ++pos)
	{
		delete (*pos);
	}
	m_assignments.clear();

	if(m_pGraph!=NULL)
	{
		delete m_pGraph;
		m_pGraph=NULL;
	}
}

/// <summary>Method that initialize the game world</summary>
/// \param[in] filename the configuration file of the application
/// <returns>The boolean flag indicating whether the loading and initialization is successful</returns>
bool SceneManager::Init(std::string filename)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filename.c_str()))
	{
		return false;
	}

	TiXmlElement* pXmlRoot=doc.RootElement();

	m_ActivityZone.left=FLT_MAX;
	m_ActivityZone.right=-FLT_MAX;
	m_ActivityZone.top=FLT_MAX;
	m_ActivityZone.bottom=-FLT_MAX;

	int count;
	pXmlRoot->QueryIntAttribute("count", &count);

	m_assignments.resize(count);

	int side=(int)(sqrt((float)count));

	if(side*side < count)
	{
		side++;
	}

	m_SideCount=side;

	int x=0;
	int y=0;
	int max_x=0;
	int max_y=0;
	int counter=0;
	for(TiXmlElement* pXmlElement1=pXmlRoot->FirstChildElement(); pXmlElement1!=NULL; pXmlElement1=pXmlElement1->NextSiblingElement())
	{
		if(strcmp(pXmlElement1->Value(), "assignment")==0)
		{
			x = counter % side;
			y = counter / side;

			x*=2;
			y*=2;

			if(max_x < x)
			{
				max_x=x;
			}
			if(max_y < y)
			{
				max_y=y;
			}

			std::string id=pXmlElement1->Attribute("factory");

			int location_id=0;
			pXmlElement1->QueryIntAttribute("location", &location_id);

			if(m_ActivityZone.left > x)
			{
				m_ActivityZone.left=x;
			}
			if(m_ActivityZone.right < x)
			{
				m_ActivityZone.right=x;
			}
			if(m_ActivityZone.top > y)
			{
				m_ActivityZone.top=y;
			}
			if(m_ActivityZone.bottom < y)
			{
				m_ActivityZone.bottom=y;
			}

			BaseGameEntity* pV=new BaseGameEntity();
			
			pV->SetPosition(Point2D(x, y));
			pV->SetID(id);

			m_assignments[location_id]=pV;
			counter++;
		}
	}

	m_pGraph=new Graph();

	m_pGraph->Init(0, 0, max_x, max_y, 1, 1);

	for(int i=0; i<count; i++)
	{
		BaseGameEntity* pStation=m_assignments[i];
		m_pGraph->ConnectEntity(pStation);
	}

	for(int i=0; i<count; i++)
	{
		BaseGameEntity* pStation=m_assignments[i];
		Behavior_Station* pBehavior=new Behavior_Station(pStation);
		for(int j=0; j<count; j++)
		{
			if(i==j)
			{
				continue;
			}
			pBehavior->RegisterStation(m_assignments[j]);
		}

		pStation->SetBehavior(pBehavior);
		pBehavior->SetSpeed((float)3/side*2);
		/*
		if(i==m_CurrentActiveStationId)
		{
			pBehavior->Start();
		}
		*/
	}

	return true;
}

/// <summary>Method taht renders all the game agents in the world</summary>
/// \param[in] buffer the image buffer onto which the game agents are rendered and displayed using double-buffer techniques
void SceneManager::Render(BITMAP* buffer)
{
	//m_pGraph->Render(buffer);

	RenderStations(buffer);

	if( m_StationIdVisible)
	{
		RenderStationId(buffer);
	}
	
	
}

/// <summary>Method that renders the station agents</summary>
/// \param[in] buffer the image buffer onto which the stations are rendered and displayed using double-buffer technique
void SceneManager::RenderStations(BITMAP* buffer)
{
	BITMAP* bmp=SimulatorImageManager->GetImage("images\\assignment_card.bmp");
	for(int i=0; i<m_assignments.size(); i++)
	{
		m_assignments[i]->Render(buffer);
	}

	float fw=Simulator->GetWidth() / (m_SideCount+1);
	float fh=fw * bmp->h / bmp->w;
	for(int i=0; i<m_assignments.size(); i++)
	{
		Point2D pos=m_assignments[i]->GetPositionOnSimulator();

		//ellipsefill(buffer, pos.GetX(), pos.GetY(), fw/2, fh/2, makecol(125, 125, 125));

		stretch_sprite(buffer, bmp, pos.GetX() - fw / 2, pos.GetY() - fh /2, fw, fh);
		//draw_sprite(buffer, bmp, pos.GetX() - bmp->w / 2, pos.GetY() - bmp->h /2 );
		
		//ellipse(buffer, pos.GetX(), pos.GetY(), fw/2, fh/2, makecol(0, 255, 0));
		//ellipse(buffer, pos.GetX(), pos.GetY(), fw/2+1, fh/2+1, makecol(0, 125, 0));

		/*
		rectfill(buffer, pos.GetX()-fw/2-5, pos.GetY()+40, pos.GetX()+fw/2+5, pos.GetY()+60, makecol(0, 0, 0));
		rect(buffer, pos.GetX()-fw/2-5, pos.GetY()+40, pos.GetX()+fw/2+5, pos.GetY()+60, makecol(0, 255, 0));
		*/

		std::ostringstream oss;
		oss << "location: " << i;
		std::string msg=oss.str();
		textout(buffer, font, msg.c_str(), pos.GetX()-30, pos.GetY()+5, makecol(0, 255, 0));
	}
}

/// <summary>Method that updates all the game agents in the world when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time duration between two consecutive calls to the update method
void SceneManager::Update(float deltaTime)
{
	if(key[KEY_A])
	{
		m_StationIdVisible=true;
	}
	if(key[KEY_S])
	{
		m_StationIdVisible=false;
	}

	/*
	Behavior_Station* pBehavior=dynamic_cast<Behavior_Station*>(m_assignments[m_CurrentActiveStationId]->GetBehavior());
	if(pBehavior->IsEnded())
	{
		m_CurrentActiveStationId++;
		if(m_CurrentActiveStationId >= m_assignments.size())
		{
			m_CurrentActiveStationId=0;
		}
		return;
	}

	pBehavior->Update(deltaTime);
	*/


	std::vector<BaseGameEntity*>::iterator pos;
	
	for(pos=m_assignments.begin(); pos!=m_assignments.end(); ++pos)
	{
		Behavior_Station* pBehavior=dynamic_cast<Behavior_Station*>((*pos)->GetBehavior());
		if(pBehavior->IsEnded())
		{
			pBehavior->Start();
		}
		(*pos)->Update(deltaTime);
	}

}

/// <summary>Method that renders the station id on each station agent</summary>
/// \param[in] buffer the image buffer onto which the station ids are rendered and displayed using double-buffer technique
void SceneManager::RenderStationId(BITMAP* buffer)
{
	for(int i=0; i < m_assignments.size(); i++)
	{
		Point2D pos=m_assignments[i]->GetPositionOnSimulator();
		pos.SetY(pos.GetY()+5);

		/*
		circlefill(buffer, pos.GetX()+25, pos.GetY()-12, 10, makecol(255, 255, 255));
		circle(buffer, pos.GetX()+25, pos.GetY()-12, 10, makecol(0, 255, 0));
		*/
		
		//textout(buffer, font, "id: ", pos.GetX()-40, pos.GetY()-20, makecol(0, 0, 0));

		std::ostringstream oss;
		oss << "factory: " << m_assignments[i]->GetID().c_str();
		std::string msg=oss.str();
		textout(buffer, font, msg.c_str(), pos.GetX()-30, pos.GetY()-10, makecol(0, 255, 0));
	}
}

