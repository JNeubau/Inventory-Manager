#include "headers/database.h"
#include "headers/global_variables.h"
#include "headers/product.h"


Product::~Product() {            // dekonstructor
    free(productName);
    free(producerName);
    free(productCategory);
};

void Product::deleteProduct(int id) {
        sqldb.deleteRow("PRODUCTS", id);
};

void Product::addNewProduct(string name, long number, float money, int code, string producer, string category) {   // nowy produkt
        ID = productIndex++;

        quantity = number;
        prize = money;
        barcode = code;

        strcpy(productName, name.data());
        strcpy(producerName, producer.data());
        strcpy(productCategory, category.data());

        sqldb.insertData(ID, productName, prize, quantity, barcode, producerName, productCategory);
};

void Product::modifyProduct(int id, string new_val) {
    // something
};

void Product::modifyProduct(int id, long new_value) {
        // int new_id = sqldb.findID("PRODUCTS", "PRODUCT_NAME", "Fajki");
        quantity = new_value;
        sqldb.update("PRODUCTS", id, "QUANTITY", new_value);
};

void Product::modifyProduct(int id, float new_prize) {
        prize = new_prize;
};

void Product::modifyProduct(int id,int new_barcode) {
        barcode = new_barcode;
};