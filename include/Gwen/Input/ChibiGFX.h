#ifndef GWEN_INPUT_CHIBIGFX_H
#define GWEN_INPUT_CHIBIGFX_H

#include "Gwen/InputHandler.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/Canvas.h"
#include <vector>

extern "C" {
    #include "ch.h"
    #include "hal.h"
    #include "gdisp_connector.h"
}

//#define DEBUG_INPUT

#ifdef DEBUG_INPUT
extern "C" {
	#include "chprintf.h"
	#include <string>
}
#endif

namespace Gwen
{
    namespace Input
    {
        class ChibiGFX
        {
          
            public:
              
                enum KB_CODES {KB_BACK = 0, KB_RETURN, KB_ESCAPE, KB_TAB, KB_SPACE, KB_UP, KB_DOWN, KB_LEFT, KB_RIGHT};
		
		ChibiGFX()
                {
			m_Canvas = NULL;
			m_MouseX = 0;
			m_MouseY = 0;
                }

                void Initialize( Gwen::Controls::Canvas* c )
                {
			m_Canvas = c;
			#if defined(GINPUT_NEED_MOUSE)
				ginputGetMouse(0);
			#endif
                }
                
                bool Touched () {
			#if defined(GINPUT_NEED_MOUSE)
				ginputGetMouseStatus(0, &ev);
				return (ev.current_buttons & GINPUT_MOUSE_BTN_LEFT);
			#else
				return false;
			#endif
                }

                bool ProcessTouch(bool touched)
                {
			#if defined(GINPUT_NEED_MOUSE)
				if ( !m_Canvas ) return false;
			
				ginputGetMouseStatus(0, &ev);

				int dx, dy;

				if (touched) {
					// Last coordinates
					dx = ev.x - m_MouseX;
					dy = ev.y - m_MouseY;

					m_MouseX = ev.x;
					m_MouseY = ev.y;
				}
				else {
					// don't move
					dx = 0;
					dy = 0;
				}
			     
				#ifdef DEBUG_INPUT
					std::string tmp("ProcessTouch [X:"+Gwen::Utility::ToString(m_MouseX)+" Y:"+Gwen::Utility::ToString(m_MouseY) \
					+" DX:"+Gwen::Utility::ToString(dx)+" DY:"+Gwen::Utility::ToString(dy)+"]\r\n");
					chprintf((BaseSequentialStream *)&DEBUG_SERIAL, tmp.c_str());	
				#endif
				if (dx>2 || dx<-2 || dy>2 || dy<-2) // 4px dead zone
					/* We send the signal that the mouse has moved, then that the primary mouse button has been pushed/released */
					m_Canvas->InputMouseMoved( m_MouseX, m_MouseY, dx, dy );

				return m_Canvas->InputMouseButton( 0, touched );
			#else
				return false;
			#endif
                }
                
                // Will be used for push buttons to keyboard key translation
                unsigned char TranslateKeyCode( unsigned char iKeyCode )
                {
			switch ( iKeyCode )
			{
				case KB_BACK:		return Gwen::Key::Backspace;
				case KB_RETURN:		return Gwen::Key::Return;
				case KB_ESCAPE:		return Gwen::Key::Escape;
				case KB_TAB:			return Gwen::Key::Tab;
				case KB_SPACE:		return Gwen::Key::Space;
				case KB_UP:			return Gwen::Key::Up;
				case KB_DOWN:		return Gwen::Key::Down;
				case KB_LEFT:		return Gwen::Key::Left;
				case KB_RIGHT:		return Gwen::Key::Right;
				default:				break;
			}
			return Gwen::Key::Invalid;
                }
		
		void AddKey(GPIO_TypeDef* Port, unsigned char Pad, unsigned char Key) {
			m_KeyList.push_back({Port, Pad, Key});
			#ifdef DEBUG_INPUT
				std::string tmp("AddKey [Key:"+Gwen::Utility::ToString(Key)+"]\r\n");
				chprintf((BaseSequentialStream *)&DEBUG_SERIAL, tmp.c_str());
			#endif
		}
                
                bool ProcessKeys() {
			bool res = false;
			for(std::vector<InputPad>::iterator iter = m_KeyList.begin(); iter != m_KeyList.end(); iter++)
			{
				if (palReadPad(iter->Port, iter->Pad)) {
					unsigned char trkey = TranslateKeyCode(iter->Key);
					#ifdef DEBUG_INPUT
						std::string tmp("ProcessKeys [Key:"+Gwen::Utility::ToString(trkey)+"]\r\n");
						chprintf((BaseSequentialStream *)&DEBUG_SERIAL, tmp.c_str());
					#endif
					// We bounce the key
					m_Canvas->InputKey( trkey, true );
					m_Canvas->InputKey( trkey, false );
					res = true;
				}
			}
			return res;
                }

                protected:
			Gwen::Controls::Canvas*	m_Canvas;
			int m_MouseX;
			int m_MouseY;
			#if defined(GINPUT_NEED_MOUSE)
				GEventMouse	ev;
			#endif
			struct InputPad {GPIO_TypeDef* Port; unsigned char Pad; unsigned char Key; };
			std::vector<InputPad> m_KeyList;
        };
    }
}
#endif

