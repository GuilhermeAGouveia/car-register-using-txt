/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   filter.h
 * Author: Guilherme Gouveia
 *
 * Created on 7 de Março de 2021, 14:59
 */
#include "lista.h"
#ifndef FILTER_H
#define FILTER_H

//tipos para lista de busca
typedef struct nobusca_ {
	//critério de busca da ordenação
	string chave;

	//'carga útil' do nó
	//num cenario real, poderia ser, por exemplo: nome, endereco...
	Tinfo *info;

	struct nobusca_ * prox;
} nobusca;

typedef struct {
    int tam;
    nobusca * lista;
    char filtros[60];
} Tlista_busca;

Tlista_busca* inicia_lista_busca();
Tlista_busca * busca_filtro(Tlista *ptlista, Tlista_busca *lista2, char *s);
void imprime_busca(Tlista_busca * ptlista);
int converter(Tlista *lista1, Tlista_busca *lista2);
void encerra_lista_busca(Tlista_busca * ptlista) ;
void busca_geral(Tlista_busca *lista, char dado[20], int (*funcPtr)(nobusca *pont, char dado[20]));
int busca_modelo(nobusca *pont, char dado[20]);
void insere_busca(nobusca *pont, nobusca *atual);
void encerra_restante(nobusca *pont);
int busca_cor(nobusca *pont, char dado[20]);
int busca_marca(nobusca *pont, char dado[20]);
int busca_tipo(nobusca *pont, char dado[20]);
int busca_ano(nobusca *pont, char dado[20]);
nobusca * remove_busca(Tlista_busca * ptlista, string chave);
bool busca_placa(Tlista_busca * ptlista, string chave,  nobusca** ant);


#endif /* FILTER_H */

