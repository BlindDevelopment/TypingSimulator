/***************************************************************
 * Name:      Typing_ProofMain.cpp
 * Purpose:   Code for Application Frame
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

#include "Typing_ProofMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(Typing_ProofFrame, wxFrame)
    EVT_CLOSE(Typing_ProofFrame::OnClose)
    EVT_MENU(idMenuQuit, Typing_ProofFrame::OnQuit)
    EVT_MENU(idMenuAbout, Typing_ProofFrame::OnAbout)
    EVT_TIMER(idTimerLetter,Typing_ProofFrame::OnLetter)
END_EVENT_TABLE()

Typing_ProofFrame::Typing_ProofFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    console = new wxTextCtrl(this,-1,_T(""),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE|wxTE_READONLY);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    console->SetDefaultStyle(wxTextAttr(*wxWHITE,*wxBLACK,wxFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false)));
    console->SetBackgroundColour(*wxBLACK);
    sizer->Add(console,1,wxEXPAND,0);
    SetSizer(sizer);
    letterTimer = new wxTimer(this,idTimerLetter);
    lettersLeft = _T("Hello world! How are you today? I'm Chris! Let's see if we can type this like a real person.");
    lettersDone = _T("");
    numCorrect = 0;
    numMistakes = 0;
    numBackspace = 0;
    numRepeats = 0;
    srand(time(0));
    letterTimer->Start(666,true);



}


Typing_ProofFrame::~Typing_ProofFrame()
{
}

void Typing_ProofFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void Typing_ProofFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void Typing_ProofFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void Typing_ProofFrame::OnLetter(wxTimerEvent &event)
{
    int backspaceChance = rand()%100+1;
    if (numMistakes > 0 && numBackspace < 1 && backspaceChance > (0-(numMistakes*10)) && numCorrect == 0)
    {
        numBackspace = numMistakes + numRepeats;
        numCorrect = numBackspace + rand()%5;
        int totalRetypes = numMistakes;
        wxString newletters = lettersDone.Mid(lettersDone.length()-totalRetypes);
        newletters<<lettersLeft;
        wxMessageDialog *dlg = new wxMessageDialog(this,newletters,lettersLeft,wxOK);
        //dlg->ShowModal();
        lettersLeft = newletters;
    }

    if (numBackspace > 0)
    {
        wxString temp = console->GetValue();
        temp = temp.RemoveLast();
        console->Clear();
        console->AppendText(temp);
        numBackspace-=1;
        letterTimer->Start(110,true);
    }
    else if (lettersLeft.length() > 0)
    {
        lettersDone<<lettersLeft.Mid(0,1);
        int screwupChange = rand()%100+1;
        if ((screwupChange > 95-((numMistakes)*15)) && (numCorrect == 0) && (numMistakes < 5))
        {
            Mistake(lettersLeft.Mid(0,1));
            numMistakes++;
        }
        else
        {
            if (numCorrect > 0)
            {
                numCorrect -= 1;
            }
            numRepeats = 0;
            numMistakes = 0;
            console->AppendText(lettersLeft.Mid(0,1));
            lettersLeft = lettersLeft.Mid(1);
        }
        letterTimer->Start(110,true);
    }
}

void Typing_ProofFrame::Mistake(wxString c)
{
    int extraLetter = rand()%100+1;
    if (extraLetter > (100-((numMistakes+1)*25)))
    {
        numRepeats++;
        console->AppendText(c);
        lettersLeft = lettersLeft.Mid(1);
        if (false)
        {

        }
        else
        {

        }
    }
    else
    {
        c = _T("~");
        lettersLeft = lettersLeft.Mid(1);
    }


    console->AppendText(c);
}
