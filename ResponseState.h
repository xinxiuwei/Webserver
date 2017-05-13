#ifndef RESPONSE_STATE_H
#define RESPONSE_STATE_H

#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sstream>

class ResponseState
{
public:
	ResponseState(int fd, std::string fName);
	void preRespond();
	void respond();
	void respondError(const std::string errNum, const std::string shortMsg, const std::string longMsg);
	virtual ~ResponseState()
	{

	}

protected:
	int getFileDescriptor();
    const std::string getFileName();
    struct stat& getStat();
    const std::string sizeTypeToStr(std::string::size_type sizeType);
	virtual const std::string buildRespondHeaders();

private:
	virtual const std::string buildForbiddenMsg() = 0;
	virtual void doRespond() = 0;
	const std::string buildRespondErrorHeaders(const std::string errNum, const std::string shortMsg);
	const std::string buildRespondErrorBody(const std::string errNum, const std::string shortMsg, const std::string longMsg);

private:
	struct stat sbuf;
	int fileDescriptor;
	std::string fileName;
};

#endif
