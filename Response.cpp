/*
 * IoReader.cpp
 *
 *  Created on: 2017年4月18日
 *      Author: xinxiuwei
 */

#include "Response.h"
#include "WebError.h"
#include "StaticResponseState.h"
#include "DynamicResponseState.h"
#include <stdexcept>

Response::Response(int fd, std::string name, std::string cgiargs, int isStc)
{
	switch(isStc)
	{
		case STATIC:
			state = new StaticResponseState(fd, name);
			break;
		case DYNAMIC:
			state = new DynamicResponseState(fd, name, cgiargs);
			break;
	}
	
		
}

Response::~Response()
{
	if(state)
		delete state;
}

void Response::respond()
{
	try
	{
		preRespond();
		doRespond();
	}
	catch (WebError& err)
	{
		return state->respondError(err.ErrNum, err.ShortMsg, err.LongMsg);
	}
	catch (std::runtime_error& err)
	{
		return state->respondError("500", "Server internal error", err.what());
	}
}

void Response::preRespond()
{
	state->preRespond();
}

void Response::doRespond()
{
	state->respond();
}



