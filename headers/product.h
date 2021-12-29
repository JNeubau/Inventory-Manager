#pragma once

#include <cstdlib>

#include "database.h"
#include "global_variables.h"


#ifndef MAIN_CPP_PRODUCT_H
#define MAIN_CPP_PRODUCT_H
#endif //MAIN_CPP_PRODUCT_H


class Product {
private:
    int ID;
    int barcode;    // different for every product -> have 12 numbers
    char *productLabel = (char *) (malloc(sizeof(char)));
    char *productName = (char *) (malloc(sizeof(char)));
    char *producerName = (char *) (malloc(sizeof(char)));
    char *productCategory = (char *) (malloc(sizeof(char)));
    long quantity;
    double prize;

public:
    Product() = default;;
    ~Product() {
        free(productName);
        free(producerName);
        free(productCategory);
        free(productLabel);
    };

    void addNewProduct() {};
    void removeProduct() {};

    // TODO: można zrobić podklase change ze wszystkimi opcjami zmiany parametru?
    void updateQuantity() {};
    void changeProducer() {};
    void changeProductLabel() {};
    void changeProductName() {};
    void changeProductCategory() {};
    void changePrize() {};
    void changeBarcode() {};

};