// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <chrono>

enum
{
    ID_Hello = 1,
    ID_CLOCK_TIMER,
};

class PomodoroFrame : public wxFrame
{
public:
    PomodoroFrame();

private:

    void OnHello(wxCommandEvent &event);

    void OnExit(wxCommandEvent &event);

    void OnAbout(wxCommandEvent &event);

    void OnUpdateClock(wxTimerEvent &event);

    wxTimeSpan m_timer_remaining{0, 0, 10};
    wxTimer m_clock_timer;
    wxStaticText *m_clock_text = nullptr;
};