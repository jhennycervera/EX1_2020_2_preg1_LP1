/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncionesEx01_20202_Preg01.h
 * Author: jhenn
 *
 * Created on 9 de octubre de 2021, 05:47 PM
 */

#ifndef FUNCIONESEX01_20202_PREG01_H
#define FUNCIONESEX01_20202_PREG01_H

#include <iostream>        
#include <fstream>
using namespace std;

void imprimirLinea(ofstream &, char, int);
void leerDatos(void *&pedidosGen, void*& stockGen) ;
void imprimirPedidos(void *pedidosGen);
void imprimirStock(void* stockGen);
void imprimirUnStock(void * stockGen);
void  imprimirPedido( void * pedidoGen);
void  leerStock(void *&stockGen);
void * leerStockArch(ifstream &arch);
void leerPedidos(ifstream &arch, int rRuc, void *buffPedidos[200], int& numPed);
void atiende(void*pedidos, void* stock) ;
void imprimirDatos(void *pedidos) ;
void  atiende(void * pedidos, void *stock);
void ordenarPedidosPorFecha(void * pedidosGen);
void  quickSortFecha(void **pedidos, int ini, int fin);
void  intercambiar( void **pedidos, int i, int j );
int comparaFechas( void *pedidoiGen, void *pedidojGen);
void atiende(void * pedidos, void *stock) ;
void  atenderPedidos(void* pedidosGen,void*stockGen );
void atenderUnPedido(void *pedidoGen, int &codPed,int &cantPed, void* stockGen );
void reducirStock(void** stock, int codPed, int cantPed, int &cantAten );
int buscarStock( void**stock, int codPed);


void imprimirDatos(void *pedidosGen);
void imprimirUnPedidoArch(ofstream &arch, void **regPedido);
void imprimirCabecera(ofstream &arch, int ruc);
void fSepararFecha(int fecha, int &dd, int &mm, int &aa);
void ordenarPedidosPorRuc(void *pedidosGen);
void quickSortRuc(void**pedidos, int ini, int fin) ;
int compararRuc(void *pedidosiGen, void* pedidosjGen) ;



#endif /* FUNCIONESEX01_20202_PREG01_H */
