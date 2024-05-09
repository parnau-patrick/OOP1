#include"ui.h"
#include"teste.h"

int main()
{
	testAll();
	
	{
		FilmRepo rep;
		CosRepo repoC{ rep }; 
		FilmService serv{ rep, repoC };

		//Filme
		serv.add("Uncharted", "actiune", 2022, "Tom Holland");  //1
		serv.add("John Wick", "actiune", 2014, "Keanu Reeves");  //2
		serv.add("In timp", "actiune", 2011, "Justin Timberlake");  //3
		serv.add("Diavolul se imbraca de la Prada", "comedie", 2006, "Anne Hathaway");  //4
		serv.add("Blonda de la drept", "comedie", 2001, "Reese Witherspoon");  //5
		serv.add("Oameni mari si fara minte", "comedie", 2010, "Adam Sandler");  //6
		serv.add("Crima din Orient Express", "politist", 2017, "Kenneth Branagh");  //7
		serv.add("Hunger Games", "thriller", 2012, "Jennifer Lawrence");  //8
		serv.add("Hunger Games 2", "thriller", 2012, "Jennifer Lawrence");  //9
		serv.add("Harry Potter 1", "fantasy", 2001, "Daniel Radcliffe");  //10


		UI ui{ serv };

		ui.startUI();
	}
	

	return 0;
}