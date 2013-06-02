ransac : main.cpp
	g++ -o ransac main.cpp fitline.cpp ransac.cpp
clean:
	rm -f ransac
