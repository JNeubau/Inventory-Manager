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

void Product::modifyProduct(char* name, char* new_val, char* columnName) {
    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", name);
    int temp = 0;
    if (strcmp(columnName, "PRODUCT_NAME") == 0) temp = 1;
    if (strcmp(columnName, "PRODUCER_NAME") == 0) temp = 2;
    if (strcmp(columnName, "CATEGORY") == 0) temp = 3;
    switch(temp) {
        case 1:
            strcpy(productName, new_val);
            sqldb.update("PRODUCTS", id, "PRODUCT_NAME", new_val);
            break;
        case 2:
            strcpy(producerName, new_val);
            sqldb.update("PRODUCTS", id, "PRODUCER_NAME", new_val);
            break;
        case 3:
            strcpy(productCategory, new_val);
            sqldb.update("PRODUCTS", id, "CATEGORY", new_val);
            break;
        default:
            break;
    }
};

void Product::modifyProduct(char* name, long new_value) {
        int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", name);
        quantity = new_value;
        sqldb.update("PRODUCTS", id, "QUANTITY", new_value);
};

void Product::modifyProduct(char* name, float new_prize) {
    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", name);
    prize = new_prize;
    sqldb.update("PRODUCTS", id, "PRIZE", new_prize);
};

void Product::modifyProduct(char* name, int new_barcode) {
    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", name);
    barcode = new_barcode;
    sqldb.update("PRODUCTS", id, "PRIZE", (long)new_barcode);
};