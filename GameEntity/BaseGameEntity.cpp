#include "BaseGameEntity.h"
#include "../Application/Application.h"
#include "../SceneManager/SceneManager.h"
#include "../Util/Rect2D.h"
#include <cassert>

/// <summary>Constructor method</summary>
BaseGameEntity::BaseGameEntity() : m_pBehavior(NULL)
{

}

/// <summary>Destructor method</summary>
BaseGameEntity::~BaseGameEntity()
{
	if(m_pBehavior!=NULL)
	{
		delete m_pBehavior;
		m_pBehavior=NULL;
	}
}

/// <summary>Method that return the game agent's translated position on the game world</summary>
Point2D BaseGameEntity::GetPositionOnSimulator()
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

/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
/// \param[in] deltaTime the time duration between two consecutive calls to the update method
void BaseGameEntity::Update(float deltaTime)
{
	if(m_pBehavior!=NULL)
	{
		m_pBehavior->Update(deltaTime);
	}
}

/// <summary>Method that renders the image and drawing associated with the game agent</summary>
/// \param[in] buffer the image buffer onto which the images and drawings associated with the game agent are rendered and displayed as the double-buffer technique
void BaseGameEntity::Render(BITMAP* buffer)
{
	if(m_pBehavior!=NULL)
	{
		m_pBehavior->Render(buffer);
	}
}

/// <summary>Method that sets the behavior of the game agent</summary>
/// \param[in] pBehavior the behvior expressed by the game agent
void BaseGameEntity::SetBehavior(Behavior* pBehavior)
{
	if(m_pBehavior!=NULL)
	{
		delete m_pBehavior;
		m_pBehavior=NULL;
	}

	m_pBehavior=pBehavior;
}
