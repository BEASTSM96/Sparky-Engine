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

#include "sppch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>

#include "ImGui/ImGuiConsoleSink.h"

namespace Saturn {

	std::shared_ptr< spdlog::logger > Log::s_CoreLogger;
	std::shared_ptr< spdlog::logger > Log::s_ClientLogger;

	void Log::Init( void )
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back( std::make_shared< spdlog::sinks::stdout_color_sink_mt >() );
		logSinks.emplace_back( std::make_shared< spdlog::sinks::basic_file_sink_mt >( "Saturn.log", true ) );
		logSinks.emplace_back( std::make_shared< ImGuiConsoleSink_mt >( true ) );

		logSinks[ 0 ]->set_pattern( "%^[%T] %n: %v%$" );
		logSinks[ 1 ]->set_pattern( "[%T] [%l] %n: %v" );
		logSinks[ 2 ]->set_pattern( "%^[%T] [%l] %n: %v%$" );

		s_CoreLogger = std::make_shared< spdlog::logger >( "SATURN", begin( logSinks ), end( logSinks ) );
		spdlog::register_logger( s_CoreLogger );

		s_ClientLogger = std::make_shared< spdlog::logger >( "APP", begin( logSinks ), end( logSinks ) );
		spdlog::register_logger( s_ClientLogger );

		// configure the loggers
		spdlog::set_pattern( "%^[%T] %n: %v%$" );
		s_CoreLogger->set_level( spdlog::level::trace );
		s_ClientLogger->set_level( spdlog::level::trace );
		//s_ClientLogger->flush_on(spdlog::level::trace);
		//s_CoreLogger->flush_on(spdlog::level::trace);
	}

}