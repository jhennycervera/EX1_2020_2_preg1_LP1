/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 * Created on 9 de octubre de 2021, 05:29 PM
 */


#include <iostream>
#include <iomanip>        
using namespace std;

/*
 * 
 */
#include "FuncionesEx01_20202_Preg01.h"

int main(int argc, char** argv) {
    void *pedidos, *stock;
    
    leerDatos(pedidos, stock);
    atiende(pedidos, stock);
    
    imprimirDatos(pedidos);
    
    return 0;
}

