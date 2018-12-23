trainermake: stick_trainer.o
	g++ -c stick_trainer.cpp
	g++ stick_trainer.o -o trainer -lsfml-graphics -lsfml-window -lsfml-system
	rm stick_trainer.o