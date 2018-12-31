trainermake: stick_trainer.o
	g++ -c -g stick_trainer.cpp
	g++ stick_trainer.o -o trainer -g -lsfml-graphics -lsfml-window -lsfml-system
	rm stick_trainer.o