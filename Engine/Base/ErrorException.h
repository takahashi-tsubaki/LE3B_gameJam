#pragma once
#pragma warning(push)
#pragma warning(disable: 4265)
#pragma warning(disable: 4324)
#pragma warning(disable: 4365)
#pragma warning(disable: 4625)
#pragma warning(disable: 4626)
#pragma warning(disable: 4668)
#pragma warning(disable: 4717)
#pragma warning(disable: 4820)
#pragma warning(disable: 5039)
#pragma warning(disable: 5204)
#pragma warning(disable: 5220)
#pragma warning(disable: 26812)
#pragma warning(disable: 5246)

#include<array>
#include<cassert>
#include<cmath>
#include<cstdint>
#include<d3d12.h>
#include<d3dcompiler.h>
#define DIRECTINPUT_VERSION 0x0800	//DirectInputのバージョン指定
#include<dinput.h>
#include<DirectXMath.h>
#include<DirectXTex.h>
#include<dxgi1_6.h>
#include<dxgidebug.h>
#include<filesystem>
#include<forward_list>
#include<fstream>
#include<iterator>
#include<memory>
#include<mmsystem.h>
#include<sstream>
#include<string>
#include<tchar.h>
#include<mfapi.h>
#include<mfidl.h>
#include<mfreadwrite.h>
#include<unordered_map>
#include<vector>
#include<xaudio2.h>
#include<Windows.h>
#include<wrl.h>
#pragma warning(pop)

using namespace DirectX;
using namespace Microsoft::WRL;

//リンクの設定
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")//directInputのバージョン
#pragma comment(lib,"dxguid.lib")
