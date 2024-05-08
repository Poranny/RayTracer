RayTracer

Program dokonuje symulacji oświetlenia poprzez raytracing. Zdecydowałem się na ten moment na raytracer czarno-biały, gdyż w ten sposób mogłem prototypować więcej nowych funkcji trochę szybciej, a podzielenie nawet rozwiniętej całości na kanały r-g-b nie wydaje się w przyszłości dużą przeszkodą.

Przykładowy cykl życia promienia (mającego początkowo pewien Max Depth):

1. zostaje wyemitowany z pozycji kamery w kierunku zgodnym z jej rotacją / FOV / rozdzielczością obrazu.

2. algorytm odnajduje (przy użyciu struktur BVH) wszystkie przecięcia promienia z obiektami sceny; 
	2.a jeśli ich nie ma - zwraca kolor tła; 
	2.b jeśli są - emitowany jest kolejny promień mający na celu przetestowanie, czy między punktem zderzenia a każdym z kolei źródłem światła istnieje przeszkoda. 
		2.b.a Jeśli istnieje przeszkoda - nic się nie dzieje i sprawdzane jest następne światło. 
		2.b.b Jeśli nie istnieje przeszkoda - punktowe wartości diffuse i/lub specular są zwiększane o wyliczoną wartość. 

3 Po dojściu do tego momentu;
	3.a jeżeli MAX DEPTH wynosi w tym momencie <= 1, kończymy; 
	3.b jeżeli wynosi więcej:
		- wokół normalnej trójkąta trafionego pierwotnie przez promień emitowane są nowe pochodne promienie dla diffuse (ich ilość to dLayerCount * dRadialCount)
		- wokół promienia odbitego od normalnej ww. trójkąta emitowane są nowe pochodne promienie dla specular (ich ilość to sLayerCount * sRadialCount)
		- kolejne promienie przechodzą powyższy proces od punktu drugiego, z ich wartością depth obniżoną o 1.

Wejścia:

Width, Height - rozdzielczość
Max Depth - maksymalna głębokość, tj. ilość odbić dla promienia.

D/S indirect factor - mnożnik wpływu światła indirect Diffuse/Specular na scenę
D/S layer count - współczynnik wpływający na ilość pochodnych promieni Diffuse/Specular z danego punktu
D/S radial count - współczynnik wpływający na ilość pochodnych promieni Diffuse/Specular z danego punktu

Camera pos - pozycja kamery (oś Y w górę)
Camera rot - obrót kamery (Euler)

Light pos - pozycja danego światła
Light intensity - intensywność danego światła

Material Diffuse - mnożnik wpływu światła diffuse na scenę
Material Specular - mnożnik wpływu światła specular na scenę
Material Roughness - wyższy roughness przyjmuje odbite światło z większego zakresu kątów; wpływa też na powstawanie rozmycia odbić jeżeli Max Depth >= 2


Proces generowania promieni pochodnych jest dla diffuse i specular bardzo podobny:

- w przypadku diffuse, wokół faceNormal generowanych jest dRadialCount koncentrycznie odchylonych promieni. Każdy z nich jest odchylony od faceNormal o pewien kąt - ilość obsługiwanych kątów (rozłożonych równomiernie między 5 i 89) to właśnie dLayerCount. Dla przykładu, dla dRadialCount=4 i dLayerCount=5, powinno być wygenerowanych 20 promieni potomnych; 5 z nich będzie odchylonych o 5 stopni od faceNormal, 5 kolejnych o 33 stopni, kolejne o 47, 61 i 89 stopni (te ostatnie będą prawie równoległe ze swoim face'm, co zapewnia że nawet małe wklęsłości zostaną uwzględnione).

- w przypadku specular główna różnica to to, że generujemy nie wokół normalnej trójkąta, tylko wokół promienia odbicia naszego promienia macierzystego. W związku z tym rzucają się w oczy pewne problemy, jak np. to, że przy dużym rozchyleniu część promieni będzie skazana na ponowne "uderzenie" w mesh, więc ten aspekt jest na pewno do poprawy.
Kolejną ważną kwestią związaną z generacją potomnych specular jest roughness - podjąłem pewne ryzyko i uzależniłem maksymalny odchył promieni specular od roughnessu, w celu uzyskania rozmytych odbić. Pomysł okazał się w niektórych przypadkach trafny (efekt widać na niektórych renderach).


Urównoleglenie obliczeń przy użyciu openmp pomogło z wydajnością znacząco (CUDA jeszcze nie próbowałem). BVH również bardzo usprawniło proces szczególnie dla dużych meshów.

Obciążenie obliczeniowe wzrasta lawinowo wraz ze zwiększaniem max depth. Dla Intela 13900k renderowanie sceny na maxdepth=3 dla rozdzielczości 100x100 potrafi sięgać minut.

Obciążenie jest też tym większe im więcej pikseli na ekranie jest reprezentowanych przez jakieś meshe, oraz im więcej w scenie trisów. BVH są tworzone pod kazdy mesh osobno więc dla dwóch meshów równiez wydajność jest stosunkowo mniejsza.



Ważniejsze klasy:

RayTracer - główna klasa z obliczeniami związanymi z samym procesem renderowania

BVH / BVHNode / AABB - klasy odpowiedzialne za zarządzanie strukturami BVH. Razem z klasami Mesh i Triangle odnajdują intersekcje promieni

Mesh - zawiera wektor ze swomi obiektami Triangle, które z kolei posiadają swoje wierzchołki (w formacie glm::vec3) oraz ich normalne 

Ray - prosta klasa, zawiera tylko operatory związane ze swoim origin i direction

Camera - tworzy i zawiera klasy Eye oraz ScreenPlane, służące do określania pierwotnego ustawienia promieni

Light, Material - jedynie przechowują swoje dane

Scene / RenderSettings - obie te klasy służą do przechowania innych klas lub zmiennych w celu łatwego zbiorczego dostępu do ustawień i przekazywania ich. Scena zawiera wszystkie obiekty które będą brać udział w renderowaniu i znajdą się w "renderowanym świecie"


W kwestii zarządzania samym oknem / GUI / renderowaniem tekstury w oknie:

MyTexture - zaimplementowany przeze mnie obiekt do prostego przechowywania danych tekstury w postaci [x,y]; pod koniec jest przekształcany do tablicy wejściowej w formacie akceptowanym przez opengl

ApplicationManager - menedżer całej aplikacji, wywołuje pozostałe funkcje (sam jest wywoływany z main.cpp)

GUIManager - definiuje całe GUI, posiada też dwie ważne funkcje czyli onClickRender (wywołuje proces renderowania) oraz updateSceneData (pobiera dane z pól tekstowych i aplikuje je do sceny)

OpenGLRenderer - obsługuje proces wyświetlania tekstury na ekranie

Defaults - przechowuje wiele domyślnych wartości



Visual Studio 2022
Użyte biblioteki:
- glew
- glfw
- glm
- wxwidgets (gui)
- tiny_obj_loader