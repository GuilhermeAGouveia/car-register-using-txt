/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <iostream>
#include "lista.h"
using namespace std;

Tlista* inicia_lista() {
    Tlista* tmp = new (Tlista);
    tmp->tam = 0;
    tmp->lista = NULL;
    return tmp;
}

void encerra_lista(Tlista * ptlista) {
    no * ant, * pont;
    ant = pont = ptlista->lista;
    if (ant != NULL) pont = ant->prox;
    while (pont != NULL) {
        delete(ant);
        ant = pont;
        pont = pont->prox;
    }
    delete(ant);
    delete(ptlista);
}

bool busca_enc(Tlista * ptlista, string chave, no** ant) {
    *ant = ptlista->lista;
    no * ptr = ptlista->lista;

    while (ptr != NULL && ptr->chave < chave) {
        *ant = ptr;
        ptr = ptr->prox;
    }
    return ptr != NULL && ptr->chave == chave;
}

bool insere_enc(Tlista * ptlista, string chave, Tinfo valor) {
    no* ant;
    if (busca_enc(ptlista, chave, &ant)) return false;
    no * ptr = new (no);
    ptr->chave = chave;
    ptr->info = valor;
    if (ptlista->tam == 0 || chave < ptlista->lista->chave) {
        ptr->prox = ptlista->lista;
        ptlista->lista = ptr;
    } else {
        ptr->prox = ant->prox;
        ant->prox = ptr;
    }
    ptlista->tam += 1;
    return true;
}

no * remove_enc(Tlista * ptlista, string chave) {
    no *ant, *ptr;
    if (!busca_enc(ptlista, chave, &ant)) return NULL;
    ptr = ant->prox;
    if (ptlista->lista->chave == chave) {
        ptlista->lista = ptr;
        ant->prox = NULL;
        ptr = ant;
    } else {
        ant->prox = ptr->prox;
        ptr->prox = NULL;
    }
    ptlista->tam -= 1;
    return ptr;
}

void imprime(Tlista * ptlista) {
    no * ptr = ptlista->lista;
    while (ptr != NULL) {
        cout << "-|-------------- Placa: " << ptr->chave << " ----------" << endl;
        cout << " |-Modelo: " << ptr->info.modelo << endl;
        cout << " |-Marca: " << ptr->info.marca << endl;
        cout << " |-Tipo: " << ptr->info.tipo << endl;
        cout << " |-Ano: " << ptr->info.ano << endl;
        cout << " |-Cor: " << ptr->info.cor << endl;
        cout << " |-Potencia: " << ptr->info.potencia << endl;
        cout << " |-Combustivel: " << ptr->info.combustivel << endl;
        cout << " |-KM: " << ptr->info.km << endl;
        cout << " |-Direção: " << ptr->info.direcao << endl;
        cout << " |-Câmbio: " << ptr->info.cambio << endl;
        cout << " |-Numero de portas: " << ptr->info.n_portas << endl;



        ptr = ptr->prox;
    }
    cout << "----------Número de Veículos: " << ptlista->tam << " --------" << endl;
}
