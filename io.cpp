/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <cstdlib>
#include "lista.h"
#include <iostream>
#include <fstream>
using namespace std;

void readInputDefault(Tlista * ptlista) {
    Tinfo info_tmp;
    string chave;
    ifstream input("bd.txt");
    if (!input.is_open()) {
        cout << "Houve um problema com o banco de dados." << endl;
        exit(10); //exit(0);
    }
    do {
        input >> info_tmp.modelo;
        input >> info_tmp.marca;
        input >> info_tmp.tipo;
        input >> info_tmp.ano;
        input >> info_tmp.km;
        input >> info_tmp.potencia;
        input >> info_tmp.combustivel;
        input >> info_tmp.cambio;
        input >> info_tmp.direcao;
        input >> info_tmp.cor;
        input >> info_tmp.n_portas;
        input >> chave;
        insere_enc(ptlista, chave, info_tmp);

    } while (!input.eof());
    input.close();
}

int menu() {
    int op;
    cout << "Sistema de Gerenciamento de Veículos-------(SGV)\n\n" << endl;
    cout << "1)Incluir Veículo" << endl;
    cout << "2)Excluir Veículo" << endl;
    cout << "3)Buscar" << endl;
    cout << "4)Relatório Geral" << endl;
    cout << "5)Visualizar Listas de Busca" << endl;
    cout << "6)Sair" << endl;
    cout << "\n" << endl;


    do {
        cout << "Escolha uma opção > ";
        cin >> op;
    } while (op < 1 || op > 6);
    return op;
}

