/*
 * StaticResponseState.h
 *
 *  Created on: 2017年4月18日
 *      Author: xinxiuwei
 */

#ifndef RESPONSE_STATICRESPONSESTATE_H_
#define RESPONSE_STATICRESPONSESTATE_H_

#include "ResponseState.h"

class StaticResponseState : public ResponseState
{
public:
	StaticResponseState(int fd, std::string fName);

private:
	virtual const std::string buildForbiddenMsg();
	virtual void doRespond();
	virtual const std::string buildRespondHeaders();
	const std::string getFiletype();
};

#endif /* RESPONSE_STATICRESPONSESTATE_H_ */
