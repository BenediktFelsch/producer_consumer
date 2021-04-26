
# this is picked up by nmake on windows

all: producer_consumer.exe

producer_consumer.exe: producer.obj consumer.obj queue.obj main.obj thread_helper.obj util.obj
	link $(LFLAGS) $** /out:producer_consumer.exe

clean:
	-del *.obj
	-del producer_consumer.exe
