#pragma once

#include "database.h"
#include "user.h"
#include "admin.h"

/* --------------------- SHARED VARIABLES --------------------- *
 *         These variables are used in the program and          *
 *          SHOULD NOT be changed or modified by user           */
inline User *globalUser = new User;
inline Admin* adminUser = (Admin *) globalUser;
inline int productIndex = 0;

/* --------------------- GLOBAL VARIABLES --------------------- *
 *                   Feel free to modify them                   */

inline char* pathLinux = "../database/sqlite3.db";
inline char* pathWindows = "C:\\Users\\neuba\\CodeProjects\\PO-proj\\Inventory-Manager\\Inventory-Manager\\database\\sqlite3.db";
inline Database sqldb(pathWindows);
const int loginAttempts = 3;
const int passwordLength = 8;
const string domain = "@company.com";
const bool debug = false;  // log database warnings and errors