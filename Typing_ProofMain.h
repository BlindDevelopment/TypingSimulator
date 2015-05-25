/***************************************************************
 * Name:      Typing_ProofMain.h
 * Purpose:   Defines Application Frame
 * Author:    Christopher Wallace (cjwallacework@gmail.com)
 * Created:   2015-03-16
 * Copyright: Christopher Wallace ()
 * License:
 **************************************************************/

#ifndef TYPING_PROOFMAIN_H
#define TYPING_PROOFMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/textctrl.h>
    #include <wx/timer.h>
#endif

#include "Typing_ProofApp.h"

class Typing_ProofFrame: public wxFrame
{
    public:
        Typing_ProofFrame(wxFrame *frame, const wxString& title);
        ~Typing_ProofFrame();
    private:
        int numMistakes;
        int numCorrect;
        int numRepeats;
        int numBackspace;
        wxTextCtrl *console;
        void OnLetter(wxTimerEvent &event);
        void Mistake(wxString c);
        wxTimer *letterTimer;
        wxString lettersLeft;
        wxString lettersDone;
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            idTimerLetter,
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // TYPING_PROOFMAIN_H
