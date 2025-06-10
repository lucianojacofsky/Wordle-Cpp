#include "lib.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> cargar_listado(const string &nombre_archivo) {
    vector<string> palabras;
    ifstream archivo(nombre_archivo);
    string palabra;
    
    if (archivo.is_open()) {
        while (archivo >> palabra) {
            palabras.push_back(palabra);
        }
        archivo.close();
    }
    
    return palabras;
}

bool intento_valido(const string &intento, const string &palabra_secreta, const vector<string> &listado) {
    if (intento.size() != palabra_secreta.size()) {
        return false;
    }
    
    for (const string &palabra : listado) {
        if (palabra == intento) {
            return true;
        }
    }
    return false;
}

vector<EstadoLetra> evaluar_intento(const string &intento, const string &palabra_secreta) {
    vector<EstadoLetra> resultado(intento.size(), EstadoLetra::NoPresente);
    
    for (int i = 0; i < intento.size(); ++i) {
        if (intento[i] == palabra_secreta[i]) {
            resultado[i] = EstadoLetra::LugarCorrecto;
        } else {
            for (int j = 0; j < palabra_secreta.size(); ++j) {
                if (intento[i] == palabra_secreta[j] && i != j) {
                    resultado[i] = EstadoLetra::LugarIncorrecto;
                    break;
                }
            }
        }
    }
    
    return resultado;
}

string respuesta_en_string(const vector<EstadoLetra> &respuesta) {
    string resultado;
    for (EstadoLetra estado : respuesta) {
        if (estado == EstadoLetra::LugarCorrecto) {
            resultado += "+";
        } else if (estado == EstadoLetra::LugarIncorrecto) {
            resultado += "-";
        } else {
            resultado += "X";
        }
    }
    return resultado;
}
