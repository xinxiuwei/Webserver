#include "RequestManager.h"
#include "IoReader.h"
#include "Response.h"
#include <cerrno>
#include <errno.h>
#include <stdio.h> 
#include <cstdlib>
#include <string.h>

RequestManager::RequestManager(int connfd) 
{
	fileDescriptor=connfd;
	IoReader reader(fileDescriptor);
	std::vector<std::string> header;
	reader.getLineSplitedByBlank(header);

	method = header[0];
	uri = header[1];
	version = header[2];
}



void RequestManager::doit()
{
	
	if(method =="GET")
	{
		printf("method=%s\n",method);
		doExecute();
	}
	else
	{
		printf("can't Distinguish");

	}
}


void RequestManager::doExecute()
{
	std::string filename, cgiargs;

	int is_Static = parseUri(filename, cgiargs);
	Response(fileDescriptor, filename, cgiargs, is_Static).respond();
}

int RequestManager::parseUri(std::string& filename, std::string& cgiargs)
{
	if (uri.find("cgi-bin") == std::string::npos)
		return parseStaticContentUri(filename);
	else
		return parseDynamicContentUri(filename, cgiargs);
}

int RequestManager::parseStaticContentUri(std::string& filename)
{

	filename = "test-files" + uri;

	if (uri[uri.length() - 1] == '/')
		filename += "index.html";

	return STATIC;
}

int RequestManager::parseDynamicContentUri(std::string& filename, std::string& cgiargs)
{
	assignCigArgs(cgiargs);

	filename = "." +  uri;

	return DYNAMIC;
}

void RequestManager::assignCigArgs(std::string& cgiargs)
{
	
	std::string::size_type pos = uri.find_first_of("?");

	doAssignCigArgs(pos, cgiargs);
}

void RequestManager::doAssignCigArgs(std::string::size_type pos, std::string& cgiargs)
{
	if (pos != std::string::npos)
		cgiargs = uri.substr(pos, uri.length() - 1);
	else
		cgiargs.clear();
}

