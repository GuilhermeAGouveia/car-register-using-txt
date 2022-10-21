/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lista.h
 * Author: Guilherme
 *
 * Created on January 25, 2021, 09:31 AM
 */

#include <iostream>

#ifndef LISTA_H
#define LISTA_H

using namespace std;
//tipo info, correspondente a cada linha do bd.txt
typedef struct {
    string modelo;
    string marca;
    string tipo;
    int ano;
    int km;
    float potencia;
    string combustivel;
    string cambio;
    string direcao;
    string cor;
    int n_portas;
 
    
} Tinfo;

//tipos para lista principal
typedef struct no_ {
	//critério de busca da ordenação
	string chave;

	//'carga útil' do nó
	//num cenario real, poderia ser, por exemplo: nome, endereco...
	Tinfo info;

	struct no_ * prox;
} no;



typedef struct {
    int tam;
    no_ * lista;
} Tlista;


//assinaturas
Tlista* inicia_lista();


void encerra_lista(Tlista * ptlista);
bool busca_enc(Tlista * ptlista, string chave, no ** ant);
bool insere_enc(Tlista * ptlista, string chave, Tinfo valor);
no * remove_enc(Tlista * ptlista, string chave);
void imprime(Tlista * ptlista);

#endif /* LISTA_H */

