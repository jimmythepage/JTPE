#ifndef JCOMMONPCH
#define JCOMMONPCH

//BOOTING DEFINES
#define __SDL__
//#define __BUILDJGAME__
//#define __PUBLISHJGAME__

//#define __STEAM__

//COMMON LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <fstream>
#include <string>
#include <map>
#include <bitset>
#include <vector>
#include <chrono>
#include <exception>
#include <functional>
#include <random>
#include <winsock2.h>

//EXT LIBRARY
#include "JBase/json.hpp"
using json = nlohmann::json;

#if defined(__SDL__)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <SDL_syswm.h>
#include <SDL_render.h>
#include <SDL_audio.h>
#endif
//FFMPEG
extern "C"
{
#include <ffmpeg/include/libavcodec/avcodec.h>
#include <ffmpeg/include/libavdevice/avdevice.h>
#include <ffmpeg/include/libavfilter/avfilter.h>
#include <ffmpeg/include/libavformat/avformat.h>
#include <ffmpeg/include/libavformat/avio.h>
#include <ffmpeg/include/libavutil/avutil.h>
#include <ffmpeg/include/libpostproc/postprocess.h>
#include <ffmpeg/include/libswresample/swresample.h>
#include <ffmpeg/include/libswscale/swscale.h>
#include <ffmpeg/include/libavutil/frame.h>
#include <ffmpeg/include/libavutil/imgutils.h>
}
//FFMPEG PLAYER
#include "ffmpeg/VideoPlayer/defs.h"

//JBASE
#include "JBase/JBaseDefines.h"
#include "JInput/JInputDefines.h"
#include "JRender/JRenderDefines.h"
#include "JBase/iJBase.h"
#include "JBase/JBase.h"
#include "JBase/JObject.h"
#include "JTask/JTask.h"
#include "JBase/JTimer.h"
#include "JBase/JFile.h"
#include "JBase/JTextDB.h"
#include "JInput/JInput_Keyboard.h"
#include "JInput/JInput_Pointer.h"
//JTWEEN
#include "JTween/JBaseTween.h"
#include "JTween/JFloatTween.h"
//JRENDER
#include "JRender/JRenderable.h"
#include "JRender/JRenderer.h"
#include "JRender/JSprite.h"
#include "JRender/JVideoSprite.h"
#include "JRender/JText.h"
//JGame
#include "JGame/JGameDefines.h"
#include "JGame/JGameElement.h"
#include "JGame/JGameCamera.h"
#include "JGame/JGameText.h"
#include "JGame/JGameSprite.h"
#include "JGame/JGameVideoSprite.h"
#include "JGame/JGameButton.h"
#include "JGame/JGameModule.h"
#include "JGame/JGameDraggable.h"
#include "JGame/JGameScreen.h"
#include "JGame/JGameLevel.h"
//JPhysics
#include "JPhysics/JPhysics.h"
#include "JPhysics/JBody.h"
#include "JPhysics/JPhysicObject.h"

//JMANAGERS
#include "JEngine.h"
#include "JRender/JRenderManager.h"
#include "JInput/JInputManager.h"
#include "JBase/JFileManager.h"
#include "JBase/JSavingSystem.h"
#include "JGame/JGameManager.h"
#include "JNet/JNetManager.h"
#include "JPhysics/JPhysicsManager.h"


#ifdef __WINDOWS__
#include <SDKDDKVer.h>

#include "JInput/Windows/JInput_Keyboard_Win.h"
#include "JInput/Windows/JInputPointer_Win.h"

#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	#if defined(__SDL__)
	#include "JRender/JSDL/JRendererSDL.h"
	#include "JRender/JSDL/JTextureManagerSDL.h"
	#include "JRender/JSDL/JSpriteSDL.h"
	#include "JRender/JSDL/JVideoSpriteSDL.h"
	#include "JRender/JSDL/JTextSDL.h"
	#endif
#endif

#ifdef __STEAM__
#include "3rdParties/Steam/public/steam/steam_api.h"
#ifdef STEAM_CEG
// Steam DRM header file
#include "cegclient.h"
#else
#define Steamworks_InitCEGLibrary() (true)
#define Steamworks_TermCEGLibrary()
#define Steamworks_TestSecret()
#define Steamworks_SelfCheck()
#endif
#endif 

#endif // !JCOMMONPCH
