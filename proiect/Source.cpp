//Acronimul numelui Gaina Aurelian-Octavian => se folosesc literele G, A si O
//Asadar tematica proiectulu va fi Organizatie

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <set>
#include <conio.h>

using namespace std;



class Angajat {

private:

	char* nume;
	string departament = "N/A";
	int salariu = 0;
	int zile_concediu = 0;
	int* bonusuri = NULL;
	const int id;
	static int nr_angajati;
	static int nr_bonusuri;

public:

	Angajat() :id(nr_angajati++)
	{
		this->nume = new char[strlen("Necunoscut") + 1];
		strcpy(this->nume, "Necunoscut");

	}

	Angajat(const char* nume, int salariu) :id(nr_angajati++)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->salariu = salariu;
	}

	Angajat(const char* nume, string departament, int salariu, int zile_concediu, int* bonusuri) :id(nr_angajati++)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->departament = departament;
		this->salariu = salariu;
		this->zile_concediu = zile_concediu;
		if (nr_bonusuri > 0)
		{
			this->bonusuri = new int[this->nr_bonusuri];
			for (int i = 0; i < nr_bonusuri; i++)
			{
				this->bonusuri[i] = bonusuri[i];
			}
		}

	}

	Angajat(const Angajat& a) :id(a.id)
	{
		this->nume = new char[strlen(a.nume) + 1];
		strcpy(this->nume, a.nume);
		this->departament = a.departament;
		this->salariu = a.salariu;
		this->zile_concediu = a.zile_concediu;
		if (a.nr_bonusuri > 0 && a.bonusuri != NULL)
		{
			this->bonusuri = new int[a.nr_bonusuri];
			for (int i = 0; i < a.nr_bonusuri; i++)
			{
				this->bonusuri[i] = a.bonusuri[i];
			}
		}
	}

	Angajat& operator=(const Angajat& a)
	{
		if (this != &a)
		{
			if (this->nume != NULL)
				delete[] this->nume;
			if (this->bonusuri != NULL)
				delete[] this->bonusuri;
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
			this->departament = a.departament;
			this->salariu = a.salariu;
			this->zile_concediu = a.zile_concediu;
			if (a.nr_bonusuri > 0 && a.bonusuri != NULL)
			{
				this->bonusuri = new int[a.nr_bonusuri];
				for (int i = 0; i < a.nr_bonusuri; i++)
				{
					this->bonusuri[i] = a.bonusuri[i];
				}
			}
		}
		return *this;
	}

	Angajat& operator+=(int marireSalariu)
	{
		this->salariu = this->salariu + marireSalariu;
		return *this;
	}

	Angajat& operator+(int marireSalariu)
	{
		Angajat rez = *this;
		rez += marireSalariu;
		return rez;
	}

	bool operator==(Angajat a)
	{
		return this->departament == a.departament;
	}

	bool operator!()
	{
		if (this->zile_concediu == 0)
			return true;
		return false;
	}

	bool operator>(Angajat a)
	{
		return this->salariu > a.salariu;
	}

	Angajat operator++() {
		this->zile_concediu++;
		return *this;
	}

	Angajat operator++(int)
	{
		Angajat a = *this;
		this->zile_concediu++;
		return a;
	}

	explicit operator double()
	{
		return this->salariu;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < this->nr_bonusuri)
			return this->bonusuri[index];
	}

	~Angajat()
	{
		if (this->nume != NULL)
			delete[] this->nume;
		if (this->bonusuri != NULL)
			delete[] this->bonusuri;
	}

	void scrieBinar(ofstream& o)
	{
		//nume
		int lungime = strlen(this->nume); 
		o.write((char*)&lungime, sizeof(int));  
		o.write(this->nume, sizeof(char) * lungime);

		//departament
		int nrLitNume = this->departament.size();
		o.write((char*)&nrLitNume, sizeof(int));
		o.write(this->departament.c_str(), nrLitNume);

		//salariu
		o.write((char*)&this->salariu, sizeof(this->salariu));

		//zile concediu
		o.write((char*)&this->zile_concediu, sizeof(this->zile_concediu));
		
		//bonusuri
		for (int i = 0; i < this->nr_bonusuri; i++) {

			o.write((char*)&this->bonusuri[i], sizeof(this->bonusuri[i]));
		}

		//id
		/*o.write((char*)&this->id, sizeof(this->id));*/
	}

	void citireBinar(ifstream& in)
	{
		int lungime;
		in.read((char*)&lungime, sizeof(int));
		char nume_nou[100];
		cout << "Noul nume al angajatului";
		in.read(nume_nou, lungime);
		this->nume = nume_nou;

		int lungime2;
		in.read((char*)&lungime2, sizeof(int));
		char departament_nou[2300];
		in.read(departament_nou, lungime2);

		this->departament = departament_nou;

		in.read((char*)&this->salariu, sizeof(this->salariu));

		in.read((char*)&this->zile_concediu, sizeof(this->zile_concediu));

		delete[]  this->bonusuri;
		this->bonusuri = new int[this->zile_concediu];
		for (int i = 0; i < this->zile_concediu; i++) 
		{
			in.read((char*)&this->bonusuri[i], sizeof(this->bonusuri[i]));
		}
		
		in.read((char*)&this->id, sizeof(this->id));

	}

	friend istream& operator>>(istream& in, Angajat& a)
	{
		if (a.nume != NULL)
			delete[] a.nume;
		if (a.bonusuri != NULL)
			delete[] a.bonusuri;
		cout << "\nIntroduceti numele angajatului: ";
		char aux[100];
		in >> aux;
		a.nume = new char[strlen(aux) + 1];
		strcpy(a.nume, aux);
		cout << "\nIntroduceti numele departamentului: ";
		in >> a.departament;
		cout << "\nIntroduceti salariul angajatului: ";
		in >> a.salariu;
		cout << "\nIntroduceti zilele de concediu: ";
		in >> a.zile_concediu;
		if (a.nr_bonusuri == 0)
		{
			a.bonusuri = 0;
		}
		else
		{
			a.bonusuri = new int[a.nr_bonusuri];
			cout << "\nBonusuri:";
			for (int i = 0; i < a.nr_bonusuri; i++)
			{
				cout << "\nBonusul " << i + 1 << " este: ";
				in >> a.bonusuri[i];
			}
		}
		return in;


	}

	friend ifstream& operator>>(ifstream& in, Angajat& a)
	{
		//------------------------------------------------------
		//nume
		char buffer[200];
		in>>buffer;
		delete[] a.nume; 
		a.nume = new char[strlen(buffer) + 1];
		strcpy(a.nume, buffer);
		//------------------------------------------------------
		//departament
		char buffer1[100];
		in>>buffer1;
		a.departament = buffer1;
		//------------------------------------------------------
		//salariu
		in >> a.salariu;
		//------------------------------------------------------
		//zile concediu
		in>>a.zile_concediu;
		//------------------------------------------------------
		//bonusuri
		delete[] a.bonusuri;
		a.bonusuri = new int[a.nr_bonusuri];
		for (int i = 0; i < a.nr_bonusuri; i++)
		{//------------------------------------------------------
			//bon i
			in >> a.bonusuri[i];
		}
		int aux_id;
		in >> aux_id;
		//------------------------------------------------------
		//final
		return in;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a)
	{
		out << "\nNumele angajatului: " << a.nume;
		out << "\nDepartamentul angajatului: " << a.departament;
		out << "\nSalariului angajtului: " << a.salariu;
		out << "\nNumarul de zile de concediu: " << a.zile_concediu;
		for (int i = 0; i < a.nr_bonusuri; i++)
		{
			out << "\nBonusul " << i + 1 << " a fost: " << a.bonusuri[i];
		}
		out << "\nID-ul angajatului: " << a.id;
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Angajat& a)
	{
		out << a.nume << endl;
		out << a.departament << endl;
		out << a.salariu << endl;
		out << a.zile_concediu << endl;
		for (int i = 0; i < a.nr_bonusuri; i++)
		{
			out << a.bonusuri[i] << endl;
		}
		out << a.id << endl;
		return out;
	}

	char* getNume()
	{
		return this->nume;
	}

	void setNume()
	{
		char nume_nou[100];
		cout << "Noul nume al angajatului";
		cin >> nume_nou;
		this->nume = nume_nou;
	}

	int getSalariu()
	{
		return this->salariu;
	}

	int getZileConcediu()
	{
		return this->zile_concediu;
	}

	string getDepartament()
	{
		return this->departament;
	}

	void setDepartament()
	{
		string departament_nou;
		cout << "Noul departament al angajatului: ";
		cin >> departament_nou;
		this->departament = departament_nou;
	}

	const int getID()
	{
		return this->id;
	}

	int* getBonusuri()
	{
		if (this->bonusuri != NULL && this->nr_bonusuri != 0)
		{
			for (int i = 0; i < this->nr_bonusuri; i++)
			{
				cout << "\nBonusul " << i + 1 << " a fost: " << this->bonusuri[i];
			}
		}
	}

	void setBonusuri()
	{
		if (this->bonusuri != NULL)
			delete[] this->bonusuri;
		this->bonusuri = new int[this->nr_bonusuri];
		for (int i = 0; i < this->nr_bonusuri; i++)
		{
			int x;
			cout << "\nBonusul " << i + 1 << " este: ";
			cin >> x;
			this->bonusuri[i] = x;
		}
	}

	void setSalariu()
	{
		int salariuNou;
		cout << "\nNoul salariu: ";
		cin >> salariuNou;
		this->salariu = salariuNou;
	}

	void setZileConcediu() {
		int zileConcediuNoi;
		cout << "\nNoul numar de zile de concediu: ";
		cin >> zileConcediuNoi;
		this->zile_concediu = zileConcediuNoi;
	}

	static int getNumarAngajati()
	{
		return nr_angajati;
	}

	void setNumarAngajati()
	{
		nr_angajati++;
	}

	void setNrBonusuri()
	{
		int nrnou;
		cout << "\nNoul numar de bonusuri: ";
		cin >> nrnou;
		nr_bonusuri = nrnou;
	}

	static void IerarhieSalariati()
	{
		vector <Angajat> a;
		ifstream fin("angajati.txt");
		Angajat ang11;
		fin >> ang11;
		do {
			a.push_back(ang11);
			Angajat ang11;
		} while (fin >> ang11);
		fin.close();
		ofstream fout("IerarhieSalariati.txt");
		string* vec = new string[a.size()];
		int* v = new int[a.size()];

		for (int i = 0; i < a.size(); i++)
		{
			vec[i] = a[i].getNume();
			v[i] = a[i].getSalariu();
		}
		for (int i = 0; i < a.size() - 1; i++)
		{
			for (int j = i + 1; j < a.size(); j++)
			{
				if (v[j] > v[i])
				{
					int aux = v[i];
					v[i] = v[j];
					v[j] = aux;
					string aux1 = vec[i];
					vec[i] = vec[j];
					vec[j] = aux1;
				}
			}
		}
		for (int i = 0; i < a.size(); i++)
		{
			fout << vec[i] << "\n";
			fout << v[i] << "\n";
		}
		fout.close();
		for (int i = 0; i < a.size(); i++)
		{
			cout << "Nume: ";
			cout << vec[i] << "\n";
			cout << "Salariu: ";
			cout << v[i] << "\n";
		}
		cout << "\nFisier Salvat" << endl;
	}

};

class Produs
{
private:
	char* denumire = NULL;
	int venituri = 0;
	int nr_versiuni = 0;
	int* an_versiune = NULL;
	int* stoc_versiune = NULL;
	int* pret_versiune = NULL;

public:
	Produs()
	{
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		
	}

	Produs(const char* denumire, int venituri)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->venituri = venituri;

	}

	Produs(const char* denumire, int venituri, int nr_versiuni, int* an_versiune, int* stoc_versiune, int* pret_versiune)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->venituri = venituri;
		
		if (nr_versiuni > 0 && an_versiune != NULL && stoc_versiune != NULL && pret_versiune != NULL)
		{
			this->nr_versiuni = nr_versiuni;
			this->an_versiune = new int[this->nr_versiuni];
			this->stoc_versiune = new int[this->nr_versiuni];
			this->pret_versiune = new int[this->nr_versiuni];
			for (int i = 0; i < this->nr_versiuni; i++)
			{
				this->an_versiune[i] = an_versiune[i];
				this->stoc_versiune[i] = stoc_versiune[i];
				this->pret_versiune[i] = pret_versiune[i];
			}
		}
	}

	Produs(const Produs& p)
	{
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->venituri = p.venituri;
		if (p.nr_versiuni > 0 && p.an_versiune != NULL && p.stoc_versiune != NULL && p.pret_versiune != NULL)
		{
			this->nr_versiuni = p.nr_versiuni;
			this->an_versiune = new int[this->nr_versiuni];
			this->stoc_versiune = new int[this->nr_versiuni];
			this->pret_versiune = new int[this->nr_versiuni];
			for (int i = 0; i < this->nr_versiuni; i++)
			{
				this->an_versiune[i] = p.an_versiune[i];
				this->stoc_versiune[i] = p.stoc_versiune[i];
				this->pret_versiune[i] = p.pret_versiune[i];
			}
		}
	}

	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			if (this->denumire != NULL)
				delete[] this->denumire;
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
			this->venituri = p.venituri;
			if (this->an_versiune != NULL)
				delete[] this->an_versiune;
			if (this->stoc_versiune != NULL)
				delete[] this->stoc_versiune;
			if (this->pret_versiune != NULL)
				delete[] this->pret_versiune;
			if (p.nr_versiuni > 0 && p.an_versiune != NULL && p.stoc_versiune != NULL && p.pret_versiune != NULL)
			{
				this->nr_versiuni = p.nr_versiuni;
				this->an_versiune = new int[this->nr_versiuni];
				this->stoc_versiune = new int[this->nr_versiuni];
				this->pret_versiune = new int[this->nr_versiuni];
				for (int i = 0; i < this->nr_versiuni; i++)
				{
					this->an_versiune[i] = p.an_versiune[i];
					this->stoc_versiune[i] = p.stoc_versiune[i];
					this->pret_versiune[i] = p.pret_versiune[i];
				}
			}
		}
		return *this;

	}


	~Produs()
	{
		if (this->denumire != NULL)
			delete[] this->denumire;
		if (this->an_versiune != NULL)
			delete[] this->an_versiune;
		if (this->stoc_versiune != NULL)
			delete[] this->stoc_versiune;
		if (this->pret_versiune != NULL)
			delete[] this->pret_versiune;

	}

	void scrieBinar(ofstream& o)
	{

		int lungime = strlen(this->denumire) + 1; 
		o.write((char*)&lungime, sizeof(int));
		o.write(denumire, sizeof(char) * lungime);

		o.write((char*)&this->venituri, sizeof(this->venituri));

		o.write((char*)&this->nr_versiuni, sizeof(this->nr_versiuni));

		for (int i = 0; i < this->nr_versiuni; i++) {

			o.write((char*)&this->an_versiune[i], sizeof(this->an_versiune[i]));
			o.write((char*)&this->stoc_versiune[i], sizeof(this->stoc_versiune[i]));
			o.write((char*)&this->pret_versiune[i], sizeof(this->pret_versiune[i]));
		}

	}

	void citireBinar(ifstream& in)
	{
		int lungime;
		in.read((char*)&lungime, sizeof(int));
		char nume_nou[100];
		cout << "Noua denumire al produsului";
		in.read(nume_nou, lungime);
		this->denumire = nume_nou;

		in.read((char*)&this->venituri, sizeof(this->venituri));

		in.read((char*)&this->nr_versiuni, sizeof(this->nr_versiuni));




		delete[] this->an_versiune;
		delete[] this->stoc_versiune;
		delete[] this->pret_versiune;

		
		for (int i = 0; i < this->nr_versiuni; i++)
		{
			in.read((char*)&this->an_versiune[i], sizeof(this->an_versiune[i]));
			in.read((char*)&this->stoc_versiune[i], sizeof(this->stoc_versiune[i]));
			in.read((char*)&this->pret_versiune[i], sizeof(this->pret_versiune[i]));

		}


	}

	friend ostream& operator<<(ostream& out, const Produs& p)
	{
		out << "\n\n";
		out << "\nDenumirea produsului: " << p.denumire;
		out << "\nVeniturile totale de pe urma produsului: " << p.venituri;
		out << "\nNumarul de versiuni ale produsului: " << p.nr_versiuni;
		for (int i = 0; i < p.nr_versiuni; i++)
		{
			out << "\nAnul versiunii " << i + 1 << " : " << p.an_versiune[i];
			out << "\nStocul versiunii " << i + 1 << " : " << p.stoc_versiune[i];
			out << "\nPretul versiunii " << i + 1 << " : " << p.pret_versiune[i];
		}
		out << "\n\n";
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Produs& p)
	{
		out << p.denumire << endl;
		out << p.venituri << endl;
		out << p.nr_versiuni << endl;
		for (int i = 0; i < p.nr_versiuni; i++)
		{
			out << p.an_versiune[i] << endl;
			out << p.stoc_versiune[i] << endl;
			out << p.pret_versiune[i] << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Produs& p)
	{
		delete[] p.denumire;
		delete[] p.an_versiune;
		delete[] p.stoc_versiune;
		delete[] p.pret_versiune;
		cout << "\nInroduceti denumirea produsului: ";
		char aux[100];
		in >> aux;
		p.denumire = new char[strlen(aux) + 1];
		strcpy(p.denumire, aux);
		cout << "\nVeniturile totale de pe urma produsului: ";
		in >> p.venituri;
		cout << "\nNumarul de versiuni ale produsului: ";
		in >> p.nr_versiuni;
		if (p.nr_versiuni < 0)
		{
			p.an_versiune = 0;
			p.stoc_versiune = 0;
			p.pret_versiune = 0;
			p.nr_versiuni = 0;
		}
		else {

			p.an_versiune = new int[p.nr_versiuni];
			p.stoc_versiune = new int[p.nr_versiuni];
			p.pret_versiune = new int[p.nr_versiuni];
			for (int i = 0; i < p.nr_versiuni; i++)
			{
				cout << "\nAnul versiunii " << i + 1 << " : ";
				in >> p.an_versiune[i];
				cout << "\nStocul versiunii " << i + 1 << " : ";
				in >> p.stoc_versiune[i];
				cout << "\nPretul versiunii " << i + 1 << " : ";
				in >> p.pret_versiune[i];
			}
		}
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Produs& p)
	{
		char buffer[200];
		in.getline(buffer, 200);
		delete[] p.denumire;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);

		in >> p.venituri;
		in >> p.nr_versiuni;

		delete[] p.an_versiune;
		delete[] p.stoc_versiune;
		delete[] p.pret_versiune;

		if (p.nr_versiuni < 0)
		{
			p.an_versiune = 0;
			p.stoc_versiune = 0;
			p.pret_versiune = 0;
			p.nr_versiuni = 0;
		}
		else {

			p.an_versiune = new int[p.nr_versiuni];
			p.stoc_versiune = new int[p.nr_versiuni];
			p.pret_versiune = new int[p.nr_versiuni];
			for (int i = 0; i < p.nr_versiuni; i++)
			{
				in >> p.an_versiune[i];
				in >> p.stoc_versiune[i];
				in >> p.pret_versiune[i];
			}
		}

		return in;


	}

	Produs operator++() {
		this->nr_versiuni++;
		return *this;
	}

	Produs operator++(int)
	{
		Produs p = *this;
		this->nr_versiuni++;
		return p;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < this->nr_versiuni)
			return this->pret_versiune[index];
	}

	Produs& operator+=(int marireVenituri)
	{
		this->venituri = this->venituri + marireVenituri;
		return *this;
	}

	Produs& operator+(int marireVenituri)
	{
		Produs rez = *this;
		rez += marireVenituri;
		return rez;
	}

	bool operator==(Produs p)
	{
		if (strcmp(this->denumire, p.denumire) == 0)
			return true;
		else
			return false;
	}

	bool operator>(Produs p)
	{
		if (this->StocTotal() > p.StocTotal())
			return true;
		else
			return false;
	}

	bool operator!()
	{
		if (this->nr_versiuni == 0)
			return true;
		else
			return false;
	}

	explicit operator float()
	{
		return this->StocTotal();
	}

	int StocTotal()
	{
		int stoc_total = 0;
		for (int i = 0; i < this->nr_versiuni; i++)
		{
			stoc_total += this->stoc_versiune[i];
		}
		return stoc_total;
	}

	char* getDenumire()
	{
		return this->denumire;
	}

	void setDenumire()
	{
		delete[] this->denumire;
		char aux[100];
		cout << "\nNoua denumire a produsului: ";
		cin >> aux;
		this->denumire = new char[strlen(aux) + 1];
		strcpy(this->denumire, aux);
	}

	int getNrVersiuni()
	{
		return this->nr_versiuni;
	}

	int* getAnVersiune()
	{
		for (int i = 0; i < this->nr_versiuni; i++)
			cout << "\nPentru versiunea " << i + 1 << " : " << this->an_versiune[i];
	}

	int* getStocVersiune()
	{
		for (int i = 0; i < this->nr_versiuni; i++)
			cout << "\nPentru versiunea " << i + 1 << " : " << this->stoc_versiune[i];
	}

	int* getPretVersiune()
	{
		for (int i = 0; i < this->nr_versiuni; i++)
			cout << "\nPentru versiunea " << i + 1 << " : " << this->pret_versiune[i];
	}
};

class Furnizor
{
private:
	string nume;
	int datorii = 0;
	int nr_resurse = 0;
	char* resurse[100];
	int importanta = 0;

public:

	Furnizor()
	{
		this->nume = "Necunoscut";
		for (int i = 0; i < 100; i++)
		{
			this->resurse[i] = NULL;
		}
	}

	Furnizor(string nume, int datorii)
	{
		this->nume = nume;
		this->datorii = datorii;
		for (int i = 0; i < 100; i++)
		{
			this->resurse[i] = NULL;
		}
	}

	Furnizor(string nume, int datorii, int nr_resurse, char* resurse[], int importanta)
	{
		this->nume = nume;
		this->datorii = datorii;
		this->nr_resurse = nr_resurse;
		if (nr_resurse > 0)
		{
			for (int i = 0; i < this->nr_resurse; i++)
			{
				this->resurse[i] = new char[strlen(resurse[i]) + 1];
				strcpy(this->resurse[i], resurse[i]);
			}
		}
		if (importanta > 5 || importanta < 0)
			this->importanta = 0;
		else
			this->importanta = importanta;
	}

	Furnizor(const Furnizor& f)
	{
		this->nume = f.nume;
		this->datorii = f.datorii;
		this->nr_resurse = f.nr_resurse;
		if (f.nr_resurse > 0)
		{
			for (int i = 0; i < this->nr_resurse; i++)
			{
				this->resurse[i] = new char[strlen(f.resurse[i]) + 1];
				strcpy(this->resurse[i], f.resurse[i]);
			}
		}
		if (f.importanta > 5 || f.importanta < 0)
			this->importanta = 0;
		else
			this->importanta = f.importanta;
	}

	Furnizor& operator=(const Furnizor& f)
	{
		if (this != &f)
		{
			this->nume = f.nume;
			this->datorii = f.datorii;
			this->nr_resurse = f.nr_resurse;
			if (f.nr_resurse > 0)
			{
				for (int i = 0; i < this->nr_resurse; i++)
				{
					if (this->resurse[i] != NULL)
						delete[] this->resurse[i];
					this->resurse[i] = new char[strlen(f.resurse[i]) + 1];
					strcpy(this->resurse[i], f.resurse[i]);
				}
			}
			if (f.importanta > 5 || f.importanta < 0)
				this->importanta = 0;
			else
				this->importanta = f.importanta;
		}

		return *this;
	}

	~Furnizor()
	{
		for (int i = 0; i < this->nr_resurse; i++)
		{
			if (this->resurse[i] != NULL)
				delete[] this->resurse[i];
		}
	}

	void scrieBinar(ofstream& o)
	{

		int lungime2 = strlen(this->nume.c_str()) + 1;
		o.write((char*)&lungime2, sizeof(int));
		o.write(this->nume.c_str(), sizeof(char) * lungime2);

		o.write((char*)&this->datorii, sizeof(this->datorii));

		o.write((char*)&this->nr_resurse, sizeof(this->nr_resurse));

		for (int i = 0; i < this->nr_resurse; i++)
		{
			int lungime = strlen(this->resurse[i]) + 1;//  
			o.write((char*)&lungime, sizeof(int));//  
			o.write(resurse[i], sizeof(char) * lungime);// 
		}

		o.write((char*)&this->importanta, sizeof(this->importanta));




	}
	
	void citireBinar(ifstream& in)
	{


		int lungime2;
		in.read((char*)&lungime2, sizeof(int));
		char s1[2300];
		in.read(s1, lungime2);

		this->nume = s1;

		in.read((char*)&this->datorii, sizeof(this->datorii));

		in.read((char*)&this->datorii, sizeof(this->datorii));
		
		//aceeasi problema ca mai devreme

		in.read((char*)&this->datorii, sizeof(this->datorii));


	}

	friend ostream& operator<<(ostream& out, const Furnizor& f)
	{
		out << "\n\n";
		out << "\nNumele furnizorului este: " << f.nume;
		out << "\nNumarul de datorii avute la furnizor este: " << f.datorii;
		out << "\nNumarul de resurse primite de la furnizor este de: " << f.nr_resurse;
		for (int i = 0; i < f.nr_resurse; i++)
		{
			out << "Numele resursei " << i + 1 << " este: " << f.resurse[i];
		}
		out << "\nImportanta furnizorului este: " << f.importanta;
		if (f.importanta < 3 && f.importanta > 0)
			out << " (mica)";
		else if (f.importanta >= 3)
			out << " (mare)";
		else
			out << " (insignifianta/nespecificata)";
		out << "\n\n";
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Furnizor& f)
	{
		out << f.nume << endl;
		out << f.datorii << endl;
		out << f.nr_resurse << endl;
		for (int i = 0; i < f.nr_resurse; i++)
		{
			out << f.resurse[i]<<endl;
		}

		out << f.importanta << endl;

		return out;
	}

	friend istream& operator>>(istream& in, Furnizor& f)
	{
		for (int i = 0; i < f.nr_resurse; i++)
		{
			if (f.resurse[i] != NULL)
				delete[] f.resurse[i];
		}
		cout << "\nIntroduceti numele furnizorului: ";
		in >> f.nume;
		cout << "\nIntroduceti suma datoriilor avute la furnizor: ";
		in >> f.datorii;
		cout << "\nIntroduceti numarul de resurse primite de la furnizor: ";
		in >> f.nr_resurse;
		for (int i = 0; i < f.nr_resurse; i++)
		{
			char aux[100];
			cout << "\nNumele resurseri " << i + 1 << " este: ";
			in >> aux;
			f.resurse[i] = new char[strlen(aux) + 1];
			strcpy(f.resurse[i], aux);
		}
		cout << "\nPe o scara de la 1 la 4, introduceti importanta furnizorului: ";
		int aux;
		in >> aux;
		if (aux > 0 && aux < 5)
		{
			f.importanta = aux;
		}
		else {
			f.importanta = 1;
		}
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Furnizor& f)
	{
		char buffer1[100];
		in >> buffer1;
		f.nume = buffer1;

		in >> f.datorii;

		in >> f.nr_resurse;

		for (int i = 0; i < 100; i++)
		{
			if (f.resurse[i] != NULL)
			{
				break;
			}
			else {
				delete[] f.resurse[i];
			}
		}

		for (int i = 0; i < f.nr_resurse; i++)
		{
			char aux1[100];
			in >> aux1;
			f.resurse[i] = new char[strlen(aux1) + 1];
			strcpy(f.resurse[i], aux1);
		}
		int aux;
		in >> aux;
		if (aux > 0 && aux < 5)
		{
			f.importanta = aux;
		}
		else {
			f.importanta = 1;
		}

		return in;

	}

	char*& operator[](int index)
	{
		if (index >= 0 && index < this->nr_resurse)
			return this->resurse[index];
	}

	Furnizor& operator+=(int marireDatorii)
	{
		this->datorii = this->datorii + marireDatorii;
		return *this;
	}

	Furnizor& operator+(int marireDatorii)
	{
		Furnizor rez = *this;
		rez += marireDatorii;
		return rez;
	}

	Furnizor operator++() {
		if (this->importanta < 5)
			this->importanta++;
		else
			cout << "\nFurnizorul selectat are deja o importanta maxima!";
		return *this;
	}

	Furnizor operator++(int)
	{
		Furnizor f = *this;
		if (this->importanta < 5)
			this->importanta++;
		else
			cout << "\nFurnizorul selectat are deja o importanta maxima!";
		return f;
	}

	bool operator==(Furnizor f)
	{
		return this->nume == f.nume;
	}

	bool operator>(Furnizor f)
	{
		if (this->importanta > f.importanta)
			return true;
		else
			return false;
	}

	bool operator!()
	{
		if (this->datorii == 0)
			return true;
		else
			return false;
	}

	explicit operator float()
	{
		return this->datorii;
	}

	int getImportanta()
	{
		return this->importanta;
	}

	int getDatorii()
	{
		return this->datorii;
	}

};

class Investitor
{
protected:
	char* nume;
	int vechime = 0;
	int* investitie_anuala = NULL;
	int numar_actiuni = 0;

public:
	Investitor()
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
	}

	Investitor(const char* nume, int numar_actiuni)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->numar_actiuni = numar_actiuni;
	}

	Investitor(char* nume, int vechime, int* investitie_anuala, int numar_actiuni)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->vechime = vechime;
		this->investitie_anuala = new int[this->vechime];
		for (int i = 0; i < this->vechime; i++)
		{
			this->investitie_anuala[i] = investitie_anuala[i];
		}
		this->numar_actiuni = numar_actiuni;
	}

	Investitor(const Investitor& i)
	{
		this->nume = new char[strlen(i.nume) + 1];
		strcpy(this->nume, i.nume);
		this->vechime = i.vechime;
		this->investitie_anuala = new int[this->vechime];
		for (int j = 0; j < this->vechime; j++)
		{
			this->investitie_anuala[j] = i.investitie_anuala[j];
		}
		this->numar_actiuni = i.numar_actiuni;
	}

	Investitor& operator=(const Investitor& i)
	{
		if (this != &i)
		{
			if (this->nume != NULL)
				delete[] this->nume;
			if (this->investitie_anuala != NULL)
				delete[] this->investitie_anuala;
			this->nume = new char[strlen(i.nume) + 1];
			strcpy(this->nume, i.nume);
			this->vechime = i.vechime;
			this->investitie_anuala = new int[this->vechime];
			for (int j = 0; j < this->vechime; j++)
			{
				this->investitie_anuala[j] = i.investitie_anuala[j];
			}
			this->numar_actiuni = i.numar_actiuni;
		}
		return *this;
	}

	~Investitor()
	{
		if (this->nume != NULL)
			delete[] this->nume;
		if (this->investitie_anuala != NULL)
			delete[] this->investitie_anuala;
	}

	void scrieBinar(ofstream& o)
	{

		int lungime = strlen(this->nume) + 1; 
		o.write((char*)&lungime, sizeof(int));  
		o.write(nume, sizeof(char) * lungime);

		o.write((char*)&this->vechime, sizeof(this->vechime));

		for (int i = 0; i < this->vechime; i++)
		{
			o.write((char*)&this->investitie_anuala[i], sizeof(this->investitie_anuala[i]));

		}

		o.write((char*)&this->numar_actiuni, sizeof(this->numar_actiuni));


	}

	void citireBinar(ifstream& in)
	{
		int lungime;
		in.read((char*)&lungime, sizeof(int));  
		char s[2300];
		in.read(s, lungime);

		char nume_nou[100];
		cout << "Noul nume al angajatului";
		cin >> nume_nou;
		this->nume = nume_nou;

		in.read((char*)&this->vechime, sizeof(this->vechime));

		delete[]  this->investitie_anuala;
		this->investitie_anuala = new int[this->vechime];
		for (int i = 0; i < this->vechime; i++) {
			in.read((char*)&this->investitie_anuala[i], sizeof(this->investitie_anuala[i]));

		}

		in.read((char*)&this->numar_actiuni, sizeof(this->numar_actiuni));


	}

	friend ostream& operator<<(ostream& out, const Investitor& i)
	{
		out << "\n\n";
		out << "\nNume investitor: " << i.nume;
		out << "\nVechime in organizatie: " << i.vechime;
		for (int j = 0; j < i.vechime; j++)
		{
			out << "\nInvestitie in anul " << j + 1 << " : " << i.investitie_anuala[j];
		}
		out << "\nNumar de actiuni in organizatie: " << i.numar_actiuni;
		out << "\n\n";

		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Investitor& i)
	{
		out << i.nume << endl;
		out << i.vechime << endl;
		for (int j = 0; j < i.vechime; j++)
		{
			out << i.investitie_anuala[j] << endl;
		}
		out << i.numar_actiuni << endl;

		return out;
	}

	friend istream& operator>>(istream& in, Investitor& i)
	{
		delete[] i.nume;
		cout << "\nIntroduceti numele invetitorului: ";
		char aux[100];
		in >> aux;
		i.nume = new char[strlen(aux) + 1];
		strcpy(i.nume, aux);
		cout << "\nIntroduceti vechimea acestuia in organizatie: ";
		in >> i.vechime;
		i.investitie_anuala = new int[i.vechime];
		for (int j = 0; j < i.vechime; j++)
		{
			cout << "\nIntroduceti suma investitia in anul " << j + 1 << " : ";
			in >> i.investitie_anuala[j];
		}
		cout << "\nIntroduceti numar de actiuni ale acestuia in organizatie: ";
		in >> i.numar_actiuni;

		return in;
	}

	friend ifstream& operator>>(ifstream& in, Investitor& i)
	{
		char buffer[200];
		in>>buffer;
		delete[] i.nume;
		i.nume = new char[strlen(buffer) + 1];
		strcpy(i.nume, buffer);

		in >> i.vechime;

		i.investitie_anuala = new int[i.vechime];

		for (int j = 0; j < i.vechime; j++)
		{
			in >> i.investitie_anuala[j];
		}

		in >> i.numar_actiuni;

		return in;
	}

	Investitor operator++() {
		this->numar_actiuni++;
		return *this;
	}

	Investitor operator++(int)
	{
		Investitor i = *this;
		this->numar_actiuni++;
		return i;
	}

	Investitor& operator+=(int marireNumarActiuni)
	{
		this->numar_actiuni = this->numar_actiuni + marireNumarActiuni;
		return *this;
	}

	Investitor& operator+(int marireNumarActiuni)
	{
		Investitor rez = *this;
		rez += marireNumarActiuni;
		return rez;
	}

	bool operator==(Investitor i)
	{
		return this->numar_actiuni == i.numar_actiuni;
	}

	bool operator>(Investitor i)
	{
		if (this->numar_actiuni > i.numar_actiuni)
			return true;
		else
			return false;
	}

	bool operator!()
	{
		if (this->numar_actiuni == 0)
			return true;
		else
			return false;
	}

	explicit operator float()
	{
		return this->vechime;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < this->vechime)
			return this->investitie_anuala[index];
	}

	char* getNume()
	{
		return this->nume;
	}

	int getVechime()
	{
		return this->vechime;
	}
};

class Proprietate
{
private:
	string adresa = "N/A";
	string tip = "N/A";
	char* departament = NULL;
	int numar_camere = 0;
	int* mp_camera = NULL;
	bool tip_proprietate = 0;
	int valoare = 0;

public:

	Proprietate()
	{
		this->departament = new char[strlen("N/A") + 1];
		strcpy(this->departament, "N/A");
	}

	Proprietate(string adresa, string tip)
	{
		this->adresa = adresa;
		this->tip = tip;
		this->departament = new char[strlen("N/A") + 1];
		strcpy(this->departament, "N/A");
	}

	Proprietate(string adresa, string tip, char* departament, bool tip_proprietate, int valoare)
	{
		this->adresa = adresa;
		this->tip = tip;
		this->departament = new char[strlen(departament) + 1];
		strcpy(this->departament, departament);
		this->numar_camere = numar_camere;
		this->mp_camera = new int[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++)
		{
			this->mp_camera[i] = mp_camera[i];
		}
		this->tip_proprietate = tip_proprietate;
		if (this->tip_proprietate == 0)
		{
			this->valoare = valoare;
		}
		else
		{
			this->valoare = 0;
		}
	}

	Proprietate(const Proprietate& pr)
	{
		if (this->departament != NULL)
			delete[] this->departament;
		this->adresa = pr.adresa;
		this->tip = pr.tip;
		this->departament = new char[strlen(pr.departament) + 1];
		strcpy(this->departament, pr.departament);
		this->numar_camere = pr.numar_camere;
		this->mp_camera = new int[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++)
		{
			this->mp_camera[i] = pr.mp_camera[i];
		}
		this->tip_proprietate = pr.tip_proprietate;
		if (this->tip_proprietate == 0)
		{
			this->valoare = pr.valoare;
		}
		else
		{
			this->valoare = 0;
		}
	}

	Proprietate& operator=(const Proprietate& pr)
	{
		if (this != &pr)
		{
			if (this->departament != NULL)
				delete[] this->departament;
			if (this->mp_camera != NULL)
				delete[] this->mp_camera;
			this->adresa = pr.adresa;
			this->tip = pr.tip;
			this->departament = new char[strlen(pr.departament) + 1];
			this->numar_camere = pr.numar_camere;
			this->mp_camera = new int[this->numar_camere];
			for (int i = 0; i < this->numar_camere; i++)
			{
				this->mp_camera[i] = pr.mp_camera[i];
			}
			strcpy(this->departament, pr.departament);
			this->tip_proprietate = pr.tip_proprietate;
			if (this->tip_proprietate == 0)
			{
				this->valoare = pr.valoare;
			}
			else
			{
				this->valoare = 0;
			}
		}

		return *this;
	}

	~Proprietate()
	{
		if (this->departament != NULL)
			delete[] this->departament;
		if (this->mp_camera != NULL)
			delete[] this->mp_camera;
	}

	void scrieBinar(ofstream& o)
	{

		int lungime2 = strlen(this->adresa.c_str()) + 1;  
		o.write((char*)&lungime2, sizeof(int));
		o.write(this->adresa.c_str(), sizeof(char) * lungime2);

		int lungime3 = strlen(this->tip.c_str()) + 1;
		o.write((char*)&lungime3, sizeof(int));
		o.write(this->tip.c_str(), sizeof(char) * lungime3);

		int lungime = strlen(this->departament) + 1;
		o.write((char*)&lungime, sizeof(int));
		o.write(departament, sizeof(char) * lungime);

		o.write((char*)&this->numar_camere, sizeof(this->numar_camere));

		for (int i = 0; i < this->numar_camere; i++)
		{

			o.write((char*)&this->mp_camera[i], sizeof(this->mp_camera[i]));

		}

		o.write((char*)&this->tip_proprietate, sizeof(this->tip_proprietate));

		o.write((char*)&this->valoare, sizeof(this->valoare));


	}

	void citireBinar(ifstream& in)
	{

		int lungime2;// a 
		in.read((char*)&lungime2, sizeof(int));//  
		char s1[2300];// 
		in.read(s1, lungime2);//

		this->adresa = s1;

		int lungime3;// a 
		in.read((char*)&lungime3, sizeof(int));//  
		char s2[2300];// 
		in.read(s2, lungime3);//

		this->tip = s2;

		int lungime;// a 
		in.read((char*)&lungime, sizeof(int));//  
		char s[2300];// 
		in.read(s, lungime);

		char departament_nou[100];
		cout << "Noul nume al angajatului";
		cin >> departament_nou;
		this->departament = departament_nou;

		in.read((char*)&this->numar_camere, sizeof(this->numar_camere));

		delete[]  this->mp_camera;
		this->mp_camera = new int[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			in.read((char*)&this->mp_camera[i], sizeof(this->mp_camera[i]));

		}

		in.read((char*)&this->tip_proprietate, sizeof(this->tip_proprietate));

		in.read((char*)&this->valoare, sizeof(this->valoare));



	}

	friend ostream& operator<<(ostream& out, const Proprietate& pr)
	{
		out << "\n\n";
		out << "\nAdresa cladirii: " << pr.adresa;
		out << "\nTipul cladirii: " << pr.tip;
		out << "\nDepartamentul ce foloseste cladirea: " << pr.departament;
		out << "\nNumar de camere al proprietatii: " << pr.numar_camere;
		for (int i = 0; i < pr.numar_camere; i++)
		{
			out << "\nMetrii patrati ai camerei " << i + 1 << " : " << pr.mp_camera[i];
		}
		out << "\nTipul de proprietate al cladirii: ";
		if (pr.tip_proprietate == 0)
		{
			out << "Detinuta";
			out << "\nValoarea cladirii: " << pr.valoare;
		}
		else {
			out << "Inchiriata";
			out << "\nCladirea nu are o valoare";
		}

		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Proprietate& pr)
	{
		out << pr.adresa << endl;
		out << pr.tip << endl;
		out << pr.departament << endl;
		out << pr.numar_camere << endl;
		for (int i = 0; i < pr.numar_camere; i++)
		{
			out << pr.mp_camera[i] << endl;
		}
		out << pr.tip_proprietate << endl;
		out << pr.valoare << endl;

		return out;
	}

	friend istream& operator>>(istream& in, Proprietate& pr)
	{
		cout << "\nAdresa cladirii: ";
		in >> pr.adresa;
		cout << "\nTipul cladirii: ";
		in >> pr.tip;
		cout << "\nDepartamentul ce foloseste cladirea: ";
		char aux[100];
		in >> aux;
		pr.departament = new char[strlen(aux) + 1];
		strcpy(pr.departament, aux);
		cout << "\nNumar de camere al proprietatii: ";
		in >> pr.numar_camere;
		pr.mp_camera = new int[pr.numar_camere];
		for (int i = 0; i < pr.numar_camere; i++)
		{
			cout << "\nMetrii patrati ai camerei " << i + 1 << " : ";
			in >> pr.mp_camera[i];
		}
		cout << "\nTipul de proprietate al cladirii: ";
		in >> pr.tip_proprietate;
		if (pr.tip_proprietate == 0)
		{
			cout << "\nIntroduceti valoarea cladirii: ";
			in >> pr.valoare;
		}
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Proprietate& pr)
	{
		char buffer1[100];
		in.getline(buffer1, 200);
		pr.adresa = buffer1;

		char buffer2[100];
		in.getline(buffer2, 200);
		pr.tip = buffer1;

		char buffer[200];
		in.getline(buffer, 200);
		delete[] pr.departament; 
		pr.departament = new char[strlen(buffer) + 1];
		strcpy(pr.departament, buffer);

		in >> pr.numar_camere;

		pr.mp_camera = new int[pr.numar_camere];

		for (int i = 0; i < pr.numar_camere; i++)
		{
			in >> pr.mp_camera[i];
		}

		in>>pr.tip_proprietate;

		in >> pr.valoare;

		return in;
	}

	Proprietate& operator+=(int marireValoare)
	{
		if (this->tip_proprietate == 0)
		{
			this->valoare = this->valoare + marireValoare;
		}
		else
		{
			cout << "\nProprietatea este inchiriata, nu s-a putut modifica valoarea";
		}
		return *this;
	}

	Proprietate& operator+(int marireValoare)
	{
		Proprietate rez = *this;
		rez += marireValoare;
		return rez;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < this->numar_camere)
			return this->mp_camera[index];
	}

	Proprietate operator++() {
		this->numar_camere++;
		return *this;
	}

	Proprietate operator++(int)
	{
		Proprietate pr = *this;
		this->numar_camere++;
		return pr;
	}

	bool operator==(Proprietate pr)
	{
		if (this->valoare == pr.valoare)
			return true;
		else
			return false;
	}

	bool operator>(Proprietate pr)
	{
		if (this->valoare > pr.valoare)
			return true;
		else
			return false;
	}

	bool operator!()
	{
		if (this->valoare == 0)
			return true;
		else
			return false;
	}

	explicit operator float()
	{
		return this->valoare;
	}


};

//exemplificare clasa compusa(de tip has-a)
class Contabilitate
{
public:
	Produs p;
	Furnizor f;	

};

//exemplificare clasa derivata(de tip is-a)

class Contabil : Angajat
{
	string rol;

public:

	Contabil() : Angajat()
	{
		this->rol = "nedefinit";
	}

	~Contabil()
	{
		cout << "Destructor";
	}
};

class Client {
public:
	virtual void abs() = 0;
	virtual void abs1() = 0;
};

class Clientela : public Client
{
public:
	void abs()
	{
		cout << 2;
	}

	void abs1()
	{
		cout << 3;
	}
};



class OperareFisiere {

public:

//Angajat

	void scriereBinarAngajat(ofstream& fout, Angajat a)
	{
		a.scrieBinar(fout);
	}

	void citireBinarAngajat(ifstream& fin, Angajat& a)
	{
		a.citireBinar(fin);
	}

//Produs
	void scriereBinarProdus(ofstream& fout, Produs p)
	{
		p.scrieBinar(fout);
	}

	void citireBinarProdus(ifstream& fin, Produs& p)
	{
		p.citireBinar(fin);
	}

//Furnizor
	void scriereBinarFurnizor(ofstream& fout, Furnizor f)
	{
		f.scrieBinar(fout);
	}

	void citireBinarFurnizor(ifstream& fin, Furnizor& f)
	{
		f.citireBinar(fin);
	}

//Investitor
	void scriereBinarInvestitor(ofstream& fout, Investitor i)
	{
		i.scrieBinar(fout);
	}

	void citireBinarInvestitor(ifstream& fin, Investitor& i)
	{
		i.citireBinar(fin);
	}

//Proprietate
	void scriereBinarProprietate(ofstream& fout, Proprietate pr)
	{
		pr.scrieBinar(fout);
	}

	void citireBinarProprietate(ifstream& fin, Proprietate& pr)
	{
		pr.citireBinar(fin);
	}
};

class Meniu {

public:
	static void afisareMeniu()
	{
		system("cls");
		cout << "\nPe ce clasa ai dori sa lucrezi?";
		cout << "\n\n(1) Angajat";
		cout << "\n(2) Produs";
		cout << "\n(3) Furnizor";
		cout << "\n(4) Investitor";
		cout << "\n(5) Proprietate";
		cout << "\n(6) Contabilitate\n";
	}
};

//class Rapoarte {
//	void CreareIerarhieSalariati(ofstream& fout, Angajat a)
//	{
//		
//
//	}
//
//};

int Angajat::nr_bonusuri = 2;
int Angajat::nr_angajati = 1;


int main()
{
	system("cls");
	int sw;
	Meniu::afisareMeniu();
	cin >> sw;
	system("cls");
	switch (sw)
	{
	case 1:
	{
		int sw1;
		cout << "\nCe doresti sa faci pe aceasta clasa?";
		cout << "\n(1)Diverse operatii folosind metodele si supraincarcarile implementate(de la faza 1)";
		cout << "\n(2)Adaugare obiect in fisier(txt)";
		cout << "\n(3)Citire obiect din fisier(txt)";
		cout << "\n(4)Adaugare obiect in fisier(bin)";
		cout << "\n(5)Citire obiect din fisier(bin)";
		cout << "\n(6)Ierarhie angajati";
		cout << "\n(7)Map \n";
		cin >> sw1;
		OperareFisiere opfisier;
		switch (sw1)
		{
		case 1:
		{
			Angajat a4;
			Angajat a1;
			Angajat a2("viorel", 2000);
			cout << "\nAngajatul 2\n\n" << a2;
			Angajat a3;
			a3 = a2;
			cout << "\nEgalam angajatul a3 cu a2\n";
			cout << a3;
			cout << "\nIi marim salariul angajatului a2 cu operatorul +=\n";
			a2 += 100;
			cout << a2;
			cout << "\nComparam a1 si a4 prin operatorul==\n";
			if (a1 == a4)
			{
				cout << "\nLucreaza in acelasi departament\n";
			}
			else
			{
				cout << "\nNu lucreaza in acelasi departament";
			}
			cout << "\nScriem angajatul a1";
			cin >> a1;
			cout << "\nComparam a3 si a2 prin operatorul>\n";
			if (a1 > a3)
			{
				cout << "\nA1 are salar mai mare decat A3\n";
			}
			else
			{
				cout << "\nA1 are salar mai mic decat A3\n";
			}
			if (!a1)
			{
				cout << "\nAngajatul a1 mai are zile de concediu!\n";
			}
			else
			{
				cout << "\nAngajatul a1 nu mai are zile de concediu :(\n";
			}
			cout << "\nIi crestem zilele de concediu angajatului a1\n";
			a1++;
			++a1;
			cout << (double)a1;
			cout << "\nCare e primul bonus al angajatului a1?\n";
			cout << a1[0];
			cin.get();
			cin.get();
			main();
			break;
		}
		case 2:
		{
			Angajat ang11;
			cin >> ang11;
			ofstream fout;
			fout.open("angajati.txt", ios::app);
			if (fout.is_open()) {
				fout << ang11;
			}
			fout.close();
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 3:
		{
			vector <Angajat> ang;
			ifstream fin("angajati.txt");
			Angajat ang11;
			fin >> ang11;
			do {
				ang.push_back(ang11);
				Angajat ang11;
			} while (fin >> ang11);
			fin.close();
			for (int i = 0; i < ang.size(); ++i)
			{
				cout << ang[i] << '\n';
			}
			cin.get();
			cin.get();
			main();
			break;
		}
		case 5:
		{
			Angajat ang13;
			ifstream fin2;
			fin2.open("angajati.bin", ios::binary | ios::in);
			while (fin2>>ang13) {
				opfisier.citireBinarAngajat(fin2, ang13);
				fin2.close();
			}
			cout << ang13;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 4:
		{
			Angajat ang12;
			ofstream fout2;
			fout2.open("angajati.bin", ios::binary | ios::app);
			if (fout2.is_open()) {
				opfisier.scriereBinarAngajat(fout2, ang12);
			}
			fout2.close();
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main(); 
			break;
		}
		case 6:
		{
			Angajat::IerarhieSalariati();
			cin.get();
			cin.get();
			main();
			break;
		}
		case 7:
		{
			Angajat ang1("viorel", 1000);
			Angajat ang2("vicentiu", 2000);
			Angajat ang3("denis", 3000);
			Angajat ang4("mihaita", 12000);
			Angajat ang5("Octavian", 800);
			map <int, Angajat> map;
			map.insert(pair<int, Angajat>(10, ang1));
			map.insert(pair<int, Angajat>(11, ang2));
			map.insert(pair<int, Angajat>(12, ang3));
			map.insert(pair<int, Angajat>(13, ang4));
			map.insert(pair<int, Angajat>(14, ang5));
			cout << "Numar de elemente in map: ";
			cout << map.size() << endl;
			/*map<int, Angajat>::iterator it;
			for (it = map.begin(); it != map.end(); it++)
			{
				cout << "\nCheia de identificare a " << it<< " este: " << it->first<<endl;
				cout << "\n Valoarea este: " << it -> second<<endl;
			}*/

			cin.get();
			cin.get();
			main();
			break;
		}
		default:
		{
			char rasp[3];
			cout << "\nNu ai introdus o optiune valida. Doresti sa te intorci la meniu?(Da/Nu)\n";
			cin >> rasp;
			if (strcmp(rasp, "Da") == 0 || strcmp(rasp, "da") == 0 || strcmp(rasp, "DA") == 0 || strcmp(rasp, "dA") == 0)
			{
				main();
			}
			else
			{
				break;
			}
		}
		}
		break;
	}
	case 2:
	{
		int sw1;
		cout << "\nCe doresti sa faci pe aceasta clasa?";
		cout << "\n(1)Diverse operatii folosind metodele si supraincarcarile implementate(de la faza 1)";
		cout << "\n(2)Adaugare obiect in fisier(txt)";
		cout << "\n(3)Citire obiect din fisier(txt)";
		cout << "\n(4)Adaugare obiect in fisier(bin)";
		cout << "\n(5)Citire obiect din fisier(bin)\n";
		cin >> sw1;
		OperareFisiere opfisier;
		switch (sw1)
		{
		case 1:
		{
			Produs p4;
			Produs p1;
			Produs p2("Telefon", 20000);
			cout << "\nProdusul p2\n\n" << p2;
			Produs p3;
			p3 = p2;
			cout << "\nEgalam produsul p3 cu p2\n";
			cout << p3;
			cout << "\nMarim veniturile produsului p2 cu operatorul +=\n";
			p2 += 100;
			cout << p2;
			cout << "\nComparam p1 si p4 prin operatorul==\n";
			if (p1 == p4)
			{
				cout << "\nE acelasi produs\n";
			}
			else
			{
				cout << "\nNu e acelasi produs\n";
			}
			cout << "\nScriem produsul p1";
			cin >> p1;
			cout << "\nComparam p3 si p2 prin operatorul>\n";
			if (p1 > p3)
			{
				cout << "\nP1 are stoc total mai mare decat p3\n";
			}
			else
			{
				cout << "\nP1 are stoc total mai mic decat p3\n";
			}
			if (!p1)
			{
				cout << "\nProdusul p1 are minim 0 versiune\n";
			}
			else
			{
				cout << "\nProdusul p1 nu are versiuni :(\n";
			}
			cout << "\nIi crestem numarul de versiuni produsului p1\n";
			p1++;
			++p1;
			cout << (float)p1;
			cout << "\nCare e pretul primei versiuni a produsului p1?\n";
			cout << p1[0];
			cin.get();
			cin.get();
			main();
			break;
		}
		case 2:
		{
			Produs prod11;
			cin >> prod11;
			ofstream fout;
			fout.open("produse.txt", ios::app);
			if (fout.is_open()) {
				fout << prod11;
				fout.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 3:
		{
			vector <Produs> prod;
			Produs prod11;
			ifstream fin("produse.txt");
			while (fin >> prod11) {
				prod.push_back(prod11);
			}
			fin.close();
			for (int i = 0; i < prod.size(); ++i)
				cout << prod[i] << '\n';
			cin.get();
			cin.get();
			main();
			break;
		}
		case 4:
		{
			Produs prod12;
			ofstream fout2;
			fout2.open("produse.bin", ios::binary | ios::out);
			if (fout2.is_open()) {
				opfisier.scriereBinarProdus(fout2, prod12);
				fout2.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 5:
		{
			Produs prod13;
			ifstream fin2;
			fin2.open("produse.bin", ios::binary | ios::in);
			while (fin2 >> prod13) {
				opfisier.citireBinarProdus(fin2, prod13);
				fin2.close();
			}
			cout << prod13;
			cin.get();
			cin.get();
			main();
			break;
		}
		default:
		{
			char rasp[3];
			cout << "\nNu ai introdus o optiune valida. Doresti sa te intorci la meniu?(Da/Nu)\n";
			cin >> rasp;
			if (strcmp(rasp, "Da") == 0 || strcmp(rasp, "da") == 0 || strcmp(rasp, "DA") == 0 || strcmp(rasp, "dA") == 0)
			{
				main();
			}
			else
			{
				break;
			}
		}
		}
		break;
	}
	case 3:
	{
		int sw1;
		cout << "\nCe doresti sa faci pe aceasta clasa?";
		cout << "\n(1)Diverse operatii folosind metodele si supraincarcarile implementate(de la faza 1)";
		cout << "\n(2)Adaugare obiect in fisier(txt)";
		cout << "\n(3)Citire obiect din fisier(txt)";
		cout << "\n(4)Adaugare obiect in fisier(bin)";
		cout << "\n(5)Citire obiect din fisier(bin)";
		cout << "\n(6)Medie datorii in functie de fiecare nivel de importanta\n";
		cin >> sw1;
		OperareFisiere opfisier;
		switch (sw1)
		{
		case 1:
		{
			Furnizor f4;
			Furnizor f1;
			Furnizor f2("Lemne_SRL", 5500);
			cout << "\nFurnizorul f2\n\n" << f2;
			Furnizor f3;
			f3 = f2;
			cout << "\nEgalam furnizorul f3 cu f2\n";
			cout << f3;
			cout << "\nMarim datoriile catre furnizorul f2 cu operatorul +=\n";
			f2 += 100;
			cout << f2;
			cout << "\nComparam f1 si f4 prin operatorul==\n";
			if (f1 == f4)
			{
				cout << "\nf1 si f4 au acelasi nume\n";
			}
			else
			{
				cout << "\nf1 si f4 nu au  au acelasi nume\n";
			}
			cout << "\nScriem furnizorul f1";
			cin >> f1;
			cout << "\nComparam f3 si f1 prin operatorul>\n";
			if (f1 > f3)
			{
				cout << "\nF1 are o importanta mai mare decat f3\n";
			}
			else
			{
				cout << "\nF1 are o importanta mai mica decat f3\n";
			}
			if (!f1)
			{
				cout << "\nExista datorii la furnizor\n";
			}
			else
			{
				cout << "\nNu exista datorii la furnizor!\n";
			}
			cout << "\nIi crestem importanta furnizorului f1\n";
			f1++;
			++f1;
			cout << (float)f1;
			cout << "\nCare e numele primei resurse a furnizorului f1?\n";
			cout << f1[0];
			cin.get();
			cin.get();
			main();
			break;
		}
		case 2:
		{
			Furnizor fur11;
			cin >> fur11;
			ofstream fout;
			fout.open("furnizori.txt", ios::app);
			if (fout.is_open()) {
				fout << fur11;
				fout.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 3:
		{
			vector <Furnizor> fur;
			Furnizor fur11;
			ifstream fin("furnizori.txt");
			while (fin >> fur11) {
				fur.push_back(fur11);
			}
			cout << fur.size() << "\n";
			fin.close();
			for (int i = 0; i < fur.size(); ++i)
				cout << fur[i] << '\n';
			cin.get();
			cin.get();
			main();
			break;
		}
		case 4:
		{
			Furnizor fur12;
			ofstream fout2;
			fout2.open("furnizori.bin", ios::binary | ios::out);
			if (fout2.is_open()) {
				opfisier.scriereBinarFurnizor(fout2, fur12);
				fout2.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 5:
		{
			Furnizor fur13;
			ifstream fin2;
			fin2.open("furnizori.bin", ios::binary | ios::in);
			while (fin2 >> fur13) {
				opfisier.citireBinarFurnizor(fin2, fur13);
				fin2.close();
			}
			cout << fur13;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 6:
		{
			vector <Furnizor> fur;
			Furnizor fur11;
			ifstream fin("furnizori.txt");
			fin >> fur11;
			do {
				fur.push_back(fur11);
				Angajat ang11;
			} while (fin >> fur11);
			fin.close();
			/*for (int i = 0; i < fur.size(); i++)
			{
				cout << fur[i] << "\n";
			}*/
			int cnt[4] = { 0, 0, 0, 0 };
			int sum[4] = { 0, 0, 0, 0 };
			for (int i = 0; i < fur.size(); i++)
			{
				if (fur[i].getImportanta() == 1)
				{
					cnt[0]++;
					sum[0] = sum[0] + fur[i].getDatorii();
				}
				else if (fur[i].getImportanta() == 2)
				{
					cnt[1]++;
					sum[1] = sum[1] + fur[i].getDatorii();
				}
				else if (fur[i].getImportanta() == 3)
				{
					cnt[2]++;
					sum[2] = sum[2] + fur[i].getDatorii();
				}
				else if (fur[i].getImportanta() == 4)
				{
					cnt[3]++;
					sum[3] = sum[3] + fur[i].getDatorii();
				}
			}
			
			ofstream fout("DatoriiImportanta.txt");
			for (int i = 0; i < 4; i++)
			{
				fout << cnt[i] << "\n";
				fout << sum[i] << "\n";
				if (cnt[i] == 0)
				{
					fout << 0<<"\n";
				}
				else
				{
					fout << sum[i] / cnt[i] << "\n";
				}
					
			}
			fout.close();
			for (int i = 0; i < 4; i++)
			{
				cout << "\nNumar de furnizori cu importanta " << i + 1 << " : ";
				cout << cnt[i] << "\n";
				cout << "\nSuma datoriilor pentru furnizori cu importanta " << i + 1 << " : ";
				cout << sum[i] << "\n";
				cout << "\nMedia datoriilor pentru furnizorii cu importanta " << i + 1 << " : ";
				if (cnt[i] == 0)
				{
					cout << 0<<"\n";
				}
				else
				{
					cout << sum[i] / cnt[i] << "\n";
				}
			}
		}
		default:
		{
			char rasp[3];
			cout << "\nNu ai introdus o optiune valida. Doresti sa te intorci la meniu?(Da/Nu)\n";
			cin >> rasp;
			if (strcmp(rasp, "Da") == 0 || strcmp(rasp, "da") == 0 || strcmp(rasp, "DA") == 0 || strcmp(rasp, "dA") == 0)
			{
				main();
			}
			else
			{
				break;
			}
		}
		}
		break;
	}
	case 4:
	{
		int sw1;
		cout << "\nCe doresti sa faci pe aceasta clasa?";
		cout << "\n(1)Diverse operatii folosind metodele si supraincarcarile implementate(de la faza 1)";
		cout << "\n(2)Adaugare obiect in fisier(txt)";
		cout << "\n(3)Citire obiect din fisier(txt)";
		cout << "\n(4)Adaugare obiect in fisier(bin)";
		cout << "\n(5)Citire obiect din fisier(bin)";
		cout << "\n(6)Cei mai vechi investitori\n";
		cin >> sw1;
		OperareFisiere opfisier;
		switch (sw1)
		{
		case 1:
		{
			Investitor i4;
			Investitor i1;
			Investitor i2("Tiriac", 105);
			cout << "\nInvestitor i2\n\n" << i2;
			Investitor i3;
			i3 = i2;
			cout << "\nEgalam investitor i3 cu i2\n";
			cout << i3;
			cout << "\nMarim numarul de actiuni al investitorului i2 cu operatorul +=\n";
			i2 += 100;
			cout << i2;
			cout << "\nComparam i1 si i4 prin operatorul==\n";
			if (i1 == i4)
			{
				cout << "\nAu acelasi numar de actiuni\n";
			}
			else
			{
				cout << "\nNu au acelasi numar de actiuni\n";
			}
			cout << "\nScriem investitorul i1";
			cin >> i1;
			cout << "\nComparam i3 si i1 prin operatorul>\n";
			if (i1 > i3)
			{
				cout << "\nI1 are un numar de actiuni mai mare decat i3\n";
			}
			else
			{
				cout << "\ni1 are un numar de actiuni mai mic decat i3\n";
			}
			if (!i1)
			{
				cout << "\nInvestitorul i1 are actiuni\n";
			}
			else
			{
				cout << "\nInvestitorul i1 nu are actiuni :(\n";
			}
			cout << "\nIi crestem numarul de actiuni investitorului i1\n";
			i1++;
			++i1;
			cout << (float)i1;
			cout << "\nCare e suma investita a investitorului in primul an f1?\n";
			cout << i1[0];
			cin.get();
			cin.get();
			main();
			break;
		}
		case 2:
		{
			Investitor inv11;
			cin >> inv11;
			ofstream fout;
			fout.open("investitori.txt", ios::app);
			if (fout.is_open()) {
				fout << inv11;
				fout.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 3:
		{
			vector <Investitor> inv;
			Investitor inv11;
			ifstream fin("investitori.txt");
			while (fin >> inv11) {
				inv.push_back(inv11);
			}
			cout << inv.size() << "\n";
			fin.close();
			for (int i = 0; i < inv.size(); ++i)
				cout << inv[i] << '\n';
			cin.get();
			cin.get();
			main();
			break;
		}
		case 4:
		{
			Investitor inv12;
			ofstream fout2;
			fout2.open("investitori.bin", ios::binary | ios::out);
			if (fout2.is_open()) {
				opfisier.scriereBinarInvestitor(fout2, inv12);
				fout2.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 5:
		{
			Investitor inv13;
			ifstream fin2;
			fin2.open("investitori.bin", ios::binary | ios::in);
			while (fin2 >> inv13) {
				opfisier.citireBinarInvestitor(fin2, inv13);
				fin2.close();
			}
			cout << inv13;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 6:
		{
			vector <Investitor> inv;
			Investitor inv11;
			ifstream fin("investitori.txt");
			fin >> inv11;
			do {
				inv.push_back(inv11);
				Investitor inv11;
			} while (fin >> inv11);
			fin.close();
			int* v = new int[inv.size()];
			string* vec = new string[inv.size()];
			ofstream fout("InvestitoriVechime.txt");
			for (int i = 0; i < inv.size(); i++)
			{
				vec[i] = inv[i].getNume();
				v[i] = inv[i].getVechime();
			}
			for (int i = 0; i < inv.size() - 1; i++)
			{
				for (int j = i + 1; j < inv.size(); j++)
				{
					if (v[j] > v[i])
					{
						int aux = v[i];
						v[i] = v[j];
						v[j] = aux;
						string aux1 = vec[i];
						vec[i] = vec[j];
						vec[j] = aux1;
					}
				}
			}
			for (int i = 0; i < inv.size(); i++)
			{
				fout << vec[i] << "\n";
				fout << v[i] << "\n";
			}
			fout.close();
			for (int i = 0; i < inv.size(); i++)
			{
				cout << "Nume: ";
				cout << vec[i] << "\n";
				cout << "Vechime: ";
				cout << v[i] << "\n";
			}
			cin.get();
			cin.get();
			main();
			break;
		}
		default:
		{
			char rasp[3];
			cout << "\nNu ai introdus o optiune valida. Doresti sa te intorci la meniu?(Da/Nu)\n";
			cin >> rasp;
			if (strcmp(rasp, "Da") == 0 || strcmp(rasp, "da") == 0 || strcmp(rasp, "DA") == 0 || strcmp(rasp, "dA") == 0)
			{
				main();
			}
			else
			{
				break;
			}
		}
		}
		break;
	}
	case 5:
	{
		int sw1;
		cout << "\nCe doresti sa faci pe aceasta clasa?";
		cout << "\n(1)Diverse operatii folosind metodele si supraincarcarile implementate(de la faza 1)";
		cout << "\n(2)Adaugare obiect in fisier(txt)";
		cout << "\n(3)Citire obiect din fisier(txt)";
		cout << "\n(4)Adaugare obiect in fisier(bin)";
		cout << "\n(5)Citire obiect din fisier(bin)\n";
		cin >> sw1;
		OperareFisiere opfisier;
		switch (sw1)
		{
		case 1:
		{
			Proprietate pr4;
			Proprietate pr1;
			Proprietate pr2("Bulevardul Dacia", "Aparatament");
			cout << "\nProprietatea pr2\n\n" << pr2;
			Proprietate pr3;
			pr3 = pr2;
			cout << "\nEgalam proprietatea p3 cu p2\n";
			cout << pr3;
			cout << "\nMarim valoarea prorpietatii p2 cu operatorul +=\n";
			pr2 += 10000;
			cout << pr2;
			cout << "\nComparam pr1 si pr4 prin operatorul==\n";
			if (pr1 == pr4)
			{
				cout << "\nAu aceeasi valoare\n";
			}
			else
			{
				cout << "\nNu au aceeasi valoare\n";
			}
			cout << "\nScriem proprietatea pr1";
			cin >> pr1;
			cout << "\nComparam pr3 si pr1 prin operatorul>\n";
			if (pr1 > pr3)
			{
				cout << "\nPr1 are o valoare mai mare decat pr3\n";
			}
			else
			{
				cout << "\nPr1 are o valoare mai mica decat pr3\n";
			}
			if (!pr1)
			{
				cout << "\nProprietatea e detinuta de organizatie\n";
			}
			else
			{
				cout << "\nProprietatea e inchiriata de organizatie\n";
			}
			cout << "\nIi crestem numarul de camere proprietatii pr1\n";
			pr1++;
			++pr1;
			cout << (float)pr1;
			cout << "\nCare sunt metrii patrati ai primei camere a proprietatii pr1?\n";
			cout << pr1[0];
			cin.get();
			cin.get();
			main();
			break;
		}
		case 2:
		{
			Proprietate prop11;
			cin >> prop11;
			ofstream fout;
			fout.open("proprietati.txt", ios::app);
			if (fout.is_open()) {
				fout << prop11;
				fout.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 3:
		{
			vector <Proprietate> prop;
			Proprietate prop11;
			ifstream fin("proprietati.txt");
			while (fin >> prop11) {
				prop.push_back(prop11);
			}
			cout << prop.size() << "\n";
			fin.close();
			for (int i = 0; i < prop.size(); ++i)
				cout << prop[i] << '\n';
			cin.get();
			cin.get();
			main();
			break;
		}
		case 4:
		{
			Proprietate prop12;
			ofstream fout2;
			fout2.open("proprietati.bin", ios::binary | ios::out);
			if (fout2.is_open()) {
				opfisier.scriereBinarProprietate(fout2, prop12);
				fout2.close();
			}
			cout << "Fisier Salvat" << endl;
			cin.get();
			cin.get();
			main();
			break;
		}
		case 5:
		{
			Proprietate prop13;
			ifstream fin2;
			fin2.open("proprietati.bin", ios::binary | ios::in);
			while (fin2 >> prop13) {
				opfisier.citireBinarProprietate(fin2, prop13);
				fin2.close();
			}
			cout << prop13;
			cin.get();
			cin.get();
			main();
			break;
		}
		default:
		{
			char rasp[3];
			cout << "\nNu ai introdus o optiune valida. Doresti sa te intorci la meniu?(Da/Nu)\n";
			cin >> rasp;
			if (strcmp(rasp, "Da") == 0 || strcmp(rasp, "da") == 0 || strcmp(rasp, "DA") == 0 || strcmp(rasp, "dA") == 0)
			{
				main();
			}
			else
			{
				break;
			}
		}
		}
		break;
	}
	case 6:
	{

		cin.get();
		cin.get();
		main();
		break;
	}
	default:
	{
		char rasp[3];
		cout << "\nNu ai introdus o optiune valida. Doresti sa te intorci la meniu?(Da/Nu)\n";
		cin >> rasp;
		if (strcmp(rasp, "Da") == 0 || strcmp(rasp, "da") == 0 || strcmp(rasp, "DA") == 0 || strcmp(rasp, "dA") == 0)
		{
			main();
		}
		else
		{
			break;
		}
	}
	}
	system("cls");
	return 0;
}