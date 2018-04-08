/***************************************************************
 * Name:      SaperApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Arkadiusz Gajda,Daniel Jedrzejczyk ()
 * Created:   2017-12-29
 * Copyright: Arkadiusz Gajda,Daniel Jedrzejczyk ()
 * License:
 **************************************************************/

#include "SaperApp.h"

//(*AppHeaders
#include "SaperMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SaperApp);

bool SaperApp::OnInit()
{

    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {

    	SaperFrame *Frame = new SaperFrame(0);
    	Frame->Show();

        Frame->SetIcon(wxICON(ikona_s));


        Frame->SetSizeHints(445,469,445,469);
    	Frame->SetTitle("Saper");
    	SetTopWindow(Frame);
    	Frame->Refresh();
    }

    return wxsOK;

}
