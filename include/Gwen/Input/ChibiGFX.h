#ifndef GWEN_INPUT_CHIBIGFX_H
#define GWEN_INPUT_CHIBIGFX_H

#include "Gwen/InputHandler.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/Canvas.h"

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

                bool ProcessTouch()
                {
                    if ( !m_Canvas ) return false;
                  
                    // Current coordinates
                    int x = tpReadX();
                    int y = tpReadY();
                  
                    // Last coordinates
                    int dx = x - m_MouseX;
                    int dy = x - m_MouseY;

                    m_MouseX = x;
                    m_MouseY = y;

                   /* We send the signal that the mouse has moved, then that the primary mouse button has been pushed */
                    m_Canvas->InputMouseMoved( m_MouseX, m_MouseY, dx, dy );
                    return m_Canvas->InputMouseButton( 1, true );
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
                
                bool KeyPressed() {
                  
                  // Check the pins that will be somewhere in a list
                  
                  return false;
                }
                
                bool ProcessKey(int key) {
                  
                    int trkey = TranslateKeyCode(key);
                    // We bounce the key
                    m_Canvas->InputKey( trkey, true );
                    return m_Canvas->InputKey( trkey, false );
                }

                protected:
                    Gwen::Controls::Canvas*	m_Canvas;
                    int m_MouseX;
                    int m_MouseY;
                    const TOUCHPADDriver m_Touchpad;
                    const SPIConfig m_Spicfg;
        };
    }
}
#endif

