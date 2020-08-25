#ifndef SIGNAL_H
#define SIGNAL_H

#include <map>
#include "object.h"

class SignalManager
{
public:
	SignalManager() { instance = this; }
	~SignalManager() {}

	static void emit(const std::pair<Object*, std::string>&, bool persist = false);
	static bool emitted(const std::string&, Object* source = NULL);
	static void treat(const std::string&, Object* source = NULL);
	void update();

private:
	std::map< std::pair<Object*, std::string>, int > m_sig_names;
	std::map<std::string, bool> m_persistant_list;

	static SignalManager* instance;
};

#endif // SIGNAL_H

