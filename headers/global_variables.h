#pragma once

#include "database.h"

// TODO: find better solution to initialize the database

inline Database sqldb("../database/sqlite3.db");  // change if needed
inline int userIndex = 0;