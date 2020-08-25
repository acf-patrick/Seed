#include "signal.h"
#include <vector>

SignalManager* SignalManager::instance(NULL);

void SignalManager::emit(const std::string& sig_name, bool persist)
{
	instance->m_sig_names[sig_name] = 0;
	if (persist)
		instance->m_persistant_list[sig_name] = true;
}

bool SignalManager::emitted(const std::string& sig_name)
{ return instance->m_sig_names[sig_name]; }

void SignalManager::treat(const std::string& sig_name)
{
    instance->m_sig_names.erase(sig_name);
    instance->m_persistant_list.erase(sig_name);
}

void SignalManager::update()
{
	std::vector<std::string> keys;
    for (auto pair : m_sig_names)
	{
		if (!m_persistant_list[pair.first])
			pair.second++;
		if (pair.second >= 2)
			keys.push_back(pair.first);
	}
	for (auto key : keys)
		m_sig_names.erase(key);
}
