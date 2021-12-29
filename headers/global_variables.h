#pragma once

#include "database.h"

// TODO: find better solution to initialize the database

// use on Windows 10
inline Database sqldb("C:\\Users\\neuba\\CodeProjects\\PO-proj\\Inventory-Manager\\Inventory-Manager\\database\\sqlite3.db");

// use on Linux
/* inline Database sqldb("../database/sqlite3.db"); */

inline int userIndex = 0;
inline int productIndex = 0;