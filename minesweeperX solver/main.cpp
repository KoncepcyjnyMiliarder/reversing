#include <windows.h>
#include <stdio.h>
#include <vector>

#define INDEX_TO_X(i,width) (i%width)
#define INDEX_TO_Y(i,width) (i/width)


struct Pola
{
    char unk[12];
    short* poletko;
    int wys;
    int unk1;
    int szer;
};

struct Mapa
{
    Pola* odkryte;
    Pola* mojeFlagi;
    Pola* unk;
    Pola* miny;
};

enum Lokacja
{
    lg,
    ld,
    pg,
    pd,
    gora,
    lewo,
    prawo,
    dol,
    srodek,
};

enum CoPodPolem
{
    spoko,
    cycki,
    niewiem,
};

Lokacja Lokalizuj(Mapa* mapa, int i)
{
    int x = INDEX_TO_X(i, mapa->miny->szer);
    int y = INDEX_TO_Y(i, mapa->miny->szer);
    if (x == 0 && y == 0) return lg;
    if (x == 0 && y == mapa->miny->wys - 1) return ld;
    if (x == mapa->miny->szer - 1 && y == mapa->miny->wys - 1) return pd;
    if (x == mapa->miny->szer - 1 && y == 0) return pg;
    if (x == 0) return lewo;
    if (y == 0) return gora;
    if (x == mapa->miny->szer - 1) return prawo;
    if (y == mapa->miny->wys - 1) return dol;
    return srodek;
}

CoPodPolem SprawdzPole(Mapa* mapa, int i)
{
    if (mapa->mojeFlagi->poletko[i] == -1 || mapa->odkryte->poletko[i] == -1) return spoko;
    if (mapa->miny->poletko[i] == -1) return cycki;
    return niewiem;
}

int SkanujSasiadow(Mapa* mapa, int i, std::vector<int>& indeksyMin, std::vector<int>& indeksyNieodkrytych)
{
    indeksyMin.clear();
    indeksyNieodkrytych.clear();
    CoPodPolem cpp;
    int index;
    Lokacja l = Lokalizuj(mapa, i);
    if (l == srodek)
    {

        index = i - 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - (mapa->miny->szer - 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - (mapa->miny->szer + 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + (mapa->miny->szer - 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + (mapa->miny->szer + 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        return 8;
    }
    if (l == lg || l == ld || l == pg || l == pd) return 3;
    if (l == dol)
    {

        index = i - 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - (mapa->miny->szer - 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - (mapa->miny->szer + 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        return 8;
    }
    if (l == gora)
    {

        index = i - 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + (mapa->miny->szer - 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + (mapa->miny->szer + 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        return 8;
    }
    if (l == lewo)
    {
        index = i + 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - (mapa->miny->szer - 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + (mapa->miny->szer + 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        return 8;
    }
    if (l == prawo)
    {

        index = i - 1;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - mapa->miny->szer;
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i - (mapa->miny->szer + 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        index = i + (mapa->miny->szer - 1);
        cpp = SprawdzPole(mapa, index);
        cpp == niewiem ? indeksyNieodkrytych.push_back(index) : cpp == cycki ? indeksyMin.push_back(index) : 0;
        return 8;
    }
    return 5;
}
/*
20 120 rog

kratki sa 16x16
*/

void LPklik(Mapa* mapa, int i)
{
    int x = INDEX_TO_X(i, mapa->miny->szer);
    int y = INDEX_TO_Y(i, mapa->miny->szer);
    SetCursorPos(20 + 16 * x, 120 + 16 * y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
}

void Pklik(Mapa* mapa, int i)
{
    int x = INDEX_TO_X(i, mapa->miny->szer);
    int y = INDEX_TO_Y(i, mapa->miny->szer);
    SetCursorPos(20 + 16 * x, 120 + 16 * y);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
}

void Lklik(Mapa* mapa, int i)
{
	int x = INDEX_TO_X(i, mapa->miny->szer);
	int y = INDEX_TO_Y(i, mapa->miny->szer);
	SetCursorPos(20 + 16 * x, 120 + 16 * y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}

bool GdzieKliknac(Mapa* mapa)
{
	static int ostatniIndeks = 0;
    for (int i = 0; i < mapa->miny->wys * mapa->miny->szer; i++)
    {
        if (mapa->mojeFlagi->poletko[i] == -1) //0 = nieoflagowane / -1 = oflagowane
        {
            //printf("Pole %d jest oflagowane\n", i);
            continue;
        }
        if (mapa->odkryte->poletko[i] == 0) // 0 = zakryte / -1 = odkryte
        {
            //printf("Pole %d jest zakryte\n", i);
            continue;
        }
        std::vector<int> indeksyMin; // jesli 0 min to odslon nieodkryte
        std::vector<int> indeksyNieodkrytych; //jesli miny == nieodkryte to zaznacz miny. Do okdrytych wliczane sa oflagowane
        int ilosc = SkanujSasiadow(mapa, i, indeksyMin, indeksyNieodkrytych);
        if (indeksyNieodkrytych.size() + indeksyMin.size() == 0) continue;
        if (indeksyMin.size() == 0)
        {
            /*printf("Odkrylbym POLA dookola %d XY %d %d bo jest %d min i %d nieodkrytych LOC %d\n", i,
                   INDEX_TO_X(i, mapa->miny->szer), INDEX_TO_Y(i, mapa->miny->szer),
                   indeksyMin.size(), indeksyNieodkrytych.size(), Lokalizuj(mapa, i));*/
			ostatniIndeks = i;
            LPklik(mapa, i);
            return true;
        }
        if (indeksyMin.size() > 0 && indeksyNieodkrytych.size() == 0)
        {
            /*printf("Odkrylbym MINY dookola %d XY %d %d bo jest %d min i %d nieodkrytych LOC %d\n", i,
                   INDEX_TO_X(i, mapa->miny->szer), INDEX_TO_Y(i, mapa->miny->szer),
                   indeksyMin.size(), indeksyNieodkrytych.size(), Lokalizuj(mapa, i));*/
            //SetCursorPos(20 + 16 * INDEX_TO_X(i, mapa->miny->szer), 120 + 16 * INDEX_TO_Y(i, mapa->miny->szer));
			
            for (int k = 0; k < indeksyMin.size(); k++)
            {
                Pklik(mapa, indeksyMin[k]);
				ostatniIndeks = indeksyMin[k];
            }
            return true;
        }
    }
    //printf("Slaba ciamajda ze mnie :(\n");
	int index = -1;

	for (int k = max(0, INDEX_TO_X(ostatniIndeks, mapa->miny->szer) - 6); k <= min(mapa->miny->szer - 1, INDEX_TO_X(ostatniIndeks, mapa->miny->szer) + 6); k++) {
		
		for (int p = max(0, INDEX_TO_Y(ostatniIndeks, mapa->miny->szer) - 6); p <= min(mapa->miny->wys - 1, INDEX_TO_Y(ostatniIndeks * mapa->miny->szer, mapa->miny->szer) + 6); p++) {
			//printf("ESP TU DE RESKJU %d %d %d\n", k, p, ostatniIndeks);
			CoPodPolem cpp;
			if (SprawdzPole(mapa, k + p * mapa->miny->szer) == niewiem) {
				//printf("ESP TU DE RESKJU :)\n");
				Lklik(mapa, k + p * mapa->miny->szer);
				index = 0;
				break;
			}
			
		}
	}
	if (index == -1){
		for (int k = 0; k < mapa->miny->szer*mapa->miny->wys; k++) {
			CoPodPolem cpp;
			if (SprawdzPole(mapa, k) == niewiem) {
				//printf("ESP HIPER SUPER ULTRA TU DE RESKJU :)\n");
				Lklik(mapa, k);
				ostatniIndeks = k;
				index = ostatniIndeks;
				break;
			}
		}
	}
	if (index == -1) {
		printf("GGWP :D\n");
		ostatniIndeks = 0;
		return true;
	}
	//printf("Ide sie powiesic :(\n");
    return false;
}


void Bot()
{

    Mapa* mapa = (Mapa*)((*(DWORD*)0x42D010) + 0x80);
    while (1)
    {
        if (GetAsyncKeyState(VK_HOME) & 1)
        {
			GdzieKliknac(mapa);
        }
    }

}

DWORD WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID q)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Bot, 0, 0, 0);
        break;
    }
    return 1;
}