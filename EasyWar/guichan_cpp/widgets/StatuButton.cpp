#include "stdafx.h"
#include "guichan/widgets/StatuButton.h"

namespace gcn
{
	StatuButton::StatuButton()
	{
		setWidth(0);
		setHeight(0);

		m_NormalImage = NULL;
		m_HoverImage = NULL;
		m_PushedImage = NULL;
	}

	StatuButton::~StatuButton()
	{
		if( m_HoverImage )
		{
			delete m_HoverImage;
		}
		if( m_HoverImage )
		{
			delete m_HoverImage;
		}
		if( m_PushedImage )
		{
			delete m_PushedImage;
		}
	}

	void StatuButton::draw( Graphics* graphics )
	{
		const int textX = (getWidth() - (m_NormalImage ? m_NormalImage->getWidth() : 0) ) / 2;
		const int textY = (getHeight() - (m_NormalImage ? m_NormalImage->getHeight() : 0) ) / 2;

		if( mHasMouse )
		{
			if( isPressed() )
			{
				if( m_PushedImage )
				{
					graphics->drawImage( m_PushedImage, textX, textY );
				}
			}else
			{
				if( m_HoverImage )
				{
					graphics->drawImage( m_HoverImage, textX, textY );
				}
			}
		}else
		{
			if( m_NormalImage )
			{
				graphics->drawImage( m_NormalImage, textX, textY );
			}
		}
	}

	void StatuButton::setNormalImage( const std::string& imgname )
	{
		if( m_NormalImage )
		{
			delete m_NormalImage;
		}

		SDLImage* img = new SDLImage( NULL, true );
		img->setImageLoader( &m_imgLoader );
		m_NormalImage = img->load( imgname );
		delete img;
	}

	void StatuButton::setHoverImage( const std::string& imgname )
	{
		if( m_HoverImage )
		{
			delete m_HoverImage;
		}

		SDLImage* img = new SDLImage( NULL, true );
		img->setImageLoader( &m_imgLoader );
		m_HoverImage = img->load( imgname );
		delete img;
	}

	void StatuButton::setPushedImage( const std::string& imgname )
	{
		if( m_PushedImage )
		{
			delete m_PushedImage;
		}

		SDLImage* img = new SDLImage( NULL, true );
		img->setImageLoader( &m_imgLoader );
		m_PushedImage = img->load( imgname );
		delete img;
	}


}
