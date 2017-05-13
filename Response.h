#include <string>

class ResponseState;

class Response
{
public:
	Response(int fd, std::string name, std::string cgiargs, int isStc);
	~Response();
	void respond();

private:
	void preRespond();
	void doRespond();
	Response(const Response&);
	Response& operator= (const Response&);
private:
	enum State { STATIC, DYNAMIC};
	ResponseState* state;
};