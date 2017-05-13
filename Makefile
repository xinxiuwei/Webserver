objects=server_main.o IoReader.o IoWriter.o SocketConnect.o RequestManager.o Response.o DynamicResponseState.o StaticResponseState.o ResponseState.o
server:$(objects)
	g++ -o sweb $(objects) -lpthread

server_main.o:RequestManager.h
IoReader.o:IoReader.h
IoWriter.o:IoWriter.h
SocketConnect.o:SocketConnect.h
RequestManager.o:IoReader.h RequestManager.h Response.h
Reponse.o:WebError.h Response.h StaticResponseState.h DynamicResponseState.h
ResponseState.o:IoWriter.h WebError.h ResponseState.h
DynamicResponseState.o:IoWriter.h DynamicResponseState.h
StaticResponseState.o:IoWriter.h StaticResponseState.h


.PHONY : clean
clean:
	rm server $(objects)