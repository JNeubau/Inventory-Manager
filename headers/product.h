#pragma once

#include <cstdlib>
#include <string>

#include "database.h"
#include "global_variables.h"


#ifndef MAIN_CPP_PRODUCT_H
#define MAIN_CPP_PRODUCT_H
#endif //MAIN_CPP_PRODUCT_H


class Product {
private:
    int ID;
    int barcode = 10000000;    // different for every product -> have 8 numbers
    char *productName = (char *) (malloc(sizeof(char)));
    char *producerName = (char *) (malloc(sizeof(char)));
    char *productCategory = (char *) (malloc(sizeof(char)));
    long quantity = 1;
    float prize = 0.0;

public:
    Product() = default;;   // konstructor
    ~Product() {            // dekonstructor
        free(productName);
        free(producerName);
        free(productCategory);
    };

    static void deleteProduct(int id) {
        sqldb.deleteRow(id, "PRODUCTS");
    };

    void addNewProduct(string name, long number, float money, int code, string producer, string category) {   // nowy produkt
        ID = productIndex++;

        quantity = number;
        prize = money;
        barcode = code;

        strcpy(productName, name.data());
        strcpy(producerName, producer.data());
        strcpy(productCategory, category.data());

        sqldb.insertDataForProducts(ID, productName, prize, quantity, barcode, producerName, productCategory);
    };

    // TODO: można zrobić podklase change ze wszystkimi opcjami zmiany parametru?
    void updateQuantity(int id, long new_value) {
        quantity = new_value;
        sqldb.updateInfo(id, "QUANTITY", new_value, "PRODUCTS");
    };

    void changeProducer(string maker) {
        strcpy(producerName, maker.data());
    };
    void changeProductName(string new_name) {
        strcpy(productName, new_name.data());
    };
    void changeProductCategory(string new_category) {
        strcpy(productCategory, new_category.data());
    };
    void changePrize(float new_prize) {
        prize = new_prize;
    };
    void changeBarcode(int new_barcode) {
        barcode = new_barcode;
    };

};