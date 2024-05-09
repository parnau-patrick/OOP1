#include"teste.h"
#include"service.h"
#include"repo.h"
#include"assert.h"
#include<iostream>
using namespace std;

//Test pentru add()
void testAdd()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };
	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	const auto& filme = serv.getAll();
	assert(filme.size() == 1);
}

//Test pentru sterge()
void testSterge()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };
	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	const auto& filme = serv.getAll();
	assert(filme.size() == 1);

	serv.sterge("Harry Potter", "fantasy");
	const auto& filme2 = serv.getAll();
	assert(filme2.size() == 0);

	try
	{
		serv.sterge("Harry Potter", "fantasy");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

//Test pentru modifica()
void testModifica()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };
	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	Film f("Cinderella", "desene animate", 2000, "-");

	serv.modifica("Harry Potter", "fantasy", f);
	
	const auto& filme = serv.getAll();
	assert(filme.size() == 1);
	assert(filme.at(0).get_titlu() == "Cinderella");

	try
	{
		serv.modifica("Harry Potter", "fantasy", f);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}

//Test pentru store()
void testStore()
{
	FilmRepo rep;
	Film f{ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" };
	rep.store(f);
	const auto& filme = rep.getAll();
	assert(filme.size() == 1);

	try
	{
		rep.store(f);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	rep.store({ "Cruella", "desene animate", 2020, "Cruella Devil" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);
}

//Test pentru get_message()
void testGetMessage()
{
	RepoException re("exceptie");

	assert(re.get_message()=="exceptie");

}

//Test pentru get_anAparitie()
void testeGetAnAparitie()
{
	Film f("a", "b", 2000, "c");

	assert(f.get_anAparitie() == 2000);
}

//Test pentru get_actorPrincipal()
void testeGetActorPrincipal()
{
	Film f("a", "b", 2000, "c");

	assert(f.get_actorPrincipal() == "c");
}

//Test pentru cauta()
void testCauta()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "Harry Potter", "desene animate", 2020, "-" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);

	vector<Film> cautare = serv.cauta("Harry");
	assert(cautare.size() == 2);

	vector<Film> cautare2 = serv.cauta("Ana");
	assert(cautare2.size() == 0);
}

//Test pentru filtrare()
void testFiltrare()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "Harry Potter 2", "desene animate", 2020, "-" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);

	vector<Film> filtrareTitlu = serv.filtrare(1,"Harry"); 
	assert(filtrareTitlu.size() == 2); 

	vector<Film> filtrareAn = serv.filtrare(2, "2000");
	assert(filtrareAn.size() == 3);
}

//Test pentru sortare() dupa titlu
void testSortareDupaTitlu()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "c", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "c", "desene animate", 2020, "-" });
	rep.store({ "a", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "z", "fantasy", 2000, "Alex Russo" });
	rep.store({ "e", "desene animate", 2000, "Cinderella" });

	assert(filme.size() == 5);

	vector<string> rezultat = { "a","c","c","e","z" };

	vector<Film> sortat = serv.sortare(1);

	int i = 0;
	//utilizez RANGE FOR pentru a parcurge vectorul sortat
	for (const auto& f:sortat)
	{
		assert(f.get_titlu() == rezultat.at(i));
		i++;
	}
}

//Test pentru sortare() dupa actor principal
void testSortareDupaActorPrincipal()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "c" });
	rep.store({ "Harry Potter 2", "desene animate", 2020, "c" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "a" });
	rep.store({ "Magicienii", "fantasy", 2000, "e" });
	rep.store({ "Cinderella", "desene animate", 2000, "z" });

	assert(filme.size() == 5);

	vector<string> rezultat = { "a","c","c","e","z" };

	vector<Film> sortat = serv.sortare(2);

	int i = 0;
	//utilizez RANGE FOR pentru a parcurge vectorul sortat
	for (const auto& f:sortat)
	{
		assert(f.get_actorPrincipal() == rezultat.at(i));
		i++;
	}
}

//Test pentru sortare() dupa an aparitie + gen
void testSortareDupaAnAparitieGen()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	const auto& filme = rep.getAll();
	rep.store({ "Harry Potter", "fantasy", 2000, "Daniel Radcliff" });
	rep.store({ "Harry Potter 2", "desene animate", 2020, "-" });
	rep.store({ "101 dalmatieni", "desene animate", 2010, "Cruella Devil" });
	rep.store({ "Cinderella", "desene animate", 2000, "Cinderella" });
	rep.store({ "Magicienii", "fantasy", 2000, "Alex Russo" }); 

	assert(filme.size() == 5);

	vector<int> rez1 = { 2000, 2000, 2000, 2010, 2020 };
	vector<string> rez2 = { "desene animate", "fantasy", "fantasy", "desene animate", "desene animate" };

	vector<Film> sortat = serv.sortare(3);

	int i = 0;
	//utilizez RANGE FOR pentru a parcurge vectorul sortat
	for (const auto& f:sortat)
	{
		assert(f.get_anAparitie() == rez1.at(i));
		assert(f.get_gen() == rez2.at(i));
		i++;
	}
}

void testSetters() 
{
	Film film("Initial Titlu", "Initial Gen", 2000, "Initial Actor");

	film.setTitlu("Noul Titlu");
	film.setGen("Noul Gen");
	film.setAnAparitie(2021);
	film.setActorPrincipal("Noul Actor");

	assert(film.get_titlu() == "Noul Titlu");
	assert(film.get_gen() == "Noul Gen");
	assert(film.get_anAparitie() == 2021);
	assert(film.get_actorPrincipal() == "Noul Actor");

}


//Test pentru delCos()
void testDel()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	try
	{
		serv.delCos();
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	serv.add("Harry Potter 2", "desene animate", 2020, "-" );
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil");
	serv.add("Cinderella", "desene animate", 2000, "Cinderella");
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo");

	vector<Film> filme = rep.getAll(); 

	serv.addCos("Harry Potter", "fantasy");
	serv.addCos("Harry Potter 2", "desene animate");
	serv.addCos("Cinderella", "desene animate");

	vector<Film> filmeCos = serv.getAllCos();
	assert(filmeCos.size() == 3);

	repoC.del(); 

	auto cos = serv.getAllCos();
	assert(cos.size() == 0);
}


//Test pentru addCos()
void testAddCos()
{
	FilmRepo rep;
	CosRepo repoC{ rep };
	FilmService serv{ rep, repoC };

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff");
	serv.add("Harry Potter 2", "desene animate", 2020, "-");
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil");
	serv.add("Cinderella", "desene animate", 2000, "Cinderella");
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo");

	vector<Film> filme = rep.getAll();

	serv.addCos("Harry Potter", "fantasy");
	serv.addCos("Harry Potter 2", "desene animate");
	serv.addCos("Cinderella", "desene animate");

	vector<Film> filmeCos = serv.getAllCos();
	assert(filmeCos.size() == 3);

	try
	{
		serv.addCos("Tom & Jerry", "desene animate");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	vector<Film> filmeCos2 = serv.getAllCos(); 
	assert(filmeCos2.size() == 3); 
}


//Test pentru genereazaCos()
void testGenereaza()
{
	FilmRepo rep; 
	CosRepo repoC{ rep }; 
	FilmService serv{ rep, repoC }; 

	vector<Film> genereazaVid = serv.genereazaCos(2);
	assert(genereazaVid.size() == 0);

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff"); 
	serv.add("Harry Potter 2", "desene animate", 2020, "-"); 
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil"); 
	serv.add("Cinderella", "desene animate", 2000, "Cinderella"); 
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo"); 

	vector<Film> filme = rep.getAll(); 

	int cate = 0;

	vector<Film> generat = serv.genereazaCos(7);

	for (const auto& f : filme)
	{
		for (const auto& g : generat)
		{
			if (f.get_titlu() == g.get_titlu())
			{
				cate++;
			}
		}
	}

	assert(cate == 7);
}

//Test pentru raport()
void testRaport()
{
	FilmRepo rep; 
	CosRepo repoC{ rep }; 
	FilmService serv{ rep, repoC }; 

	serv.add("Harry Potter", "fantasy", 2000, "Daniel Radcliff"); 
	serv.add("Harry Potter 2", "desene animate", 2020, "-"); 
	serv.add("101 dalmatieni", "desene animate", 2010, "Cruella Devil"); 
	serv.add("Cinderella", "desene animate", 2000, "Cinderella"); 
	serv.add("Magicienii", "fantasy", 2000, "Alex Russo"); 

	map<string, DTOFilm> mp = serv.raport();

	assert(mp.size() == 2);
}




void testAll()
{
	testAdd();
	testSterge();
	testModifica();
	testStore();
	testGetMessage();
	testeGetAnAparitie(); 
	testeGetActorPrincipal();
	testCauta();
	testFiltrare();
	testSortareDupaTitlu();
	testSortareDupaActorPrincipal();
	testSortareDupaAnAparitieGen();
	testSetters();

	testDel();
	testAddCos();
	testGenereaza();

	testRaport();

	std::cout << "\nTestele au avut succes!\n";
}