//!XDL_ContentManager
/*!
A content manager for loading assets into your game, and keeping track of currently loaded assets
Currently supports all types of Image files.
*/

#ifndef _CONTENT_MANAGER
#define _CONTENT_MANAGER

#include <SDL.h>
#include <stdlib.h>
#include <iostream>
#include <map>
using namespace std;
#include <SDL_image.h>
class XDL_ContentManager
{
public:
	XDL_ContentManager(void);
	~XDL_ContentManager(void);

	 /*!
	\return Pointer to XDL_ContentManager Instance.Creates a new ContentManager if none exist.
	*/
	static XDL_ContentManager* GetInstance(); 

	/*!< Depricated */ 
	 /*!
	\sa LoadSprite(char* _path,SDL_Renderer* _renderer)
	 */
	SDL_Texture* LoadBMP(char* _path,SDL_Renderer* _renderer);

	 /*!
	\return Pointer to an SDL_Texture holding our sprite
	\param _path Path to the sprite
	\param _renderer Pointer to the current draw surface
	 */
	//! LoadSprite.
	/*!
	Loads a sprite into memory.If it is already in memory, it will return a pointer to the loaded asset.If its the first time loading, it will store it in a map for future use.
	*/
	SDL_Texture* LoadSprite(char* _path,SDL_Renderer* _renderer);
private:
	static XDL_ContentManager* _me;/*!< Pointer to our Instance */ 

	std::map<char*,SDL_Texture*> _dictionary;/*!<Map to hold all our sprites*/ 

};


#endif
