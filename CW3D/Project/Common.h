#pragma once

#include	<iostream>
#include	<iomanip>
#include	<string>
#include	<random>
#include	<vector>
#include	<queue>
#include	<list>
#include	<map>
#include	<unordered_map>
#include	<tuple>
#include	<type_traits>
#include	<memory>
#include	<filesystem>
#include	<fstream>
#include	<sstream>
#include	<cmath>
#include	<cassert>
#include	<cstdarg>
#include	<algorithm>
#include	<functional>
#include	<utility>
#include	<thread>
#include	<mutex>
#include	<any>





#define		__MOFLIB
#ifdef 		__MOFLIB
#include	<Mof.h>
#endif		//__MOFLIB

// Effekseerä÷òAÇÃëgÇ›çûÇ›
#include	<Effekseer.h>
#include	<EffekseerRendererDX11.h>
#include	<EffekseerSoundXAudio2.h>
#ifdef DEBUG
#pragma comment(lib, "Effekseerd.lib")
#pragma comment(lib, "EffekseerRendererDX11d.lib")
#pragma comment(lib, "EffekseerSoundXAudio2d.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#pragma comment(lib, "EffekseerSoundXAudio2.lib")
#endif // DEBUG