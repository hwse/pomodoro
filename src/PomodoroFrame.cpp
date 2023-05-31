#include "PomodoroFrame.hpp"
#include <wx/notifmsg.h>

namespace
{
const wxSize WINDOW_SIZE = {300, 100};
const wxTimeSpan CLOCK_INTERVAL{0, 0, 1};
}

PomodoroFrame::PomodoroFrame()
        : wxFrame(nullptr, wxID_ANY, "Pomodoro Timer")
{

    auto *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    auto *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    auto *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    {
        sizer->SetMinSize(WINDOW_SIZE);

        m_clock_text = new wxStaticText(this, 41, m_timer_remaining.Format());
        m_clock_text->SetFont(m_clock_text->GetFont().Scale(3.0));
        sizer->Add(m_clock_text, 1, wxALIGN_CENTER_HORIZONTAL, 10);

        auto *button = new wxButton(this, 42, "start/stop");
        sizer->Add(button, 1, wxEXPAND | wxALL, 10);
    }
    SetSizerAndFit(sizer);

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Work on the task!");

    m_clock_timer.Bind(wxEVT_TIMER, &PomodoroFrame::OnUpdateClock, this);
    m_clock_timer.Start(CLOCK_INTERVAL.GetMilliseconds().ToLong());

    Bind(wxEVT_MENU, &PomodoroFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &PomodoroFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &PomodoroFrame::OnExit, this, wxID_EXIT);
}

void PomodoroFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void PomodoroFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void PomodoroFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void PomodoroFrame::OnUpdateClock(wxTimerEvent &event)
{
    m_timer_remaining -= CLOCK_INTERVAL;
    if (m_timer_remaining <= wxTimeSpan{0})
    {
        auto notification = new wxNotificationMessage{"ping", "time is over", this};
        notification->Show();
    }
    if (m_clock_text != nullptr)
    {
        m_clock_text->SetLabel(m_timer_remaining.Format());
    }
}
