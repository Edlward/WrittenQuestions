CXXFLAGS = -lpthread
CFLAGS = -std=c99
WrittenQuestions: 
	g++ test.cpp -o test $(CXXFLAGS)
	gcc async_callback.c -o async_callback $(CXXFLAGS)
	g++ cxx_async_callback.cpp -o cxx_async_callback $(CXXFLAGS)
	gcc GetListMidPos.c -o GetListMidPos $(CFLAGS)
	gcc TwoStackToQueue.c -o TwoStackToQueue $(CFLAGS)
clean:
	rm test async_callback cxx_async_callback GetListMidPos TwoStackToQueue
	
