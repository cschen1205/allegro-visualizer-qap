#ifndef _H_BEHAVIOR_STATION_H
#define _H_BEHAVIOR_STATION_H

#include "Behavior.h"
#include <list>
#include <vector>
#include "../PathFinding/PathPlanner.h"
#include "../PathFinding/GraphEdge.h"

class BaseGameEntity;

/// <summary>Class that represents the behavior expressed by the station agent</summary>
class Behavior_Station : public Behavior
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] pOwner the station game agent
	Behavior_Station(BaseGameEntity* pOwner);
	/// <summary>Destructor method</summary>
	virtual ~Behavior_Station();

public:
	/// <summary>Method that update the game agent when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time interval between two consecutive calls to the update method
	virtual void Update(float deltaTime);
	/// <summary>Method that renders the images and drawings of the station agent</summary>
	/// \param[in] buffer the image buffer onto which the images and drawings of the station agent are rendered and displayed using the double-buffer techniques
	virtual void Render(BITMAP* buffer);

public:
	/// <summary>Method that start the engine of the vehicle agent</summary>
	void Start();

public:
	/// <summary>Method that add the station agent visited by the vehicle from the station</summary>
	/// \param[in] pStation the station agent added to the vehicle's route of the station
	void RegisterStation(BaseGameEntity* pStation);
	/// <summary>Method that set the speed of the vehicle of the station</summary>
	/// \param[in] f the new value of vehicle speed
	void SetSpeed(float f) { m_speed=f; }

public:
	/// <summary>Method that determines whether the vehicle has ended its tour</summary>
	bool IsEnded() { return m_unvisited.empty() && m_CurrentPath.empty(); }

private:
	/// <summary>stations that have already visited by the vehicle of the station</summary>
	std::list<BaseGameEntity* > m_unvisited;
	/// <summary>stations that are yet to be visited by the vehicle of the station</summary>
	std::list<BaseGameEntity* > m_visited;
	/// <summary>The station agent</summary>
	BaseGameEntity* m_pOwner;
	/// <summary>The vehicle of the station</summary>
	BaseGameEntity* m_pVehicle;
	/// <summary>The speed of the vehicle</summary>
	float m_speed;
	/// <summary>The rotation angle of the vehicle</summary>
	fixed m_angle;
	/// <summary>The path planner for the vehicle of the station</summary>
	PathPlanner* m_pPathPlanner;
	/// <summary>The currently travelled path</summary>
	std::list<GraphEdge*> m_CurrentPath;
	/// <summary>The currently travelled full path of the vehicle of the station</summary>
	std::vector<GraphEdge*> m_CurrentFullPath;
};
#endif