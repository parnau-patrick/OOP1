#pragma once
#include<string>
#include<map>
#include"domain.h"
#include"repo.h"
using std::string;
using std::map;

//Service pentru Film
class FilmService
{
private:
	FilmRepo& rep;
    CosRepo& repoC;

	//pentru UNDO
	///vector<vector<Film>> undo;

public:
	
    FilmService(FilmRepo& rep, CosRepo& repoC) noexcept : rep{ rep }, repoC{ repoC } {}

    FilmService(const FilmService& ot) = delete;
    FilmService() = default;

    //Adauga film
    void add(string titlu, string gen, int anAparitie, string actorPrincipal); 

    //Sterge film
    void sterge(string titlu, string gen); 

    //Modifica film
    void modifica(string titlu, string gen, const Film& film);

    //Returneaza toate filmele
    const vector<Film>& getAll();

    //Cauta film dupa titlu
    vector<Film> cauta(string titlu); 

    //Filtreaza filme
    vector<Film> filtrare(int filtru, string tip);

    //Sorteaza filme
    vector<Film> sortare(int tip); 

    //Sterge toate filmele din cos
    void delCos();

    //Adauga film in cos
    void addCos(string titlu, string gen);

    //Returneaza toate filmele din cos
    const vector<Film>& getAllCos() const;

    //Genereaza un cos care contine aleatoriu un numar de filme dat din lista
    vector<Film> genereazaCos(int numar);


    map<string, DTOFilm> raport();
};