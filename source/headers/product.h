#pragma once

#include <cstdlib>
#include <string>

using std::string;


class Product {
protected:
    int ID;
    int barcode = 10000000;    // different for every product -> have 8 numbers
    char *productName = (char *) (malloc(sizeof(char)));
    char *producerName = (char *) (malloc(sizeof(char)));
    char *productCategory = (char *) (malloc(sizeof(char)));
    long quantity = 1;
    float prize = 0.0;

public:
    Product() = default;;
    ~Product();

    static void deleteProduct(int);
    void addNewProduct(string, long, float, int, string, string);

    void modifyProduct(char*, char*, char*);    // pozostałę
    void modifyProduct(char*, long);   // quantity
    void modifyProduct(char*, float);   // new_prize
    void modifyProduct(char*, int);   // barcode
};