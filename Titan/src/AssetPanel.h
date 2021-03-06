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

#include <Saturn/Layer.h> 
#include <Saturn/Core/Ray.h>
#include <Saturn/Core/Ref.h>

#include <vector>

namespace Saturn {

	class AssetPanel : public Layer, public RefCounted
	{
	public:
		AssetPanel( void );
		~AssetPanel( void );
	public:
		virtual void OnAttach( void ) override;
		virtual void OnDetach( void ) override;
		virtual void OnImGuiRender() override;
		bool CheckHasAsset( std::string name, std::string filepath, std::string folder );
		virtual void OnUpdate( Timestep ts ) override;
		virtual void OnEvent( Event& e ) override;

		bool OnMouseButtonPressed( MouseButtonEvent& e );
		bool OnKeyPressedEvent( KeyPressedEvent& e );
	public:

	protected:
		Ref<Texture2D> m_CheckerboardTex;

		std::vector<std::string> m_Assets;
		std::vector<std::string> m_AssetsFolderContents;
	private:
	};
}