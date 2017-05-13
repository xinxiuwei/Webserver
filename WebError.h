#ifndef WEB_ERROR_H
#define WEB_ERROR_H

#include <string>

struct WebError
{
	WebError(const std::string& errNum,
			const std::string& shortMsg,
			const std::string& longMsg)
			: ErrNum(errNum), ShortMsg(shortMsg), LongMsg(longMsg)
	{

	}

	~WebError() throw ()
	{

	}

	std::string ErrNum;
	std::string ShortMsg;
	std::string LongMsg;
};

#endif
