/***************************************************************
 * Name:      Typing_ProofApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Christopher Wallace (cjwallacework@gmail.com)
 * Created:   2015-03-16
 * Copyright: Christopher Wallace ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "Typing_ProofApp.h"
#include "Typing_ProofMain.h"

IMPLEMENT_APP(Typing_ProofApp);

bool Typing_ProofApp::OnInit()
{
    Typing_ProofFrame* frame = new Typing_ProofFrame(0L, _("wxWidgets Application Template"));
    
    frame->Show();
    
    return true;
}
