/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Guilherme
 *
 * Created on January 28, 2021, 18:36 AM
 */

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "lista.h"
#include "io.h"
#include "filter.h"

//using namespace std;

void buscar();
void excluir();
void inserir();
void relatorio();
int listas();
string verificarUso(Tlista_busca *lista);

Tlista * listaP;
Tlista_busca *lista2;
Tlista_busca *lista3;
Tlista_busca *lista4;

/*
 * 
 */
int main() {

    no * p;
    bool loop = true;

    listaP = inicia_lista();
    lista2 = inicia_lista_busca();
    lista3 = inicia_lista_busca();
    lista4 = inicia_lista_busca();

    readInputDefault(listaP);
    int op = 0;
    do {
        op = menu();
        switch (op) {
            case 1:
                inserir();
                break;
            case 2:
                excluir();
                break;
            case 3:
                buscar();
                break;
            case 4:
                relatorio();
                break;
            case 5:
                listas();
                break;
            case 6:
                loop = !loop;
                break;
        }
        cout << "\n...PRESSIONE QUALQUER TECLA PARA CONTINUAR..." << endl;
        getchar();
        getchar();
    } while (loop);


    encerra_lista(listaP);
    encerra_lista_busca(lista2);
    encerra_lista_busca(lista3);
    encerra_lista_busca(lista4);
    return (EXIT_SUCCESS);
}

string verificarUso(Tlista_busca *lista) {
    if (lista->filtros[0]) {
        return "(Em uso)";
    } else {
        return "(Vazia)";
    }
}

void buscar() {
    char filtros[60];
    int op;
    cout << "\n------------Buscas com Filtros-------------\n" << endl;

    cout << "Escolha uma das Listas para armanezar sua busca\n" << endl;
    cout << "Lista 1" << verificarUso(lista2) << endl;
    cout << "Lista 2" << verificarUso(lista3) << endl;
    cout << "Lista 3" << verificarUso(lista4) << endl;
    do {
        cout << "Insira o numero da Lista > ";
        cin >> op;
    } while (op < 1 || op > 3);
    cout << "Filtros: 1-modelo 2-marca 3-tipo 4-ano 5-cor" << endl;
    cout << "Insira o numero seguido por seu valor separado por '-', cada filtro deve ser separado por '\\'" << endl;
    cout << "Este sistema é CASE-SENSITIVE" << endl;
    cout << "Exemplo: 1-KA\\3-Hatch\\2-FORD\\5-Branco" << endl;
    cout << "\nFiltro: ";
    cin >> filtros;
    //strcpy(filtros,"3-Hatch\\2-FORD");
    switch (op) {
        case 1:
            busca_filtro(listaP, lista2, filtros);
            imprime_busca(lista2);
            break;
        case 2:
            busca_filtro(listaP, lista3, filtros);
            imprime_busca(lista3);
            break;
        case 3:
            busca_filtro(listaP, lista4, filtros);
            imprime_busca(lista4);
            break;

    }


}

void inserir() {
    Tinfo insert;
    //KA FORD SUV 2020 20101 1.8 Flex Manual Automatico Preto 4
    string placa;
    cout << "\n------------Inserir Veículo-------------\n" << endl;
    cout << "Modelo > ";
    cin >> insert.modelo;
    cout << "Marca > ";
    cin >> insert.marca;
    cout << "Tipo > ";
    cin >> insert.tipo;
    cout << "Ano > ";
    cin >> insert.ano;
    cout << "KM > ";
    cin >> insert.km;
    cout << "Potencia > ";
    cin >> insert.potencia;
    cout << "Combustivel > ";
    cin >> insert.combustivel;
    cout << "Cambio > ";
    cin >> insert.cambio;
    cout << "Direção > ";
    cin >> insert.direcao;
    cout << "Cor > ";
    cin >> insert.cor;
    cout << "Numero de portas > ";
    cin >> insert.n_portas;
    cout << "Placa > ";
    cin >> placa;
    if (insere_enc(listaP, placa, insert)) {
        cout << "Inserido com sucesso" << endl;
        if (lista2->filtros[0]) busca_filtro(listaP, lista2, lista2->filtros); //update pos-insert
        if (lista3->filtros[0]) busca_filtro(listaP, lista3, lista3->filtros);
        if (lista4->filtros[0]) busca_filtro(listaP, lista4, lista4->filtros);
    }
}

void excluir() {
    string placa;
    cout << "\n------------Excluir Veículo-------------\n" << endl;
    cout << "Placa > ";
    cin >> placa;
    if (remove_enc(listaP, placa)) {
        cout << "Removido" << endl;
        if (lista2->filtros[0]) remove_busca(lista2, placa);//update pos-remove
        if (lista3->filtros[0]) remove_busca(lista3, placa);
        if (lista4->filtros[0]) remove_busca(lista4, placa);
    } else {
        cout << "Não existe" << endl;
    }
}

void relatorio() {
    cout << "--Relatório Geral \n\n" << endl;
    imprime(listaP);
}

int listas() {
    int op;
    int control = false;
    cout << "------------Visualização de buscas-------------" << endl;
    cout << "\n\nQual lista deseja visualizar?\n" << endl;
    if (lista2->filtros[0]) {
        cout << "Lista 1" << endl;
        control = true;
    }
    if (lista3->filtros[0]) {
        cout << "Lista 2" << endl;
        control = true;
    }
    if (lista4->filtros[0]) {
        cout << "Lista 3\n" << endl;
        control = true;
    }
    if (!control) {
        cout << "Nenhuma lista foi criada\n";
        return 0;
    }
    do {
        cout << "\nInsira o numero da Lista > ";
        cin >> op;
    } while (op < 1 || op > 3);
    switch (op) {
        case 1:
            imprime_busca(lista2);
            cout << "O filtro usado foi:" << lista2->filtros << endl;
            break;
        case 2:
            imprime_busca(lista3);
            cout << "O filtro usado foi:" << lista3->filtros << endl;
            break;
        case 3:
            imprime_busca(lista4);
            cout << "O filtro usado foi:" << lista4->filtros << endl;
            break;
    }
    return 0;
}