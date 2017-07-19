#include "Application.h"
#include "../allegro_include/winalleg.h"
#include "../ImageManager/ImageManager.h"
#include "../Util/Rect2D.h"
#include "../Util/Point2D.h"
#include "../SceneManager/SceneManager.h"

/// <summary>Destructor method</summary>
Application::Application() : m_IsRunning(false), m_IsWindowed(true), m_Inset(80, 80), m_MenuVisible(false), m_BackgroundVisible(true)
{

}

/// <summary>Private copy constructor</summary>
/// \param[in] rhs the object to be copied
Application::Application(const Application& rhs)
{

}

/// <summary>Private assignment operator</summary>
Application& Application::operator=(const Application& rhs)
{
	return *this;
}

/// <summary>Singleton method that returns the single instance of this class</summary>
Application* Application::Instance()
{
	static Application theInstance;
	return &theInstance;
}

/// <summary>Destructor method</summary>
Application::~Application()
{

}

/// <summary>Method that ticks the timer of the game engine, which is called iteratively to update the game world and characters</summary>
/// \param[in] deltaTime the time interval between the two cnosecutive calls to the update method
void Application::Update(float deltaTime)
{
	if(key[KEY_ESC])
	{
		Quit();
		return;
	}

	float scroll_speed=100;

	float deltaX=0.0f;
	float deltaY=0.0f;

	if(key[KEY_RIGHT])
	{
		deltaX=-scroll_speed * deltaTime;
	}
	if(key[KEY_LEFT])
	{
		deltaX=scroll_speed * deltaTime;
	}

	Rect2D br;
	br.left=m_TopLeft.GetX();
	br.right= br.left + m_CurrentSize.GetX();
	br.top=m_TopLeft.GetY();
	br.bottom = br.top + m_CurrentSize.GetY();

	Rect2D sr;
	sr.left=0;
	sr.right=m_ScreenSize.GetX();
	sr.top=0;
	sr.bottom=m_ScreenSize.GetY();

	if(deltaX != 0)
	{
		if((br.left < sr.left && deltaX> 0) || (br.right > sr.right && deltaX < 0))
		{
			m_TopLeft.SetX(m_TopLeft.GetX()+deltaX);
		}
	}

	if(key[KEY_UP])
	{
		deltaY = scroll_speed * deltaTime;
	}
	if(key[KEY_DOWN])
	{
		deltaY = - scroll_speed * deltaTime;
	}

	if(deltaY != 0)
	{
		if((br.top < sr.top && deltaY> 0) || (br.bottom > sr.bottom && deltaY < 0))
		{
			m_TopLeft.SetY(m_TopLeft.GetY()+deltaY);
		}
	}

	float size_speed=100;
	if(key[KEY_PLUS_PAD])
	{
		m_CurrentSize.SetX(m_CurrentSize.GetX() + size_speed * deltaTime);
		m_CurrentSize.SetY(m_CurrentSize.GetY() + size_speed * deltaTime);
	}
	if(key[KEY_MINUS_PAD])
	{
		if(m_CurrentSize.GetX() > m_ScreenSize.GetX())
		{
			m_CurrentSize.SetX(m_CurrentSize.GetX() - size_speed * deltaTime);
			m_CurrentSize.SetY(m_CurrentSize.GetY() - size_speed * deltaTime);
		}
	}

	if(key[KEY_N])
	{
		m_MenuVisible=false;
	}
	if(key[KEY_M])
	{
		m_MenuVisible=true;
	}

	if(key[KEY_Q])
	{
		m_BackgroundVisible=true;
	}
	if(key[KEY_W])
	{
		m_BackgroundVisible=false;
	}

	SimulatorSceneManager->Update(deltaTime);
}

/// <summary>Method that renders the sprite images of game agents in the game world onto image buffer and displayed using double-buffer techniques</summary>
/// \param[in] buffer The image buffer onto which the sprite images of characters in the game worlds are rendered and displayed using double-buffer techniques
void Application::Render(BITMAP* buffer)
{
	clear_bitmap(buffer);

	if(m_BackgroundVisible)
	{
		BITMAP* bmp=SimulatorImageManager->GetImage("images\\panel_background.bmp");
		stretch_sprite(buffer, bmp, m_TopLeft.GetX(), m_TopLeft.GetY(), GetWidth(), GetHeight());
	}

	SimulatorSceneManager->Render(buffer);

	int left=20;
	
	text_mode(-1);
	
	int txtc=makecol(0, 255, 0);

	if(m_MenuVisible)
	{
		int top=m_ScreenSize.GetY()-150;

		if(m_BackgroundVisible)
		{
			rectfill(buffer, left-10, top-4, left+500, top+60+2, makecol(0, 0, 0));
		}
		rect(buffer, left-10, top-4, left+500, top+60+2, txtc);

		textout(buffer, font, "Press [SPACE_BAR] to toggle between window and fullscreen", left, top, txtc);
		textout(buffer, font, "Press [A] to show station id", left, top+10, txtc);
		textout(buffer, font, "Press [S] to hide station id", left, top+20, txtc);
		textout(buffer, font, "Press [N] to hide the menu", left, top+30, txtc);
		textout(buffer, font, "Press [Q] to show background", left, top+40, txtc);
		textout(buffer, font, "Press [W] to hide background", left, top+50, txtc);
	}
	else
	{
		int top=10;

		if(m_BackgroundVisible)
		{
			rectfill(buffer, left-10, top-4, left+500, top+10+2, makecol(0, 0, 0));
		}
		rect(buffer, left-10, top-4, left+500, top+10+2, txtc);

		textout(buffer, font, "Press [M] to show the menu", left, top, txtc);
	}
}

/// <summary>Method that is called at the end of Run method</summary>
void Application::End()
{

}

void Application::Run()
{
	BITMAP* buffer=create_bitmap(m_CurrentSize.GetX(), m_CurrentSize.GetY());

	long start_time=timeGetTime();
	while(m_IsRunning)
	{
		if(key[KEY_SPACE])
		{
			if(m_IsWindowed)
			{
				m_IsWindowed=false;
			}
			else
			{
				m_IsWindowed=true;
			}

			if(m_IsWindowed)
			{
				set_gfx_mode(GFX_AUTODETECT_WINDOWED, m_WindowSize.GetX(), m_WindowSize.GetY(), 0, 0);
				m_CurrentSize=m_WindowSize;
				m_ScreenSize=m_CurrentSize;
			}
			else
			{
				int width, height;
				get_desktop_resolution(&width, &height);
				m_CurrentSize=Size2D(width, height);
				m_ScreenSize=m_CurrentSize;
				set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, m_CurrentSize.GetX(), m_CurrentSize.GetY(), 0, 0);
			}

			destroy_bitmap(buffer);
			buffer=create_bitmap(m_CurrentSize.GetX(), m_CurrentSize.GetY());
		}

		long end_time=timeGetTime();

		float deltaTime=(end_time - start_time) * 0.001f;

		start_time=end_time;

		Update(deltaTime);

		Render(buffer);

		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, m_CurrentSize.GetX(), m_CurrentSize.GetY());
		release_screen();
	}

	destroy_bitmap(buffer);

	End();
}

/// <summary>Method that stop the game engine</summary>
void Application::Quit()
{
	m_IsRunning=false;
}

/// <summary>Method that initialize the game engine</summary>
/// \param[in] width the width of the screen area onto which the animation sprites of game agents are drawn
/// \param[in] height the height of the screen area onto which the animation sprites of the game characters are drawn
/// \param[in] windowed the boolean flag indicating whether the game engine should be open in a window mode instead of fullscreen
bool Application::Init(int width, int height, bool windowed)
{
	if(allegro_init()!=0)
	{
		return false;
	}

	if(install_keyboard()!=0)
	{
		return false;
	}

	m_WindowSize=Size2D(width, height);
	m_CurrentSize=Size2D(width, height);
	m_ScreenSize=m_CurrentSize;
	m_IsWindowed=windowed;

	set_color_depth(32);

	set_window_title("QAP Visualizer");

	if(m_IsWindowed)
	{
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	}
	else
	{
		get_desktop_resolution(&width, &height);
		m_CurrentSize=Size2D(width, height);
		set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0);
	}

	m_IsRunning=true;

	return true;
}

/// <summary>Method that returns the width of the 2D game world</summary>
/// <returns>The width of the 2D game world</returns>
float Application::GetWidth()
{
	return m_CurrentSize.GetX();
}

/// <summary>Method that returns the height of the 2D game world</summary>
/// <returns>The height of the 2D game world</returns>
float Application::GetHeight()
{
	return m_CurrentSize.GetY();
}
