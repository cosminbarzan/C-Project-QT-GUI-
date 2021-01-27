#pragma once
#include "domeniu.h"

/*Functie care testeaza crearea unei oferte*/
void test_oferta();

/*Functie care testeaza adaugarea unei oferte*/
void test_repo_store();

/*Functie care testeaza adaugarea unei oferte*/
void test_srv_adauga();

/*Functie care testeaza stergerea unei oferte*/
void test_repo_sterge();

/*Functie care testeaza stergerea unei oferte*/
void test_srv_sterge();

/*Functie care testeaza modificare unei oferte*/
void test_repo_modifica();

/*Functie care testeaza modificare unei oferte*/
void test_srv_modifica();

/*Functie care testeaza cautarea unei oferte*/
void test_srv_cauta();

/*Functie care testeaza filtrarea dupa destinatie*/
void test_filtrare_dest();

/*Functie care testeaza filtrarea dupa pret*/
void test_filtrare_pret();

/*Functie care testeaza sortarea dupa denumire*/
void test_srv_sort_denumire();

/*Functie care testeaza sortarea dupa destinatie*/
void test_srv_sort_destinatie();

/*Functie care testeaza sortarea dupa tip+pret*/
void test_srv_sort_tip_pret();

/*Functie care testeaza validarea unei oferte*/
void test_validator();

/*Functie care testeaza raportul ofertelor dupa tip*/
void test_srv_raport();

/*Functie care testeaza adaugarea in cos a unei oferte*/
void test_adauga_cos();

/*Functie care testeaza stergerea ofertelor din cos*/
void test_sterge_cos();