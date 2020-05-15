#include <iostream>

using namespace std;
class Kamera
{
protected:
int mp;
int fp;
static int photoCounter;
public:
Kamera() { mp = 10; fp = 100; }
Kamera(int m, int f) { mp = m; fp = f; }
Kamera(const Kamera &k) { mp = k.mp; fp = k.fp; }

static int getCounter() { return photoCounter; }

bool Slikaj()
{
	if (fp >= mp)
		{
		fp -= mp;
	photoCounter++;
			return true;
		}
	return false;
}
	void ispisi() { cout << mp << "," << fp; }
};
int Kamera::photoCounter = 0;
class VideoKamera : public Kamera
{
protected:
	static int videoCounter;
public:
VideoKamera() :Kamera() {}
VideoKamera(int m, int f) :Kamera(m, f) {}

static int getVCounter() { return videoCounter; }

bool Snimaj(int sekunde)
{
	if (sekunde*mp <= fp)
{
		fp -= sekunde * mp;
		videoCounter++;
		return true;
}
	return false;
	}

};
int VideoKamera::videoCounter = 0;
class DinString
{
private:
int duzina;
char *tx;
public:
DinString() { duzina = 0; tx = NULL; }
DinString(const char ulaz[])
{
	duzina = 0;
	while (ulaz[duzina] != '\0')
	{
		duzina++;
	}
	tx = new char[duzina + 1];
	for (int i = 0; i < duzina; i++)
	{
		tx[i] = ulaz[i];
	}
	tx[duzina] = '\0';
}
DinString(const DinString &ds)
{
	duzina = ds.duzina;
	tx = new char[duzina + 1];
	for (int i = 0; i < duzina; i++)
	{
		tx[i] = ds.tx[i];
	}
	tx[duzina] = '\0';
}
~DinString() { delete[] tx; }

int length() const { return duzina; }
char& operator[] (int i) { return tx[i]; }
char operator[] (int i) const { return tx[i]; 
	}
	DinString& operator=(const DinString &ds)
{
	if (this != &ds) {
		delete[] tx;
		duzina = ds.duzina;
		tx = new char[duzina + 1];
		for (int i = 0; i < duzina; i++)
	{
			tx[i] = ds.tx[i];
		}
		tx[duzina] = '\0';
	}
	return *this;
}
DinString& operator+=(const DinString &ds)
{
	int i;
	char *tempText = new char[duzina + ds.duzina + 1];
	for (i = 0; i < duzina; i++)
	{
		tempText[i] = tx[i];
	}
	for (i = 0; i < ds.duzina; i++)
	{
		tempText[duzina + i] = ds.tx[i];
	}
	tempText[duzina + ds.duzina] = '\0';
	duzina += ds.duzina;
	delete[] tx;
	tx = tempText;

	return *this;
}
friend bool operator==(const DinString &ds1, const DinString &ds2)
{
	if (ds1.duzina != ds2.duzina)
	{
		return false;
	}
	for (int i = 1; i < ds1.duzina; i++)
	{
		if (ds1.tx[i] != ds2.tx[i])
		{
			return false;
		}
	}
}
friend bool operator!=(const DinString &ds1, const DinString &ds2)
{
if (ds1.duzina != ds2.duzina)
{
	return true;
}
for (int i = 1; i < ds1.duzina; i++)
{
	if (ds1.tx[i] != ds2.tx[i])
	{
		return true;
	}
}
return false;
}
friend DinString operator+(const DinString &ds1, const DinString &ds2)
{
DinString tp;
tp.duzina = ds1.duzina + ds2.duzina;
tp.tx = new char[tp.duzina + 1];
int i;
for (i = 0; i < ds1.duzina; i++)
{
tp.tx[i] = ds1.tx[i];
}
for (i = 0; i < ds2.duzina; i++)
{
tp.tx[ds1.duzina + i] = ds2.tx[i];
}
tp.tx[tp.duzina] = '\0';
return tp;
}

friend ostream& operator<<(ostream &out, const DinString &ds)
{
if (ds.duzina > 0)
{
cout << ds.tx;
}
return out;


}
};
class Telefon
{
protected:
	DinString broj;
public:
Telefon() { broj = "  065 203 1114"; }
Telefon(DinString brojic) { broj = brojic; }

bool pozovi(DinString brojic)
{
if (broj != brojic)
{
	return true;
}
return false;
}
};
class TelefonG2 : public Telefon
{
protected:
	Kamera k;
public:
TelefonG2() : Telefon(), k() {}
TelefonG2(int m, int f, DinString b) :Telefon(b), k(m, f) {}

bool slikajSliku()
{
	return k.Slikaj();
}
};
class TelefonG3 : public TelefonG2
{
private:
	VideoKamera vk;
public:
	TelefonG3() : TelefonG2(), vk() {}
	TelefonG3(int m, int f, DinString b) :TelefonG2(m, f, b), vk(m, f) {}

bool snimiVideo(int sekunde)
{
	return vk.Snimaj(sekunde);
}
void ispisiKamera()
{
	k.ispisi();
	cout << "|" << k.getCounter() << "|" << vk.getVCounter() << "|" << broj << endl;
}
void ispisiVideo()
{
	vk.ispisi();
	cout << "|" << k.getCounter() << "| " << vk.getVCounter() << "|" << broj << endl;
}
};
int main()
{
Kamera k;
Kamera k2(10, 100);
Kamera k3(k);

k2.Slikaj();
cout << k2.getCounter() << endl;

TelefonG3 t;
TelefonG3 t2(12, 100, "063 335 427");
TelefonG3 t3(t);

t.pozovi("065 203 1114");
t.pozovi("063 335 427");

t.slikajSliku();
t2.snimiVideo(10);

t.ispisiKamera();
t2.ispisiVideo();

t.slikajSliku();
t.slikajSliku();
t.ispisiKamera();
t2.snimiVideo(10);
t2.snimiVideo(10);
t2.ispisiVideo();
	return 0;
}
