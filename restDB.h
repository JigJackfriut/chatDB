#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>

#include <mariadb/conncpp.hpp>

#include "restEntry.h"

#ifndef USERDB_H
#define USERDB_H

#define DB_URL "jdbc:mariadb://localhost:3306/rest"
#define USER "root"
#define PASS "newpassword"

using namespace std;

class restDB {
public:
    restDB();
    vector<restEntry> find(string search);
    vector<restEntry> getUserEntries(string username);
    restEntry fetchEntry(string idnum);
    void addEntry(string user, string email, string pass);
    void editEntry(string idnum, string user,string email,string pass);
    void deleteEntry(string idnum);
private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* RESTDB_H */
