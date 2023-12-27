#include "PomodoroState.hpp"

namespace
{
constexpr size_t LONG_BREAK_AFTER_N_BLOCKS = 4;
const wxTimeSpan ZERO_TIME_SPAN{0};
const wxTimeSpan WORK_TIME{0, 0, 30};
const wxTimeSpan BREAK_TIME{0, 0, 5};
const wxTimeSpan LONG_BREAK_TIME{0, 0, 10};

wxTimeSpan new_state_time(PomodoroState state)
{
    switch (state)
    {
        case PomodoroState::WORKING:
            return WORK_TIME;
        case PomodoroState::BREAK:
            return BREAK_TIME;
        case PomodoroState::LONG_BREAK:
            return LONG_BREAK_TIME;
        default:
            throw std::runtime_error("Unknown PomodoroState: " + std::to_string(static_cast<int>(state)));
    }
}

}

std::vector<PomodoroEvent> PomodoroStateTracker::update_state(wxTimeSpan time_passed)
{
    std::vector<PomodoroEvent> result;

    m_remaining_time -= time_passed;
    result.emplace_back(PomodoroUpdateRemainingTime{m_remaining_time});
    if (m_remaining_time <= ZERO_TIME_SPAN)
    {
        m_current_state = next_state();
        switch (m_current_state)
        {
            case PomodoroState::WORKING:
            {
                m_work_block += 1;
                break;
            }
            case PomodoroState::LONG_BREAK:
            {
                m_work_block = 0;
                break;
            }
            default:
                break;
        }
        result.emplace_back(PomodoroStateChange{m_current_state});
        m_remaining_time = new_state_time(m_current_state);
        result.emplace_back(PomodoroUpdateRemainingTime{m_remaining_time});
    }

    return result;
}

void PomodoroStateTracker::reset()
{
}

PomodoroState PomodoroStateTracker::next_state() const
{
    if (m_current_state == PomodoroState::WORKING)
    {
        if (m_work_block >= LONG_BREAK_AFTER_N_BLOCKS)
        {
            return PomodoroState::LONG_BREAK;
        }
        else
        {
            return PomodoroState::BREAK;
        }
    }
    else
    {
        return PomodoroState::WORKING;
    }

}
