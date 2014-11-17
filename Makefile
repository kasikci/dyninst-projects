all:
	g++ -L/usr/local/lib controller.cpp -o controller -lpcontrol

clean:
	rm -f controller
