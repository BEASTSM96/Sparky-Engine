/********************************************************************************************
*                                                                                           *
*                                                                                           *
*                                                                                           *
* MIT License                                                                               *
*                                                                                           *
* Copyright (c) 2020 - 2021 BEAST                                                           *
*                                                                                           *
* Permission is hereby granted, free of charge, to any person obtaining a copy              *
* of this software and associated documentation files (the "Software"), to deal             *
* in the Software without restriction, including without limitation the rights              *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                 *
* copies of the Software, and to permit persons to whom the Software is                     *
* furnished to do so, subject to the following conditions:                                  *
*                                                                                           *
* The above copyright notice and this permission notice shall be included in all            *
* copies or substantial portions of the Software.                                           *
*                                                                                           *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                  *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE               *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                    *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,             *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE             *
* SOFTWARE.                                                                                 *
*********************************************************************************************
*/

#pragma once

#include <memory>
#include "Ref.h"

#pragma warning(push, 0)

namespace Saturn {
	void InitCore( void );
	void EndCore( void );
}

#if (__cplusplus >= 201402L)
#error C++ 14 is not supported
#else

#include "PlatformDetection.h"

#define DISABLE_ALL_WARNINGS_BEGIN
#define DISABLE_ALL_WARNINGS_END

//from the vc++
#define SAT_MoveMemory( Destination, Source, Length ) memmove( ( Destination ), ( Source ), ( Length ) )
#define SAT_CopyMemory( Destination, Source, Length ) memcpy( ( Destination ), ( Source ), ( Length ) )
#define SAT_FillMemory( Destination, Length, Fill ) memset( ( Destination ), ( Fill ), ( Length ) )
#define SAT_ZeroMemory( Destination, Length ) memset( ( Destination ), 0, ( Length ) )

#define SAT_FILEOPENNAMEA OPENFILENAMEA
#define SAT_FILEOPENNAME OPENFILENAME

#define GAMEFRAMEWORK_API

/*Can be used for macros just core*/
#define _VA_AGRS_(x) x

#define BIT(x) (1 << x)

#define SAT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef SAT_DEBUG
#if defined(SAT_PLATFORM_WINDOWS)
#define SAT_DEBUGBREAK() __debugbreak()
#elif defined(SAT_PLATFORM_LINUX)
#include <signal.h>
#define SAT_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define SAT_ENABLE_ASSERTS
#else
#define SAT_DEBUGBREAK()
#endif

#include "Asserts.h"

#include "Types.h"

#define PHYSX
#ifdef PHYSX
#define USE_NVIDIA
#endif // PHYSX

#define HOTRELOADS(name) struct name {

namespace Saturn {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using RefSR = std::shared_ptr<T>;

	using byte = uint8_t;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr RefSR<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#endif

#pragma warning(pop)