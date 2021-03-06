#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Main.h"
#include "Texture.h"

namespace GaltE
{
	/**
	* Manages all textures. Can read a file in the proper format to add textures
	* or can add them one by one. Texture manager works by giving each texture it reads and id
	* the id is given by the placement in the vector space. 
	*/
	class TextureManager
	{
	private:
		std::vector<Texture> textures;

	public:
		/**
		* Defualt construtor
		*/
		TextureManager();

		/**
		* Method reads the file. Each line must have the directory, ideally local
		* of where the texture file is located and the file name. The method reads the file
		* and adds the textures in the file. Returns false if the file or a texture failed to load,
		* returns true if it succeded.
		*/
		bool readFile(std::string fileName);

		/**
		* Method adds a texture, returns true if the file was found and it succeded, otherwise false
		*/
		bool addTexture(std::string fileName);
	};
}

#endif