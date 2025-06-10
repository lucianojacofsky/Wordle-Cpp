#include "lib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    string ruta_archivo;
    cout << "Ruta al listado de palabras: ";
    cin >> ruta_archivo;

    vector<string> listado = cargar_listado(ruta_archivo);
    if (listado.empty()) {
        cout << "Error" << endl;
        return 1;
    }

    
    std::srand(std::time({}));

    
    std::string palabra_secreta = listado[std::rand() % listado.size()];
    cout << "La palabra secreta tiene " << palabra_secreta.size() << " letras." << endl;

    int intentos_restantes = 5;
    string intento;

    while (intentos_restantes > 0) {
        cout << "Te quedan " << intentos_restantes << " intentos" << endl;
        cin >> intento;

        if (!intento_valido(intento, palabra_secreta, listado)) {
            cout << "Mal, intenta nuevamente" << endl;
            continue;
        }

        vector<EstadoLetra> resultado = evaluar_intento(intento, palabra_secreta);
        cout << respuesta_en_string(resultado) << endl;

        if (intento == palabra_secreta) {
            cout << "¡Correcto!" << endl;
            return 0;
        }

        intentos_restantes--;
    }

    cout << "El número de intentos se agotó, la palabra era: " << palabra_secreta << endl;
    return 0;
}
