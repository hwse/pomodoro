#include "PomodoroConfig.hpp"

#include <stdexcept>

namespace
{

std::string to_string(PomodoroState::Type type)
{
    switch (type)
    {
        case PomodoroState::Type::WORKING:
            return "WORKING";
        case PomodoroState::Type::BREAK:
            return "BREAK";
        default:
            return "UNKNOWN";
    }
}

}

PomodoroConfig::PomodoroConfig()
        : m_config(wxConfigBase::Get(true))
{
    if (m_config == nullptr)
    {
        throw std::runtime_error{"wxConfigBase::Get returned nullptr"};
    }
    m_config->SetAppName("pomodoro");
    m_config->SetVendorName("pomodoro");
    m_config->Write("test", "value1");
}

std::vector<PomodoroState> PomodoroConfig::get_states()
{
    std::vector<PomodoroState> result;

    m_config->SetPath("/states");

    const size_t states_count = m_config->GetNumberOfGroups();
    result.reserve(states_count);

    for (size_t i = 0; i < states_count; ++i)
    {
        PomodoroState state;
        const wxString type = m_config->Read(std::to_string(i) + "/type", "");
        if (type == "WORKING")
        {
            state.type = PomodoroState::Type::WORKING;
        } else if (type == "BREAK")
        {
            state.type = PomodoroState::Type::BREAK;
        } else
        {
            continue;
        }
        wxLongLong_t duration = m_config->ReadLongLong(std::to_string(i) + "/duration", 0);
        if (duration == 0)
        {
            continue;
        }
        state.duration = wxTimeSpan{wxLongLong{duration}};
        result.push_back(state);
    }

    m_config->SetPath("/");
    return result;
}

void PomodoroConfig::set_states(const std::vector<PomodoroState> &states)
{
    m_config->SetPath("/");
    m_config->DeleteGroup("states");

    size_t index = 0;
    for (const auto &state: states)
    {
        const wxString state_key = "/states/" + std::to_string(index);

        const wxString type_key = state_key + "/type";
        const wxString type_value = to_string(state.type);
        m_config->Write(type_key, type_value);


        const wxString duration_key = state_key + "/duration";
        const wxLongLong_t duration_value = state.duration.GetValue().GetValue();
        m_config->Write(duration_key, duration_value);

        index++;
    }
    m_config->SetPath("/");
    m_config->Flush();
}
