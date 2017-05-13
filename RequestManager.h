#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include <string>

class RequestManager
{
public:
	RequestManager(int connfd);
	
	void doit();
	virtual void doExecute();
	int parseUri(std::string& filename, std::string& cgiargs);
	int parseStaticContentUri(std::string& filename);
	int parseDynamicContentUri(std::string& filename, std::string& cgiargs);
	void assignCigArgs(std::string& cgiargs);
	void doAssignCigArgs(std::string::size_type pos, std::string& cgiargs);

private:
	enum State { STATIC, DYNAMIC};

	int fileDescriptor;
	std::string uri;
	std::string method;
	std::string version;
};

#endif
