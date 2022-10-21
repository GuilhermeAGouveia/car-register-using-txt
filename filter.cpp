/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "lista.h"
#include "filter.h"

using namespace std;

Tlista_busca * busca_filtro(Tlista *listaP, Tlista_busca *listaB, char filtros[60]) {
    strcpy(listaB->filtros, filtros);
    //Tratando string com os filtros
    char matriz[10][20];
    char tmp[20];
    char *s = filtros;
    char *ant = s;
    for (int i = 0; i < 10; i++) strcpy(matriz[i], "\0");
    for (; *s; s++) {
        if (*s == '-') {
            s++;
            for (int i = 0; i < 20; i++) tmp[i] = '\0'; //reiniciando tmp manualmente
            for (int i = 0; *s != '\\' && *s; s++, i++) {
                tmp[i] = *s;
            }
            strcpy(matriz[atoi(ant)], tmp);
            //cout << atoi(ant) << "->" << matriz[atoi(ant)] << endl;
        }
        if (*s) *ant = *s;
    }
    /*for (int i = 0; i < 10; i++) {
        if (matriz[i][0]) cout << "OLA" << matriz[i] << endl;
    }*/
    //Tratamento_END

    converter(listaP, listaB);
    for (int i = 1; i <= 5; i++) {

        //cout << matriz[i] << endl;
        if (!matriz[i][0]) continue;
        listaB->tam = 0;
        switch (i) {
            case 1:
                //cout << "Caso 1: modelo" << endl;
                busca_geral(listaB, matriz[i], busca_modelo);
                break;
            case 2:
                //cout << "Caso 2: Marca" << endl;
                busca_geral(listaB, matriz[i], busca_marca);
                break;
            case 3:
                //cout << "Caso 3: tipo" << endl;
                busca_geral(listaB, matriz[i], busca_tipo); //busca-tipo
                break;
            case 4:
                //cout << "Caso 4: ano" << endl;
                busca_geral(listaB, matriz[i], busca_ano);
                break;
            case 5:
                //cout << "Caso 5: cor ->" << matriz[i] << endl;
                busca_geral(listaB, matriz[i], busca_cor);
                break;
            case 6:
                //busca cobustivel
                break;

        }
        if (listaB->tam == 0) {
            listaB->lista = NULL;
            //cout << "Olá" << endl;
            break;
        }
    }

    return listaB;
}

int converter(Tlista *listaP, Tlista_busca *listaB) {
    no *pont_1;
    pont_1 = listaP->lista;
    nobusca *pont_2 = listaB->lista;
    nobusca *tmp;
    while (pont_1 != NULL) {

        tmp = new (nobusca);
        // cout << tmp << endl;
        tmp->chave = pont_1->chave;
        tmp->info = &(pont_1->info);
        tmp->prox = NULL;
        if (listaP->lista->chave == pont_1->chave) {
            listaB->lista = tmp;
            pont_2 = listaB->lista;
        } else {
            pont_2->prox = tmp;
            pont_2 = pont_2->prox;
        }
        //cout << pont_2->chave << endl;

        pont_1 = pont_1->prox;
    }
    return 0;
}

void imprime_busca(Tlista_busca * lista) {
    if (lista->tam == 0) {
        cout << "Nunhum elemento foi encontrado!" << endl;
    } else {
        nobusca * ptr = lista->lista;
        cout << ">Veiculos encontrados" << endl;
        while (ptr != NULL) {
            cout << "-|-------------- Placa: " << ptr->chave << " ----------" << endl;
            cout << " |-Modelo: " << ptr->info->modelo << endl;
            cout << " |-Marca: " << ptr->info->marca << endl;
            cout << " |-Tipo: " << ptr->info->tipo << endl;
            cout << " |-Ano: " << ptr->info->ano << endl;
            cout << " |-Cor: " << ptr->info->cor << endl;
            cout << " |-Potencia: " << ptr->info->potencia << endl;
            cout << " |-Combustivel: " << ptr->info->combustivel << endl;
            cout << " |-KM: " << ptr->info->km << endl;
            cout << " |-Direção: " << ptr->info->direcao << endl;
            cout << " |-Câmbio: " << ptr->info->cambio << endl;
            cout << " |-Numero de portas: " << ptr->info->n_portas << endl;
            ptr = ptr->prox;
        }
        cout << "------------ Foram encontrados " << lista->tam << " veículos." << endl;
    }
}

void encerra_lista_busca(Tlista_busca * lista) {
    //cout << "-Encerrando lista Busca"<<endl;
    nobusca *pont, *ant;
    ant = pont = lista->lista;
    if (ant != NULL) pont = ant->prox;
    while (pont != NULL) {
        delete(ant);
        ant = pont;
        pont = pont->prox;

    }
    delete(ant);
    delete(lista);
    //cout << "-A lista de busca foi removida."<<endl;
}

Tlista_busca* inicia_lista_busca() {
    Tlista_busca* tmp = new (Tlista_busca);
    tmp->tam = 0;
    tmp->lista = NULL;
    strcpy(tmp->filtros, "\0");
    return tmp;
}

void busca_geral(Tlista_busca *lista, char dado[20], int (*funcPtr)(nobusca *pont, char dado[20])) {

    nobusca *ant, *pont;
    nobusca *atual, *atual_ant;
    int tmp;
    ant = pont = atual = atual_ant = lista->lista;
    while (pont != NULL) {
        tmp = funcPtr(pont, dado);
        if (!tmp) {
            ++lista->tam;
            insere_busca(pont, atual);
            atual_ant = atual;
            atual = atual->prox;
        }

        ant = pont;
        pont = pont->prox;
    }
    encerra_restante(atual);
    atual_ant->prox = NULL;
}

int busca_modelo(nobusca *pont, char dado[20]) {
    if (pont->info->modelo == dado) return 0;
    return 1;
}

int busca_cor(nobusca *pont, char dado[20]) {
    if (pont->info->cor == dado) return 0;
    return 1;
}

int busca_marca(nobusca *pont, char dado[20]) {
    if (pont->info->marca == dado) return 0;
    return 1;
}

int busca_tipo(nobusca *pont, char dado[20]) {
    if (pont->info->tipo == dado) return 0;
    return 1;
}

int busca_ano(nobusca *pont, char dado[20]) {
    if (pont->info->ano == atoi(dado)) return 0;
    return 1;
}

void insere_busca(nobusca *pont, nobusca *atual) {
    if (pont != atual) {
        atual->chave = pont->chave;
        atual->info = pont->info;
    }
}

/*
void insere_busca_inicio(Tlista_busca lista, nobusca noh){
    noh->prox = lista->lista;
    lista->lista = noh;
    
}
 */
void encerra_restante(nobusca *pont) {
    nobusca * ant = pont;

    if (ant != NULL) pont = pont->prox;

    while (pont != NULL) {
        delete(ant);
        ant = pont;
        pont = pont->prox;
    }
    delete(ant);
    //cout << "-Lixo de busca foi removido."<<endl;
}

nobusca * remove_busca(Tlista_busca * ptlista, string chave) {
    nobusca *ant, *ptr;
    if (!busca_placa(ptlista, chave, &ant)) return NULL;
    ptr = ant->prox;
    if (ptlista->lista->chave == chave) {
        ptlista->lista = ptr;
        ant->prox = NULL;
        ptr = ant;
    } else {
        ant->prox = ptr->prox;
        ptr->prox = NULL;
    }
    --ptlista->tam;
    return ptr;
}

bool busca_placa(Tlista_busca * ptlista, string chave, nobusca** ant) {
    *ant = ptlista->lista;
    nobusca * ptr = ptlista->lista;

    while (ptr != NULL && ptr->chave < chave) {
        *ant = ptr;
        ptr = ptr->prox;
    }
    return ptr != NULL && ptr->chave == chave;
}