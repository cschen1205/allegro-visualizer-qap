#ifndef _H_SCENE_MANAGER_H
#define _H_SCENE_MANAGER_H

#include <string>
#include "../Util/Rect2D.h"
#include "../GameEntity/BaseGameEntity.h"
#include <vector>
#include "../allegro_include/allegro.h"
#include "../PathFinding/Graph.h"

/// <summary>Class that represents the game world of the game engine</summary>
class SceneManager
{
public:
	/// <summary>Method that returns the singleton instance of the class</summary>
	/// <returns>The singleton instance of the class</returns>
	static SceneManager* Instance();
	/// <summary>Destructor method</summary>
	virtual ~SceneManager();

private:
	/// <summary>Private constructor</summary>
	SceneManager();
	/// <summary>Private copy constructor</summary>
	/// \param[in] rhs the object to be copied
	SceneManager(const SceneManager& rhs);
	/// <summary>Private assignment operator</summary>
	/// \param[in] rhs the object to be copied
	SceneManager& operator=(const SceneManager& rhs);

public:
	/// <summary>Method that updates all the game agents in the world when the timer ticks in the game engine</summary>
	/// \param[in] deltaTime the time duration between two consecutive calls to the update method
	void Update(float deltaTime);
	/// <summary>Method taht renders all the game agents in the world</summary>
	/// \param[in] buffer the image buffer onto which the game agents are rendered and displayed using double-buffer techniques
	void Render(BITMAP* buffer);

protected:
	/// <summary>Method that initialize the game world</summary>
	/// \param[in] filename the configuration file of the application
	/// <returns>The boolean flag indicating whether the loading and initialization is successful</returns>
	bool Init(std::string filename);

public:
	/// <summary>Method that returns the activity region of the game engine</summary>
	/// <returns>The activity region of the game engine</returns>
	Rect2D GetActivityZone() { return m_ActivityZone; }
private:
	/// <summary>the activity region of the game engine</summary>
	Rect2D m_ActivityZone;

private:
	/// <summary>The boolean flag indicating whether the station id should be visible</summary>
	 bool m_StationIdVisible;
protected:
	/// <summary>Method that renders the station id on each station agent</summary>
	/// \param[in] buffer the image buffer onto which the station ids are rendered and displayed using double-buffer technique
	void RenderStationId(BITMAP* buffer);
	/// <summary>Method that renders the station agents</summary>
	/// \param[in] buffer the image buffer onto which the stations are rendered and displayed using double-buffer technique
	void RenderStations(BITMAP* buffer);

private:
	/// <summary>The set of stations managed in the game world</summary>
	std::vector<BaseGameEntity*> m_assignments;
	

private:
	/// <summary>The graph on which the stations are the nodes and the edge are the paths travelled by the vehicles of the stations</summary>
	Graph* m_pGraph;
public:
	/// <summary>Method that return the graph</summary>
	Graph* GetGraph() { return m_pGraph; }

private:
	/// <summary>The number of stations on the width / height of the game world</summary>
	int m_SideCount;
public:
	/// <summary>Method that returns the number of stations on the width / height of the game world</summary>
	/// <returns>The number of stations on the width / height of the game world</returns>
	int GetSideCount() { return m_SideCount; }

};

#define SimulatorSceneManager SceneManager::Instance()

#endif