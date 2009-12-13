#pragma once
#include "guichan/platform.hpp"
#include "guichan/widgets/button.hpp"
#include "guichan/sdl/sdlimageloader.hpp"
#include "guichan/sdl/sdlimage.hpp"


namespace gcn
{
	class Image;

	//Èý×´Ì¬°´Å¥
	class GCN_CORE_DECLSPEC StatuButton : public gcn::Button
	{
	public:
		StatuButton();
		~StatuButton();

		void setNormalImage( const std::string& imgname );
		void setHoverImage( const std::string& imgname );
		void setPushedImage( const std::string& imgname );

		void draw(gcn::Graphics* graphics);

	protected:
		const Image* m_NormalImage;
		const Image* m_HoverImage;
		const Image* m_PushedImage;

		SDLImageLoader m_imgLoader;

	};

}
