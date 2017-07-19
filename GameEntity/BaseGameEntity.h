#ifndef _H_BASE_GAME_ENTITY_H
#define _H_BASE_GAME_ENTITY_H

#include "../Util/Point2D.h"
#include "../allegro_include/allegro.h"
#include "../Behavior/Behavior.h"
#include <string>

/// <summary>Class that represents a game engine in the game world</summary>
class BaseGameEntity
{
public:
	/// <summary>Constructor method</summary>
	BaseGameEntity();
	/// <summary>Destructor method</summary>
	virtual ~BaseGameEntity();

public:
	/// <summary>Method that sets the position of the game agent</summary>
	void SetPosition(Point2D point) { m_position=point; }
	/// <summary>Method that returns the position of the game agent</summary>
	Point2D GetPosition() { return m_position; }
	/// <summary>Method that return the game agent's translated position on the game world</summary>
	Point2D GetPositionOnSimulator();

public:
	/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time duration between two consecutive calls to the update method
	void Update(float deltaTime);
	/// <summary>Method that renders the image and drawing associated with the game agent</summary>
	/// \param[in] buffer the image buffer onto which the images and drawings associated with the game agent are rendered and displayed as the double-buffer technique
	void Render(BITMAP* buffer);

public
	/// <summary>Method that sets the behavior of the game agent</summary>
	/// \param[in] pBehavior the behvior expressed by the game agent
	void SetBehavior(Behavior* pBehavior);
/// <summary>Method that returns the behavior expressed by the game agent</summary>
	/// <returns>the behavior expressed by the game agent</returns>
	Behavior* GetBehavior() { return m_pBehavior; }

public:
	/// <summary>Method that return the id of the agent</summary>
	/// <returns>The id of the agent</returns>
	std::string GetID() { return m_id; }
	/// <summary>Method that set the id of the agent</summary>
	/// <returns>The id of the agent</returns>
	void SetID(std::string id) { m_id=id; }

private:
	/// <summary>The position of the game agent</summary>
	Point2D m_position;
	/// <summary>The behavior of the game agent</summary>
	Behavior* m_pBehavior;
	/// <summary>The id of the game agent</summary>
	std::string m_id;
};
#endif