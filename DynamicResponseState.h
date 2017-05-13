/*
 * DynamicResponseState.h
 *
 *  Created on: 2017年4月18日
 *      Author: xinxiuwei
 */

#ifndef RESPONSE_DYNAMICRESPONSESTATE_H_
#define RESPONSE_DYNAMICRESPONSESTATE_H_

#include "ResponseState.h"

class DynamicResponseState : public ResponseState
{
public:
	DynamicResponseState(int fd, std::string fName, std::string args);

private:
	virtual const std::string buildForbiddenMsg();
	virtual void doRespond();
	void execveCgiProgram();

private:
	std::string cgiArgs;
};



#endif /* RESPONSE_DYNAMICRESPONSESTATE_H_ */
