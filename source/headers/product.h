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

    static void modifyProduct(string name, string new_val, string columnName);    // rest
    static void modifyProduct(string name, long new_value);   // quantity
    static void modifyProduct(string name, float new_prize);   // new_prize
    static void modifyProduct(string name, int new_barcode);   // barcode
};