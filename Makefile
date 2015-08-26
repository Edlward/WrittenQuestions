CXXFLAGS = -lpthread

WrittenQuestions: 
	g++ test.cpp -o test $(CXXFLAGS)
	gcc async_callback.c -o async_callback $(CXXFLAGS)
clean:
	rm test async_callback
	
