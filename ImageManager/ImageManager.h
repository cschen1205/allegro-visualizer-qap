#ifndef _H_IMAGE_MANAGER_H
#define _H_IMAGE_MANAGER_H

#include "../allegro_include/allegro.h"
#include <map>
#include <string>

/// <summary>Class that represents the image manager of the game engine<summary>
class ImageManager
{
public:
	/// <summary>Method that return the single instance of the class</summary>
	static ImageManager* Instance();
	/// <summary>Destructor method</summary>
	virtual ~ImageManager();

private:
	/// <summary>Private constructor for the singleton class</summary>
	ImageManager();
	/// <summary>Private copy constructor for the singleton class</summary>
	/// \param[in] rhs the object to be copied
	ImageManager(const ImageManager& rhs);
	/// <summary>Private assigment operator for the singleton class</summary>
	/// \param[in] rhs the object to be copied
	ImageManager& operator=(const ImageManager& rhs);

public:
	/// <summary>Method that load the image into the manager</summary>
	/// \param[in] image_src the path to the image file
	/// <returns>The bitmap image allocated in the manager and loaded from the image file</returns>
	BITMAP* LoadImage(std::string image_src);
	/// <summary>Method that reload the image into the manager</summary>
	/// \param[in] image_src the path to the image file
	/// <returns>The bitmap image allocated in the manager and loaded from the image file</returns>
	BITMAP* ReloadImage(std::string image_src);
	/// <summary>Method that returns a image using its tag</summary>
	/// \param[in] image_src the image tag
	/// <returns>The bitmap image associated with the image tag</returns>
	BITMAP* GetImage(std::string image_src);

private
	/// <summary>The image store</summary>
	std::map<std::string, BITMAP*> m_images;
};

#define SimulatorImageManager ImageManager::Instance()

#endif