#pragma once

#include "database.h"
#include "user.h"

// use on Windows 10
/* inline Database sqldb("C:\\Users\\neuba\\CodeProjects\\PO-proj\\Inventory-Manager\\Inventory-Manager\\database\\sqlite3.db"); */
// TODO: find better solution to initialize the database
// use on Linux
inline Database sqldb("../database/sqlite3.db");

inline User globalUser;
const int loginAttempts = 3;
inline int userIndex = 0;
inline int productIndex = 0;
