#pragma once
#include <string>

class Manager;

int init_from_lua(Manager * manager, std::string filename);
