#pragma once

#include <wx/config.h>

#include <PomodoroState.hpp>

class PomodoroConfig
{
public:
    PomodoroConfig();

    std::vector<PomodoroState> get_states();

    void set_states(const std::vector<PomodoroState> &states);

private:
    wxConfigBase *m_config = nullptr;
};