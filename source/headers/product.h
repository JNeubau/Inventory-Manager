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

    static void deleteProduct(string name);
    static void deleteProduct(int barcode);

    void addNewProduct(string name, long number, float money, int code, string producer, string category);

    void modifyProduct(char* name, char* new_val, char* columnName);    // rest
    void modifyProduct(char* name, long new_value);   // quantity
    void modifyProduct(char* name, float new_prize);   // new_prize
    void modifyProduct(char* name, int new_barcode);   // barcode
};