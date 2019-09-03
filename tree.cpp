#include <iostream>
using namespace std;

class Cvor{
	int info;
public:
	Cvor** niz;
	Cvor* o;
	Cvor(int i, int m) {
		info = i; o = nullptr; niz = new Cvor*[m]; for (int i = 0; i < m; niz[i++] = nullptr);
	}

	friend ostream& operator<<(ostream& it,const Cvor* p)  {
		return it << p->info;			
}

	~Cvor()
	{
		delete [] niz;
	}
};

class CvorListe {
public:
	Cvor* cvor=nullptr;
	CvorListe* next = nullptr;
	CvorListe(Cvor* c) {
		cvor=c;
	}
	~CvorListe() {
		cvor = nullptr;
	}
};

/*class Red {
	CvorListe* p;
	CvorListe* z;
public:
	Red() {
		p = z = nullptr;
	}
	void ins(Cvor* c) {
		CvorListe* q= new CvorListe(c);
		if (p == nullptr) { p = z = q; }
		else { z->next = q; z = q; }
	}
    
	Cvor* del() {
		if (p == nullptr) return nullptr;
		else {
			CvorListe* stari = p;
			Cvor* vrati = p->cvor;
			p = p->next;
			delete stari;
			return vrati;	}	
	}

	~Red() {
		CvorListe* stari=nullptr;
		for (CvorListe* q = p; q != nullptr; q = q->next) {
			if (!stari) { delete stari; } stari = q;}
		}
};*/

class Stek {   
	CvorListe* p; 
public:
	Stek() {
		p =  nullptr;
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



class Stablo {
	int m;
	Cvor* koren;


	int nivocvora(Cvor *c){
		int n = 0;
		Cvor *q = c;
		while (q != koren) { n += 1; q = q->o; }
		return n;
	}

public:

	

	Stablo(int mm) {
		m = mm;
		koren = nullptr;
	}

	/*Stablo& operator +=(int k) { //efikasno, stil lvlorder
		if (koren == nullptr) {
			koren = new Cvor(k, m);
			return *this;
		}
		else {
			Cvor* q = new Cvor(k, m);
			Red red;
			red.ins(koren);
			while (true)
			{
				Cvor* p = red.del();
				for (int i = 0; i < m; i++) {
					if (p->niz[i] == nullptr) { p->niz[i] = q; q->o = p; return *this; }
					else { red.ins(p->niz[i]); }
				}
			}
		}
		}*/

	Stablo& operator +=(int k) {
		if (koren == nullptr) {
			koren = new Cvor(k, m);
			return *this;
		}
		else {
			Stek s;
				s.PUSH(koren);
				Cvor* q = new Cvor(k, m);
				Cvor *mincvor = nullptr;  int mincvornivo = 10000; int minpoz;
				while (!s.EMPTY())
				{
					Cvor* p = s.POP();
					int ima_praznih = false; int prpoz = -1;
					for (int i = m-1; i > -1; i--) {
						if (p->niz[i] != nullptr) { s.PUSH(p->niz[i]); }
						else {
							ima_praznih = true; if ((prpoz == -1) || (prpoz>i)) prpoz = i;
					} }
					if ((nivocvora(p) < mincvornivo) && ima_praznih) { mincvor = p; mincvornivo = nivocvora(p); minpoz = prpoz; }
				}
				mincvor->niz[minpoz] = q;
				q->o = mincvor;
				return *this;
			}	
	}



	int sirina() {
		int sirine[100];
		for (int i = 0; i < 100; i++) sirine[i] = 0;
		Stek s;
		if (koren != nullptr) {
			s.PUSH(koren);
			while (!s.EMPTY())
			{
				Cvor* p = s.POP();
				sirine[nivocvora(p)] += 1;
				for (int i = m - 1; i > -1; i--) { if (p->niz[i] != nullptr) { s.PUSH(p->niz[i]); } }
			}
			int max = 0;
			for (int i = 0; i < 100; i++) { if (sirine[i] > max) max = sirine[i]; }
			return max;
		}
		else { return 0; }
	}

	void ispis() const {
		Stek s;
		if (koren != nullptr) {
			s.PUSH(koren);
			cout << "Preorder: " << endl;
			while (!s.EMPTY())
			{
				Cvor* p = s.POP();
				cout << "Cvor: " <<  p << ", sinovi: ";
				int br = 0;
				for (int i = 0; i < m; i++) {
					if (p->niz[i] != nullptr) { cout << p->niz[i] << " "; br += 1;
					}
				}
				if (br == 0) cout << "nema" << endl; else { cout << endl; }
				for (int i = m - 1; i > -1; i--) { if (p->niz[i] != nullptr) { s.PUSH(p->niz[i]); } }
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
				for (int i = m - 1; i > -1; i--) { if (p->niz[i] != nullptr) { s.PUSH(p->niz[i]); } }
				delete p;
			}
		}
	}

	~Stablo() {
		brisi();
	}
	};



	int main() {
		Stablo* s = new Stablo(3);
		while (true)
		{
			cout << "----------------------------------------" << endl;
			cout << "|Izaberite stavku iz menija:            |" << endl;
			cout << "|[1]      - Napravi stablo.             |" << endl;
			cout << "|[2]      - Izbrisi stablo.             |" << endl;
			cout << "|[3]      - Dodaj cvor u stablo(int).   |" << endl;
			cout << "|[4]      - Ispisi preorder stabla.     |" << endl;
			cout << "|[5]      - Odredi sirinu stabla.       |" << endl;
			cout << "|[0]      - Kraj programa.              |" << endl;
			cout << "----------------------------------------" << endl;
			cout << "Kod operacije: ";
			int a;
			cin >> a;
			switch (a) {
			case 1:
				s->brisi();
				cout << "Dimenzija stabla: "; int m; cin >> m;
				if (m < 2) { cout << "Neodgovarajuca visina stabla."; break; }
				s = new Stablo(m);
				break;
			case 2:
				s->brisi(); break;
				break;
			case 3:
				cout << "Unesite vrednost novog cvora(int):"; int k; cin >> k; (*s) += k; break;
			case 4:
				(*s).ispis(); break;
			case 5:
				cout << "Sirina stabla je: " << (*s).sirina() << endl; break;
			case 0:
				exit(0);
			}

		}

	}
