#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//test: 1 2 1 0 0 1 2 1 2 1 2 1 2 1 2 2 1 2 1 2 1 2 1 2 1
//1 je za prvog igraca, 2 za drugog, 0 za prazno mesto u matrici
int rdm() {
	int a = rand() % 2 + 1;
	return a;
}


//matrica je formata 5x5 integera, pri cemu 0 oznacava prazno mesto, 1 mesto popunjeno kuglicom prvog igraca, a 2 mesto popunjeno kuglicom drugog igraca
class Matrica {
	int elem[5][5];
public:
	Matrica()
	{
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) elem[i][j] = 0;
	}

	int get(int i, int j) const {
		return elem[i][j];
	}

	void set(int i, int j, int k)
	{
		elem[i][j] = k;
	}

	bool ubaci(int col, int brigr) {
		if(col>=0 && col<=4){
		int i = 4;
			while (elem[i][col] != 0 && i>=0) { i -= 1; }
			if (elem[i][col] == 0) {
				elem[i][col] = brigr; return true;
			}
			else return false;
		}
		else return false;
	}

	friend ostream& operator << (ostream& it, const Matrica& m) {
		it << "------------" << endl;
		for(int i=0;i<5;i++) {
			cout << "|";
			for (int j = 0; j < 5; j++) it << m.get(i, j) << " ";
			cout << "|";
				it << endl;
		}
		it << "------------" << endl;
		return it;
	}

	Matrica& operator = (Matrica& m) {
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) elem[i][j] = m.get(i, j);
		return *this;
	}

	Matrica(const Matrica& m) {
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) elem[i][j]= m.get(i,j);
	}
	Matrica(Matrica&& m) {
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) elem[i][j] = m.get(i, j);
	}
};

int proverirez(Matrica& m) {
	for(int i=0;i < 5;i++)
		for (int j = 0; j < 5; j++)
		{
			if (m.get(i, j) == 1) {
				if ((j - 1 >= 0) && (j + 1 <= 4)) if (m.get(i, j - 1) == 1 && m.get(i, j + 1) == 1) return 1;
				if ((i - 1 >= 0) && (i + 1 <= 4)) if (m.get(i - 1, j) == 1 && m.get(i + 1, j) == 1) return 1;
				if ((i - 1 >= 0) && (j - 1 >= 0) && (i + 1 <= 4) && (j + 1 <= 4)) if (m.get(i - 1, j - 1) == 1 && m.get(i + 1, j + 1) == 1) return 1;
				if ((i + 1 >= 0) && (j - 1 >= 0) && (i - 1 <= 4) && (j + 1 <= 4)) if (m.get(i+1,j-1) == 1 && m.get(i-1,j+1) == 1) return 1;
				}
			if (m.get(i, j) == 2) {
				if ((j - 1 >= 0) && (j + 1 <= 4)) if (m.get(i, j - 1) == 2 && m.get(i, j + 1) == 2) return -1;
				if ((i - 1 >= 0) && (i + 1 <= 4)) if (m.get(i - 1, j) == 2 && m.get(i + 1, j) == 2) return -1;
				if ((i - 1 >= 0) && (j - 1 >= 0) && (i + 1 <= 4) && (j + 1 <= 4)) if (m.get(i - 1, j - 1) == 2 && m.get(i + 1, j + 1) == 2) return -1;
				if ((i + 1 >= 0) && (j - 1 >= 0) && (i - 1 <= 4) && (j + 1 <= 4)) if (m.get(i + 1, j - 1) == 2 && m.get(i - 1, j + 1) == 2) return -1;
			}
		}
	return 0;
}

int dohvatibr(Matrica& m) {
	int a = 0;
	for (int j = 0; j < 5; j++) if (m.get(0, j) == 0) a += 1;
	return a;
}

int dohvatislcol(Matrica& m)
{
	if (m.get(0, 0)==0) return 0;
	if (m.get(0, 1)==0) return 1;
	if (m.get(0, 2)==0) return 2;
	if (m.get(0, 3)==0) return 3;
	if (m.get(0, 4)==0) return 4;
	else { return 0; }
}

class Cvor {
	public:
		int igrac;
		int stanje; int br;
	Matrica mat;
	Cvor** niz;
	Cvor* o;
	Cvor(const Matrica& matt, int m, int igr): mat(matt) {
		o = nullptr; niz = new Cvor*[m]; for (int i = 0; i < m; niz[i++] = nullptr); br = m; stanje = 0; igrac = igr;
	}

	friend ostream& operator<<(ostream& it, const Cvor* p) {
		it << "Stanje: " << p->stanje  << endl;
		it << p->mat;
			return it;
	}

	~Cvor()
	{
		delete[] niz;
	}
};


class CvorListe {
public:
	Cvor* cvor = nullptr;
	CvorListe* next = nullptr;
	CvorListe(Cvor* c) {
		cvor = c;
	}
	~CvorListe() {
		cvor = nullptr;
	}
};


class Stek {
	CvorListe* p;
public:
	Stek() {
		p = nullptr;
	}
	void PUSH(Cvor* c) {
		CvorListe* q = new CvorListe(c);
		q->next = p;
		p = q;
	}

	Cvor* POP() {
		if (p == nullptr) return nullptr;
		else {
			CvorListe* stari = p;
			Cvor* vrati = p->cvor;
			p = p->next;
			delete stari;
			return vrati;
		}
	}

	bool EMPTY() {
		if (p == nullptr) return true;
		else return false;
	}


	~Stek() {
		CvorListe* stari = nullptr;
		for (CvorListe* q = p; q != nullptr; q = q->next) {
			if (!stari) { delete stari; } stari = q;
		}
	}
};


class Red {
	CvorListe* p;
	CvorListe* z;
public:
	Red() {
		p = z = nullptr;
	}
	void INS(Cvor* c) {
		CvorListe* q = new CvorListe(c);
		if (p == nullptr) { p = z = q; }
		else { z->next = q; z = q; }
	}

	Cvor* DEL() {
		if (p == nullptr) return nullptr;
		else {
			CvorListe* stari = p;
			Cvor* vrati = p->cvor;
			p = p->next;
			delete stari;
			return vrati;
		}
	}
	bool EMPTY() {
		if (p == nullptr) return true;
		else return false;
	}

	~Red() {
		CvorListe* stari = nullptr;
		for (CvorListe* q = p; q != nullptr; q = q->next) {
			if (!stari) { delete stari; } stari = q;
		}
	}
};




class Stablo {
	int m;
	Cvor* koren;




public:
	Stablo() = default;


	Stablo(Matrica& poc) {
		int igr = rdm();
		m = dohvatibr(poc);
		koren = new Cvor(poc, m, igr);
		koren->stanje = proverirez(poc);
		if ((m != 0) && (koren->stanje == 0)) {
			Red r; Cvor *p;
			r.INS(koren);
			while (!r.EMPTY())
			{
				p = r.DEL();
				m = dohvatibr(p->mat);
				Matrica mtemp2(p->mat), mtemp(p->mat);
				for (int i = 0; i < m; i++) {
					mtemp2.ubaci(dohvatislcol(mtemp), igr);
					mtemp.ubaci(dohvatislcol(mtemp), igr);
					Cvor *q = new Cvor(mtemp2, dohvatibr(mtemp2), igr); q->o = p;
					q->stanje = proverirez(mtemp2);
					p->niz[i] = q;
					if (dohvatibr(mtemp2) != 0 && q->stanje == 0) {
						r.INS(q);
					}
					if (q->stanje == 1 && p->stanje == 0 && igr == 1) { p->stanje = 1; }
					if (q->stanje == -1 && p->stanje == 0 && igr == 2) { p->stanje = -1; }
					mtemp2 = p->mat;
				}
				if (p->igrac == 1) { igr = 2; }
				else { igr = 1; }
			}
		}
	}

	

void ispis() const {
	Stek s;
	if (koren != nullptr) {
		s.PUSH(koren);
		cout << "Preorder: " << endl;
		while (!s.EMPTY())
		{
			Cvor* p = s.POP();
			cout << p;
			for (int i = p->br -1; i > -1; i--) { if (p->niz[i] != nullptr) { s.PUSH(p->niz[i]); } }
		}
		cout << endl;
	}
}

	
void brisi() {
	Stek s;
	if (koren != nullptr) {
		s.PUSH(koren);
		while (!s.EMPTY())
		{
			Cvor* p = s.POP();
			for (int i = p->br - 1; i > -1; i--) { if (p->niz[i] != nullptr) { s.PUSH(p->niz[i]); } }
			delete p;
		}
		koren = nullptr;
	}
}

~Stablo() {
	brisi();
}
};



int main() {
	Stablo* s=new Stablo();
	srand(time(NULL));
	while(true){
	cout << "----------------------------------------------" << endl;
	cout << "|Izaberite stavku iz menija:                 |" << endl;
	cout << "|[1]      - Napravi novo stablo igre.        |" << endl;
	cout << "|[2]      - Izbrisi stablo igre.             |" << endl;
	cout << "|[3]      - Ispisi  stablo igre.             |" << endl;
	cout << "|[0]      - Kraj programa.                   |" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Kod operacije: ";
	Matrica m1;
	int a;
	cin >> a;
	switch (a) {
	case 1:
		s->brisi();
		cout << "Matrica pocetnog stanja igre: (0 za prazno mesto, 1 za mesto prvog igraca, 2 za mesto drugog igraca)" << endl;
		cout << "Matrica: ";
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) {
			cin >> a; m1.set(i, j, a);
		}
		s = new Stablo(m1);
		break;
	case 2:
		s->brisi();
		break;
	case 3:
		s->ispis();
		break;
	case 0:
		exit(0);
	}
	}
}
