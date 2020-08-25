#ifndef SIGNAL_H
#define SIGNAL_H

#include <map>

class SignalManager
{
public:
	SignalManager() { instance = this; }

	static void emit(const std::string&, bool persist = false);
	static bool emitted(const std::string&);
	static void treat(const std::string&);
	void update();

private:
	std::map<std::string, int> m_sig_names;
	std::map<std::string, bool> m_persistant_list;

	static SignalManager* instance;
};

#endif // SIGNAL_H

