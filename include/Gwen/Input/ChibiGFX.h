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
    #include "touchpad.h"
}

namespace Gwen
{
    namespace Input
    {
        class ChibiGFX
        {
          
            public:
              
                enum KB_CODES {KB_BACK = 0, KB_RETURN, KB_ESCAPE, KB_TAB, KB_SPACE, KB_UP, KB_DOWN, KB_LEFT, KB_RIGHT};

                ChibiGFX() : m_Spicfg({NULL, TP_CS_PORT, TP_CS, SPI_CR1_BR_1 | SPI_CR1_BR_0}), m_Touchpad({&TP_SPI, &m_Spicfg, TP_IRQ_PORT, TP_IRQ, TRUE})
                {
                    m_Canvas = NULL;
                    m_MouseX = 0;
                    m_MouseY = 0;
                }

                void Initialize( Gwen::Controls::Canvas* c )
                {
                   m_Canvas = c;
                   tpInit(&m_Touchpad);
                   tpCalibrate();
                }
                
                bool Touched () {
                  return tpIRQ();
                }

                bool ProcessTouch(bool touched)
                {
                    if ( !m_Canvas ) return false;
                  
                    // Current coordinates
                    int x = ((float)SCREEN_WIDTH-((float)tpReadX()*2.0f))*TP_W_FIX;
                    int y = ((float)tpReadY()/2.0f)*TP_H_FIX;
                  
                    // Last coordinates
                    int dx = x - m_MouseX;
                    int dy = x - m_MouseY;

                    m_MouseX = x;
                    m_MouseY = y;

                   /* We send the signal that the mouse has moved, then that the primary mouse button has been pushed/released */
                    m_Canvas->InputMouseMoved( m_MouseX, m_MouseY, dx, dy );
		    return m_Canvas->InputMouseButton( 1, touched );
                }
                
                // Will be used for push buttons to keyboard key translation
                unsigned char TranslateKeyCode( int iKeyCode )
                {
			switch ( iKeyCode )
			{
				case KB_BACK:			return Gwen::Key::Backspace;
				case KB_RETURN:		return Gwen::Key::Return;
				case KB_ESCAPE:		return Gwen::Key::Escape;
				case KB_TAB:			return Gwen::Key::Tab;
				case KB_SPACE:		return Gwen::Key::Space;
				case KB_UP:			return Gwen::Key::Up;
				case KB_DOWN:			return Gwen::Key::Down;
				case KB_LEFT:			return Gwen::Key::Left;
				case KB_RIGHT:		return Gwen::Key::Right;
				default:
				break;
			}

			return Gwen::Key::Invalid;
                }
		
		void AddKey(int Port, int Pad, int Key) {
			m_KeyList.push_back({Port, Pad, Key});
		}
                
                void ProcessKeys() {
			for(std::vector<InputPad>::iterator iter = m_KeyList.begin(); iter != m_KeyList.end(); iter++)
			{/* TODO
				if (palReadPad(&iter->Port, &iter->Pad)) {
					int trkey = TranslateKeyCode(&iter->Key);
					// We bounce the key
					m_Canvas->InputKey( trkey, true );
					m_Canvas->InputKey( trkey, false );
				} */
			}
                }

                protected:
			Gwen::Controls::Canvas*	m_Canvas;
			int m_MouseX;
			int m_MouseY;
			const TOUCHPADDriver m_Touchpad;
			const SPIConfig m_Spicfg;
			struct InputPad {int Port; int Pad;	int Key; };
			std::vector<InputPad> m_KeyList;
        };
    }
}
#endif
