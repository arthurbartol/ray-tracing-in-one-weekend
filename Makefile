default:
	g++ -std=c++20 ./src/*.cpp -o ./bin/raytracer
	./bin/raytracer >> ./bin/image.ppm
