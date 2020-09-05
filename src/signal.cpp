#include "header/signal.h"
#include <vector>

SignalManager* SignalManager::instance(NULL);

void SignalManager::emit(const std::pair<Object*, std::string> & signal, bool persist)
{
    instance->m_sig_names[signal] = 0;
    if (persist)
        instance->m_persistant_list[signal.second] = true;
}

bool SignalManager::emitted(const std::string& sig_name, Object* source)
{
    if (source)
        return instance->m_sig_names[std::pair<Object*, std::string>(source, sig_name)];
    bool ret(false);
    for (auto pair : instance->m_sig_names)
        if (pair.first.second == sig_name)
            ret |= pair.second;
    return ret;
}

void SignalManager::treat(const std::string& sig_name, Object* source)
{
    if (source)
        instance->m_sig_names.erase(std::pair<Object*, std::string>(source, sig_name));
    else
    {
        std::vector< std::pair<Object*, std::string> > keys;
        for (auto pair : instance->m_sig_names)
            if (pair.first.second == sig_name)
            {
                keys.push_back(pair.first);
            }
        for (auto key : keys)
            instance->m_sig_names.erase(key);
    }
    instance->m_persistant_list.erase(sig_name);
}

void SignalManager::update()
{
    std::vector< std::pair<Object*, std::string> > keys;
    for (auto pair : m_sig_names)
    {
        if (!m_persistant_list[pair.first.second])
            pair.second++;
        if (pair.second >= 2)
            keys.push_back(pair.first);
    }
    for (auto key : keys)
        m_sig_names.erase(key);
}
