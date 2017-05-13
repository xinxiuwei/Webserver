/*
 * IoReader.cpp
 *
 *  Created on: 2017年4月18日
 *      Author: xinxiuwei
 */

#include "IoReader.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <cerrno>

namespace
{
const int MAX_LENGTH = 8192;

struct rio_t
{
	int rio_fd; /* descriptor for this internal buf */
	int rio_cnt; /* unread bytes in internal buf */
	char *rio_bufptr; /* next unread byte in internal buf */
	char rio_buf[MAX_LENGTH]; /* internal buffer */
};

void unix_error(char *msg) /* unix-style error */
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}

void rio_readinitb(rio_t *rp, int fd)
{
	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_bufptr = rp->rio_buf;
}

void Rio_readinitb(rio_t *rp, int fd)
{
	rio_readinitb(rp, fd);
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
	int cnt;

	while (rp->rio_cnt <= 0)
	{ /* refill if buf is empty */
		rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
		if (rp->rio_cnt < 0)
		{
			if (errno != EINTR) /* interrupted by sig handler return */
				return -1;
		}
		else if (rp->rio_cnt == 0) /* EOF */
			return 0;
		else
			rp->rio_bufptr = rp->rio_buf; /* reset buffer ptr */
	}

	/* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
	cnt = n;
	if (rp->rio_cnt < n)
		cnt = rp->rio_cnt;
	memcpy(usrbuf, rp->rio_bufptr, cnt);
	rp->rio_bufptr += cnt;
	rp->rio_cnt -= cnt;
	return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
	int n, rc;
	char c, *bufp = reinterpret_cast<char*>(usrbuf);

	for (n = 1; n < maxlen; n++)
	{
		if ((rc = rio_read(rp, &c, 1)) == 1)
		{
			*bufp++ = c;
			if (c == '\n')
				break;
		}
		else if (rc == 0)
		{
			if (n == 1)
				return 0; /* EOF, no data read */
			else
				break; /* EOF, some data was read */
		}
		else
			return -1; /* error */
	}
	*bufp = 0;
	return n;
}

ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
	ssize_t rc;

	if ((rc = rio_readlineb(rp, usrbuf, maxlen)) < 0)
		unix_error("Rio_readlineb error");
	return rc;
}

rio_t rio;
}

IoReader::IoReader(int fd)
{
	Rio_readinitb(&rio, fd);
}

void IoReader::getLineSplitedByBlank(std::vector<std::string>& buf)
{
	char innerBuf[MAX_LENGTH], method[MAX_LENGTH], uri[MAX_LENGTH], version[MAX_LENGTH];
	Rio_readlineb(&rio, innerBuf, MAX_LENGTH);

	sscanf(innerBuf, "%s %s %s", method, uri, version);
	buf.push_back(method);
	buf.push_back(uri);
	buf.push_back(version);
}




