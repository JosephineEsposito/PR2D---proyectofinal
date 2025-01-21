#pragma region | Lib


// editor
#include <litegfx.h>
#include <glfw3.h>

// stream
#include <iostream>
#include <sstream> // per ostringstream
#include <vector> // per gestire i mazzi


// custom
#include "Vec2.h"
#include "Mazzo.h"
#include "Carta.h"
#include "World.h"
#include "Sprite.h"

// namespaces

#pragma endregion


#pragma region | Variabili Globali e Defines

// ---------- DEFINES ---------- //
#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265358979323846f


// ---------- CONST ---------- //
// Centro dello schermo
const Vec2 screenCenter = Vec2(WIDTH / 2, HEIGHT / 2);

#pragma endregion


#pragma region | Methods

// Templates
// From number to string
template <typename T>
std::string stringFromNumber(T val) {
	std::ostringstream stream;
	stream << std::fixed << val;
	return stream.str();
}

#pragma endregion


/// ==================== MAIN ==================== ///
int main()
{
#pragma region | Initializing
	std::cout << "Initializing GLFW and LiteGFX...\n";

	// DeltaTime
	static float previous_seconds = static_cast<float>(glfwGetTime());
	float current_seconds = static_cast<float>(glfwGetTime());
	float deltaTime = current_seconds - previous_seconds;
	previous_seconds = current_seconds;

	// >> 1. Inizializziamo la libreria
	int ans = glfwInit();
	if (ans == 0)
	{
		cout << "[Error] Unable to initialize GLFW.\n";
	}

	// >> 2. Creiamo una finestra
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Title", nullptr, nullptr); //<< window width, window height, window title, new(nullptr) or existing monitor, monitor to share with or none(nullptr)

	// >> 3. Associamo il contesto attuale per questa finestra
	glfwMakeContextCurrent(window); // se perdiamo il riferimento a window si pu� ottenere con glfwGetContextCurrent()

	// >> 4. Inizializzare LiteGFX
	lgfx_setup2d(WIDTH, HEIGHT);
#pragma endregion

#pragma region | Local Variables
	cout << "Creating the variables...\n";
	// Mouse
	double mouse_x = 0;
	double mouse_y = 0;
	Vec2 mouse = Vec2();


	//Vars
	string s_Title = "Scopa";

	World scene;
	Player* player = new Player();

	scene.start(player); // carichiamo il background (ci basta una sola volta)
	scene.startGame(); // iniziamo il gioco (ci basta una sola volta)

#pragma endregion


	/// ==================== MAIN LOOP ==================== ///
	cout << "Starting the game\n";
	// >> 5. Ciclo principale
	while (glfwWindowShouldClose(window) != 1) // oppure se si preme ESC
	{
		// >> 5.1 Attualizza DeltaTime
		current_seconds = static_cast<float>(glfwGetTime());
		deltaTime = current_seconds - previous_seconds;

		// >> 5.2 Leggiamo l'input
		ans = glfwWindowShouldClose(window); //(Input)per sapere  se chiudere la finestra

		glfwGetCursorPos(window, &mouse_x, &mouse_y); //(Input)per sapere la posizione del mouse
		mouse.x = mouse_x;
		mouse.y = mouse_y;

		

		/// ==================== LOGICA ==================== ///
		// >> 5.3 Attualizziamo la logica del gioco
		
		//TODO>>load the cards!!


		scene.update(deltaTime, window);
		if (scene.GS == scene.quit)
		{
			break;
		}

		
		// >> 5.4 Puliamo il buffer
		lgfx_clearcolorbuffer(.4, .8, .2); // Limpiamos el fondo

		/// ==================== RENDER ==================== ///
		// >> 5.5 Renderizziamo la scena
		glfwSetWindowTitle(window, s_Title.c_str()); // Titolo window

		scene.draw(Vec2(WIDTH, HEIGHT));

		// >> 5.6 Camiamo il backbuffer per il frontbuffer
		glfwSwapBuffers(window);
		// >> 5.7 Processiamo gli eventi (inputs)
		glfwPollEvents();
	}


	// >> 6. Liberiamo le risorse
	/// ==================== END ==================== ///
	cout << "Cleaning the memory\n";
	glfwTerminate();// Per chiudere e finalizzare, in caso ci siano errori



	return 0;
}
//EOF