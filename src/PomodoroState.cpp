#include "PomodoroState.hpp"

#include <utility>

namespace
{

const wxTimeSpan ZERO_TIME_SPAN{0};

template<typename T>
T pop_front(std::queue<T> &queue)
{
    if (queue.empty())
    {
        throw std::out_of_range("can not pop first element of a empty queue");
    }
    T result = std::move(queue.front());
    queue.pop();
    return result;
}

}


PomodoroStateTracker::PomodoroStateTracker(std::vector<PomodoroState> states)
        : m_states(std::move(states))
{
    if (m_states.empty())
    {
        throw std::logic_error{"states must not be empty"};
    }
    m_current_state = next_state();
}


std::vector<PomodoroEvent> PomodoroStateTracker::update_state(wxTimeSpan time_passed)
{
    std::vector<PomodoroEvent> result;

    m_current_state.duration -= time_passed;
    result.emplace_back(PomodoroUpdateRemainingTime{m_current_state.duration});
    if (m_current_state.duration <= ZERO_TIME_SPAN)
    {
        m_current_state = next_state();
        result.emplace_back(PomodoroStateChange{m_current_state});
    }
    return result;
}

void PomodoroStateTracker::reset()
{
}

PomodoroState PomodoroStateTracker::next_state()
{
    if (m_upcoming_states.empty())
    {
        for (const auto &state: m_states)
        {
            m_upcoming_states.push(state);
        }
    }
    return pop_front(m_upcoming_states);
}