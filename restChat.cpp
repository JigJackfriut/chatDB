//
//  namesAPI.cc - a microservice demo program
//
// James Skon
// Kenyon College, 2022
//

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include "httplib.h"
#include <vector>

#include "restDB.h"
#include "restEntry.h"

using namespace httplib;
using namespace std;

const int port = 5005;





int main(void) {
  Server svr;
  restDB rDB;
int nextUser=0;
 map<string,vector<string>> messageMap;
 map<string,string> userMap;
 map<string,string> userEmail;

	
  /* "/" just returnsAPI name */
  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content("Chat API", "text/plain");
  });

	
//code for registration!!!!!!!
 svr.Get(R"(/chat/register/(.*)/(.*)/(.*))", [&](const Request& req, Response& res) {
	res.set_header("Access-Control-Allow-Origin","*");
 	string username = req.matches[1];
	string email = req.matches[2];
	string password = req.matches[3];
	 
 	string result;
 	vector<string> empty;

 vector<restEntry> entries = rDB.getUserEntries(username);
bool usernameExists = false;
for (const auto& entry : entries) {
    if (entry.user == username) {
        usernameExists = true;
        break;
    }
}

	 
 if (usernameExists or messageMap.count(username) or messageMap.count(email) or password.length() < 7){
 result = "{\"status\":\"registrationfailure\"}";
 } else {
 messageMap[username]= empty;
	userEmail[username] = email;
	restDB rDB;
	string user=username; string pass=password;
	rDB.addEntry(user,email,pass);
 result = "{\"status\":\"success\",\"user\":\"" + username + "\",\"email\":\"" + email + "\",\"pass\":\"" + password + "\"}";
 }
 });
	



  cout << "Server listening on port " << port << endl;
  svr.listen("0.0.0.0", port);

}
