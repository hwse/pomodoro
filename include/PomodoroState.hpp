#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <variant>
#include <vector>
#include <queue>

struct PomodoroState
{
    enum class Type
    {
        WORKING,
        BREAK,
    };

    Type type = Type::WORKING;
    wxTimeSpan duration{};
};

struct PomodoroStateChange
{
    PomodoroState new_state{};
};

struct PomodoroUpdateRemainingTime
{
    wxTimeSpan remaining_time{};
};

using PomodoroEvent = std::variant<
        PomodoroUpdateRemainingTime,
        PomodoroStateChange>;

class PomodoroStateTracker
{
public:
    std::vector<PomodoroEvent> update_state(wxTimeSpan time_passed);

    void set_states(std::vector<PomodoroState> states);

private:
    PomodoroState next_state();

    std::vector<PomodoroState> m_states{};
    PomodoroState m_current_state{};
    std::queue<PomodoroState> m_upcoming_states;
};