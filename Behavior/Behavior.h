#ifndef _H_BEHAVIOR_H
#define _H_BEHAVIOR_H

#include "../allegro_include/allegro.h"

/// <summary>Class that represents the behavior of a game agent</summary>
class Behavior
{
public:
	/// <summary>Method that ticks the timer, which is iteratively called within the game agent's update method</summary>
	/// \param[in] deltaTime the time interval between two consecutive calls to update
	virtual void Update(float deltaTime)=0;
	/// <summary>Method that renders images and drawing associated with the behavior</summary>
	/// \param[in] buffer the image buffer onto which the rendering is performend and displayed using the double-buffer technique
	virtual void Render(BITMAP* buffer)=0;
};

#endif