/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_DRAGANDDROP_H
#define GWEN_DRAGANDDROP_H

#include "Gwen/Skin.h"
#include "Gwen/Structures.h"
#include <sstream>
#include <string>

namespace Gwen
{
	namespace DragAndDrop
	{
		extern  Package*	CurrentPackage;
		extern  Gwen::Controls::Base*	SourceControl;
		extern  Gwen::Controls::Base*	HoveredControl;

		bool  Start( Gwen::Controls::Base* pControl, Package* pPackage );

		bool  OnMouseButton( Gwen::Controls::Base* pHoveredControl, int x, int y, bool bDown );
		void  OnMouseMoved( Gwen::Controls::Base* pHoveredControl, int x, int y );

		void  RenderOverlay( Gwen::Controls::Canvas* pCanvas, Skin::Base* skin );

		void  ControlDeleted( Gwen::Controls::Base* pControl );
	}

}
#endif

