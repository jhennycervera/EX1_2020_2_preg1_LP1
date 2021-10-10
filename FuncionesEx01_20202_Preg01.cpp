/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/* 
 * File:   FuncionesEx01_20202_Preg01.cpp
 * Author: jhenn
 * Codigo: 20182841
 * Created on 9 de octubre de 2021, 05:47 PM
 */

#include "FuncionesEx01_20202_Preg01.h"
#include <iostream>        
#include <iomanip>
#include <fstream>
#include <cstring>        
using namespace std;

enum PEDIDO_ENUM {
    FECHA, RUC, COD, NOMBRE, CANT_SOL, CANT_A
};

void imprimirLinea(ofstream &Rep, char c, int cant) {
    Rep.fill(c);
    Rep << setw(cant) << c << endl;
    Rep.fill(' ');
}

void leerDatos(void *&pedidosGen, void*& stockGen) {

    ifstream arch("pedidos.csv", ios::in);
    void** pedidos; //para la estructura exacta de pedidos.

    void* buffPedidos[200]; //buff estatico de punteros void+ para guardar los pedidos.
    int rRuc, numPed = 0;
    char rNombreTienda[50];
    while (1) {
        arch>>rRuc;
        if (arch.eof()) break;
        arch.get();
        arch.getline(rNombreTienda, 50, ',');
        leerPedidos(arch, rRuc, buffPedidos, numPed);
    }

    pedidos = new void*[numPed + 1];
    for (int i = 0; i < numPed; i++) {
        pedidos[i] = buffPedidos[i];
    }
    pedidos[numPed] = nullptr;

    pedidosGen = pedidos;

    leerStock(stockGen);

    imprimirPedidos(pedidosGen);
    imprimirStock(stockGen);

}

void imprimirPedidos(void *pedidosGen) {

    void **pedidos = (void **) pedidosGen;
    for (int i = 0; pedidos[i] != nullptr; i++) {
        imprimirPedido(pedidos[i]);
    }

}

void imprimirStock(void* stockGen) {
    void **stock = (void **) stockGen;
    for (int i = 0; stock[i] != nullptr; i++) {
        imprimirUnStock(stock[i]);
    }
}

void imprimirUnStock(void * stockGen) {
    void** stock = (void**) stockGen;

    int cod = *(int *) stock[0];
    int cant = *(int *) stock[1];
    cout << setw(10) << cod << cant << endl;
}

void imprimirPedido(void * pedidoGen) {

    void ** pedido = (void**) pedidoGen;

    int ruc = *(int*) pedido[RUC];
    int fecha = *(int*) pedido[FECHA];
    int cod = *(int*) pedido[COD];
    char *nombre = (char*) pedido[NOMBRE];
    int stock = *(int*) pedido[CANT_SOL];
    int cant = *(int*) pedido[CANT_A];

    cout << left << setw(10) << fecha << setw(10) << ruc << setw(10) << cod
            << setw(60) << nombre << setw(10) << stock << cant << endl;



}

void leerStock(void *&stockGen) {

    ifstream arch("stock.csv", ios::in);
    void **stock, *regStock, *buffStock[100];
    int numStock = 0;

    while (1) {
        regStock = leerStockArch(arch);
        if (regStock == nullptr) break;
        buffStock[numStock] = regStock;
        numStock++;
    }

    stock = new void*[numStock + 1];
    for (int i = 0; i < numStock; i++) {
        stock[i] = buffStock[i];
    }
    stock[numStock] = nullptr;

    stockGen = stock;
}

void * leerStockArch(ifstream &arch) {

    void** regStock;
    int rcodProd, stock;

    arch>>rcodProd;
    if (arch.eof()) return nullptr;
    arch.get();
    arch>> stock;

    regStock = new void*[2];
    regStock[0] = new int(rcodProd);
    regStock[1] = new int (stock);

    return regStock;
}

void leerPedidos(ifstream &arch, int rRuc, void *buffPedidos[200], int& numPed) {
    // 1) int *cod  - arch>> *cod   --mal, pq no se ha separado memoria 
    // 2) int cod   - arch>>cod  - int* ptroCod= &cod   ---> mal, pq la varible cod se destruye y ya no voy a poder tener ese valor en mi ptro generico     
    int dd, mm, aa, rcodPed, rcantPed;
    char c, nombrePed[50];
    void **regPed;
    while (1) {
        arch >> aa >> c >> mm >> c>>dd;
        arch.get();
        arch>>rcodPed;
        arch.get();
        arch.getline(nombrePed, 50, ',');
        arch>>rcantPed;

        int fecha = dd + mm * 100 + aa * 10000;
        char* nombre = new char [ strlen(nombrePed) + 1];
        strcpy(nombre, nombrePed);
        regPed = new void*[6]; //separamos memoria para el pedido
        regPed[FECHA] = new int(fecha);
        regPed[RUC] = new int(rRuc);
        regPed[COD] = new int(rcodPed);
        regPed[NOMBRE] = nombre;
        regPed[CANT_SOL] = new int (rcantPed);
        regPed[CANT_A] = new int(0);

        buffPedidos[numPed] = regPed;
        numPed++;
        if (arch.get() == '\n') break;
    }
}

void ordenarPedidosPorFecha(void * pedidosGen) {
    void** pedidos = (void**) pedidosGen;

    int numPed;
    for (numPed = 0; pedidos[numPed] != nullptr; numPed++);

    quickSortFecha(pedidos, 0, numPed - 1); //indice del inicio-indice del fin del arreglo
}

void quickSortFecha(void **pedidos, int ini, int fin) {

    if (ini >= fin) return;
    int pivote = ini;

    for (int i = ini + 1; i <= fin; i++) {
        if (comparaFechas(pedidos[i], pedidos[ini]) < 0) { //ordeno de forma ascendente 
            pivote++;
            intercambiar(pedidos, i, pivote);
        }
    }

    intercambiar(pedidos, ini, pivote);
    quickSortFecha(pedidos, ini, pivote - 1);
    quickSortFecha(pedidos, pivote + 1, fin);
}

void intercambiar(void **pedidos, int i, int j) {

    void * aux;
    aux = pedidos[i];
    pedidos[i] = pedidos[j];
    pedidos[j] = aux;

}

int comparaFechas(void *pedidoiGen, void *pedidojGen) {

    void** pedidoi = (void**) pedidoiGen;
    void** pedidoj = (void**) pedidojGen;

    return *(int*) pedidoi[FECHA] - *(int*) pedidoj[FECHA];
}

void atiende(void * pedidos, void *stock) {

    ordenarPedidosPorFecha(pedidos);
    cout << endl;
    atenderPedidos(pedidos, stock);

    cout << endl << endl;
    //impresion de los pedidos y stock
    imprimirPedidos(pedidos);
    imprimirStock(stock);
}

void atenderPedidos(void* pedidosGen, void*stockGen) {
    void** pedidos = (void**) pedidosGen;

    int codPed, cantPed;

    for (int i = 0; pedidos[i] != nullptr; i++) {
        atenderUnPedido(pedidos[i], codPed, cantPed, stockGen);
    }
}

void atenderUnPedido(void *pedidoGen, int &codPed, int &cantPed, void* stockGen) {
    void** pedido = (void**) pedidoGen;
    void**stock = (void**) stockGen;

    int cantAten;
    codPed = *(int*) pedido[COD];
    cantPed = *(int*) pedido[CANT_SOL];

    reducirStock(stock, codPed, cantPed, cantAten);

    int * ptroCantAt = (int*) pedido[CANT_A]; //apunta a esa DM
    (* ptroCantAt) = cantAten;


}

void reducirStock(void** stock, int codPed, int cantPed, int &cantAten) {

    int pos = buscarStock(stock, codPed);
    if (pos != -1) {

        void**regStock = (void**) stock[pos];
        int *ptrStock = (int*) regStock[1];

        int cantResta = (*ptrStock) - cantPed;
        if (cantResta >= 0) {
            cantAten = cantPed;
            (*ptrStock) = cantResta;
        } else {
            cantAten = (*ptrStock);
            (*ptrStock) = 0;
        }
    }
}

int buscarStock(void**stock, int codPed) {

    for (int i = 0; stock[i] != nullptr; i++) {
        void** regStock = (void**) stock[i];
        int cod = *(int*) regStock[0];
        if (cod == codPed) return i;

    }
    return -1;
}

void imprimirDatos(void *pedidosGen) {

    ofstream arch("Reporte.txt", ios::out);

    void**pedidos = (void**) pedidosGen;

    ordenarPedidosPorRuc(pedidosGen);

    cout << "PEDIDOS ORDENADOS POR RUC" << endl;
    imprimirPedidos(pedidosGen);
    int rucAnt = 0;
    arch << setw(50) << "REPORTE DE ATENCION" << endl;


    for (int i = 0; pedidos[i] != nullptr; i++) {

        void**regPedido = (void**) pedidos[i];
        int ruc = *(int*) regPedido[RUC];

        if ((rucAnt != ruc && rucAnt != 0) || rucAnt == 0) {
            imprimirCabecera(arch, ruc);
        }
        imprimirUnPedidoArch(arch, regPedido);
        rucAnt = ruc;
    }

}

void imprimirUnPedidoArch(ofstream &arch, void **regPedido) {

    int dd, mm, aa;
    int fecha = *(int*) regPedido[FECHA];
    fSepararFecha(fecha, dd, mm, aa);

    int cod = *(int*) regPedido[COD];
    char *nombre = (char*) regPedido[NOMBRE];
    int cant_sol = *(int*) regPedido[CANT_SOL];
    int cant = *(int*) regPedido[CANT_A];
    
    
    arch<<setfill('0')<<right<<aa<<'/'<<setw(2)<<mm<<'/'<<setw(2)<<dd;
    arch<<left<<setfill(' ')<<setw(5)<<" ";
    arch<<right<<setw(4)<<cod<<setw(10)<<' '<<left<<setw(50)<<nombre<<setw(25)<<cant_sol<<cant<<endl;
    
}

void imprimirCabecera(ofstream &arch, int ruc){
    arch<<endl<<"RUC: "<<ruc<<endl;
    imprimirLinea(arch, '=',200);
    arch<<left<<setw(15)<<"Fecha"<<setw(25)<<"Cod. Producto"<<setw(40)<<"Producto"
              <<setw(25)<<"Cant. Solicitada"<<"Cant. Atendida"<<endl;
    
     imprimirLinea(arch, '=',200);
    
}

void fSepararFecha(int fecha, int &dd, int &mm, int &aa) {

    aa = fecha / 10000;
    fecha %= 10000;
    mm = fecha / 100;
    dd = fecha % 100;

}

void ordenarPedidosPorRuc(void *pedidosGen) {

    void** pedidos = (void**) pedidosGen;
    int i;
    for (i = 0; pedidos[i] != nullptr; i++);
    quickSortRuc(pedidos, 0, i - 1);

}

void quickSortRuc(void**pedidos, int ini, int fin) {

    if (ini >= fin) return;
    int pivote = ini;

    for (int i = ini + 1; i <= fin; i++) {
        if (compararRuc(pedidos[i], pedidos[ini]) < 0) { //asecendente
            pivote++;
            intercambiar(pedidos, i, pivote);
        }
    }

    intercambiar(pedidos, ini, pivote);
    quickSortRuc(pedidos, ini, pivote - 1);
    quickSortRuc(pedidos, pivote + 1, fin);
}

int compararRuc(void *pedidosiGen, void* pedidosjGen) {

    void** pedi = (void**) pedidosiGen;
    void**pedj = (void**) pedidosjGen;

    return *(int*) pedi[RUC] - *(int*) pedj[RUC];
}