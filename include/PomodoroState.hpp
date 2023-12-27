#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <variant>
#include <vector>

enum class PomodoroState
{
    WORKING,
    BREAK,
    LONG_BREAK
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
    void reset();
private:
    PomodoroState next_state() const;

    PomodoroState m_current_state{PomodoroState::WORKING};
    size_t m_work_block = 0;
    wxTimeSpan m_remaining_time{0, 0, 30};
};