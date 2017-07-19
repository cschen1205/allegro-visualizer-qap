#include "ImageManager.h"
#include <cassert>

/// <summary>Destructor method</summary>
ImageManager::ImageManager()
{

}

/// <summary>Private copy constructor for the singleton class</summary>
/// \param[in] rhs the object to be copied
ImageManager::ImageManager(const ImageManager& rhs)
{

}

/// <summary>Private assigment operator for the singleton class</summary>
/// \param[in] rhs the object to be copied
ImageManager& ImageManager::operator=(const ImageManager& rhs)
{
	return *this;
}

/// <summary>Method that return the single instance of the class</summary>
ImageManager* ImageManager::Instance()
{
	static ImageManager theInstance;
	return &theInstance;
}

/// <summary>Destructor method</summary>
ImageManager::~ImageManager()
{
	std::map<std::string, BITMAP*>::iterator pos;
	for(pos=m_images.begin(); pos!=m_images.end(); ++pos)
	{
		destroy_bitmap(pos->second);
	}
	m_images.clear();
}

/// <summary>Method that load the image into the manager</summary>
/// \param[in] image_src the path to the image file
/// <returns>The bitmap image allocated in the manager and loaded from the image file</returns>
BITMAP* ImageManager::LoadImage(std::string image_src)
{
	std::map<std::string, BITMAP*>::iterator pos=m_images.find(image_src);
	if(pos!=m_images.end())
	{
		return NULL;
	}

	BITMAP* img=load_bitmap(image_src.c_str(), NULL);

	assert(img!=NULL);

	m_images[image_src]=img;

	return img;
}

/// <summary>Method that reload the image into the manager</summary>
/// \param[in] image_src the path to the image file
/// <returns>The bitmap image allocated in the manager and loaded from the image file</returns>
BITMAP* ImageManager::ReloadImage(std::string image_src)
{
	std::map<std::string, BITMAP*>::iterator pos=m_images.find(image_src);
	if(pos!=m_images.end())
	{
		destroy_bitmap(pos->second);
	}

	BITMAP* img=load_bitmap(image_src.c_str(), NULL);

	assert(img!=NULL);

	m_images[image_src]=img;

	return img;
}

/// <summary>Method that returns a image using its tag</summary>
/// \param[in] image_src the image tag
/// <returns>The bitmap image associated with the image tag</returns>
BITMAP* ImageManager::GetImage(std::string image_src)
{
	std::map<std::string, BITMAP*>::iterator pos=m_images.find(image_src);
	if(pos!=m_images.end())
	{
		return pos->second;
	}

	return LoadImage(image_src);
}
