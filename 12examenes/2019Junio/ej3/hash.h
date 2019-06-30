#ifndef __HASH_H
#define __HASH_H

 // AQUI DEBEN DECLARARSE LA FUNCION O FUNCIONES h QUE
 // SEAN NECESARIAS (deben ponerse las cabeceras).
 // LAS FUNCIONES DEBEN IMPLEMENTARSE EN UN ARCHIVO .cpp
 // APROPIADO (p.e., hash.cpp)
 template <typename T>
 unsigned int h(T v) {
     std::hash<T> hash;
     return hash(v);
 }
 
 
#endif