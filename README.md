Gul Farhad Ali Irinel 
Tic-Tac-Toe based on MiniMax Algorithm

<=================================<STRUCTURI>=================================>

	In realizarea acestei teme am decis sa pun intr-un fisier separat numit
	"structuri.h" toate structurile folosite. Am sa explic in cateva randuri 
	semnificatia fiecarei structuri in parte:
	1. Tree - structura de arbori pe care am folosit-o pentru a transpune
	jocurile obtinute din jocul radacina dar si pentru construirea arborelui
	de la cerinta 3. tabla - contine matricea de joc din nodul respectiv,
	valoarea - reprezinta ce valoare are acel nod (folosit pentru cerintele 2 
	si 3, nr_fii - indica numarul de fii pe care il are nodul respectiv
	si child[100] - unde se retine pointer la toti fii acelui nod.
	2. pozitie - folosit pentru a determina prioritatea elementelor din
	matrice (pentru a efectua asa cum trebuie subjocurile.
	3. Queue - am folosit o coada pentru a putea realiza citirea la cerinta
	a 3 a. In coada am retinut constant radacinile subarborilor pe care
	ii citeam. 
	4. node - nodul de la coada - contine pointer la o radacine de subarbore
	si tip pentru a determina daca nodul respectiv e frunza sau nod intern.
	
<=================================<CERINTA 1>=================================>

	Pentru aceasta cerinta am citit matricea data in enunt si am pus-o ca
	radacina in arborele de joc. De aici am apelat o functie recursiva
	principala care sa-mi construiasca arborele de joc bazat pe matricea de
	start si primul care trebuie sa puna (X sau 0). 
	In functia de efectuare joc am extras matricea din nodul radacina, am 
	calculat prioritatea de punere si cat timp am (-) in matrice inseamna ca
	de atatea ori vom pune elemente in subarbore. Astfel se apeleaza recursiv
	in functie de cine trebuie sa puna si cate mutari mai sunt necesare pana
	la finalizarea jocului. Astfel daca jocul s-a terminat chiar daca numarul
	de (-) din matrice nu s-a terminat exista o functie de verificare
	daca jocul meu s-a terminat (cu victoria jucatorului aferent).
	Afisarea se face in adancime si se printeaza cate taburi sunt necesare.

<=================================<CERINTA 2>=================================>

	Cerinta 2 este asemanatoare cu prima cu mici exceptii. Plecand din 
	nodurile terminale se verifica valoarea de adevar (1 pentru victoria
	jucatorului dat din enunt si 0 pentru remiza sau infrangere). Astfel 
	se face operatie logica "sau" atunci cand jucatorul initial trebuie sa
	mute si operatia logica "si" atunci cand oponentul trebuie sa mute
	intre toate mutarile si finalizarile posibile. Astfel se merge recursiv
	pana ce se poate determina valorile din radacini.
	Afisarea se face similar cu cea de la cerinta 1 cu exceptia ca atunci 
	cand valoarea din nod este 1 se afiseaza T si cand este 0, F.

<=================================<CERINTA 3>=================================>

	Cerinta 3 reprezenta algoritmul minimax pentru un arbore dat.
	Citirea am facut-o cu ajutorul unei cozi in care sa retin nodurile 
	radacina pentru fii cititi pe urmatorul rand. Daca caracterul de dinaintea
	unui numar este "(" stim ca numarul citit reprezinta numarul de fii
	pe care acel nod cu valoarea INT_MAX (pentru a-l diferentia de celelalte)
	il are. Astfel, extragem nodul radacina din coada, ii general numarul de
	fii necesari, ii adaugam si pe acestia in coada si efectuam aceste
	operatii cat timp am elemente citite (in functie de inaltimea arborelui).
	Daca numarul citit se afla intre caracterele "[]" atunci vom stii ca
	acel nod este de tip frunza si nu il mai adaugam in coada de noduri
	radacina. Daca este intalnit caracterul '\n' in locul ' ' atunci vom 
	incrementa pozitia liniei curente.
	Algoritmul de minimax l-am implementat astfel:
	1. Daca arborele este nul inseamna ca nu are valoare deci returnam 0
	2. Daca nu exista primul fiu al nodului curent sau acesta are 0 fii
	atunci returnam valoarea din acesta (stim concret ca este nod radacina
	3. Cat timp am fii, in functie de nivelul adancimii (par sau impar)
	efectuez minimul sau maximul dintre valorile nodurilor fii si le
	pun in valoarea nodului parinte. Acest procedeu este recursiv. La final 
	afisam arborele rezultat in adancime, asemanator cerintelor anterioare.


