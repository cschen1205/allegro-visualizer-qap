#ifndef _H_APPLICATION_H
#define _H_APPLICATION_H

#include "../allegro_include/allegro.h"
#include "../Util/Point2D.h"

/// <summary>Class that represents the game engine of the application</summary>
class Application
{
public:
	/// <summary>Singleton method that returns the single instance of this class</summary>
	static Application* Instance();
	/// <summary>Destructor method</summary>
	virtual ~Application();

private:
	/// <summary>Private constructor method</summary>
	Application();
	/// <summary>Private copy constructor</summary>
	/// \param[in] rhs the object to be copied
	Application(const Application& rhs);
	/// <summary>Private assignment operator</summary>
	Application& operator=(const Application& rhs);

protected:
	/// <summary>Method that ticks the timer of the game engine, which is called iteratively to update the game world and characters</summary>
	/// \param[in] deltaTime the time interval between the two cnosecutive calls to the update method
	void Update(float deltaTime);
	/// <summary>Method that renders the sprite images of game agents in the game world onto image buffer and displayed using double-buffer techniques</summary>
	/// \param[in] buffer The image buffer onto which the sprite images of characters in the game worlds are rendered and displayed using double-buffer techniques
	void Render(BITMAP* buffer);
	/// <summary>Method that is called at the end of Run method</summary>
	void End();

public:
	void Run();
	/// <summary>Method that initialize the game engine</summary>
	/// \param[in] width the width of the screen area onto which the animation sprites of game agents are drawn
	/// \param[in] height the height of the screen area onto which the animation sprites of the game characters are drawn
	/// \param[in] windowed the boolean flag indicating whether the game engine should be open in a window mode instead of fullscreen
	bool Init(int width, int height, bool windowed);
	/// <summary>Method that stop the game engine</summary>
	void Quit();

public:
	/// <summary>Method that returns the width of the 2D game world</summary>
	/// <returns>The width of the 2D game world</returns>
	float GetWidth();
	/// <summary>Method that returns the height of the 2D game world</summary>
	/// <returns>The height of the 2D game world</returns>
	float GetHeight();
	/// <summary>Method taht returns the width of the 2D screen</summary>
	/// <returns>The width of the 2D screen</returns>
	float GetScreenWidth() { return m_ScreenSize.GetX(); }
	/// <summary>Method that returns the height of the 2D screen</summary>
	/// <returns>The height of the 2D screen</returns>
	float GetScreenHeight() { return m_ScreenSize.GetY(); }
	/// <summary>Method that returns the vertical inset of hte 2D game world<summary>
	/// <returns>The vertical inset of the 2D game world</returns>
	float GetInsetV() { return m_Inset.GetY(); }
	/// <summary>Method that returns the horizontal inset of the 2D game world</summary>
	/// <returns>The horizontal inset of the 2D game world</returns>
	float GetInsetH() { return m_Inset.GetX(); }
	/// <summary>Method that returns the current top and left coordinate of the 2D game world</summary>
	/// <returns>The current top and left coorindate of the 2D game world</returns>
	Point2D GetTopLeft() { return m_TopLeft; }

private:
	/// <summary>The size of the game engine window</summary>
	Size2D m_WindowSize;
	/// <summary>The actual size of the game world</summary>
	Size2D m_CurrentSize;
	/// <summary>The size of the 2D screen</summary>
	Size2D m_ScreenSize;
	/// <summary>The inset of the game world</summary>
	Point2D m_Inset;
	/// <summary>The top left coordinate of the game world</summary>
	Point2D m_TopLeft;
	/// <summary>The boolean flag indiciating whether the menu is visible</summary>
	bool m_MenuVisible;
	/// <summary>The boolean flag indicating whehter the background image is visible</summary>
	bool m_BackgroundVisible;

private:
	/// <summary>The boolean flag indicating whether the game engine is running</summary>
	volatile bool m_IsRunning;
	/// <summary>The boolean flag indicating whether the game engine should be running in windows mode or fullscreen</summary>
	volatile bool m_IsWindowed;

};

#define Simulator Application::Instance()

#endif