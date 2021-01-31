#include"serverparser.h"

struct PlayerMsg {
	string playerName;
	string playerMsg;
};

struct Advancement {
	string playerName;
	string advancement;

	void operator=(Advancement* in) {
		this->playerName = in->playerName;
		this->advancement = in->advancement;
	}
};

