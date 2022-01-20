#include "headers/database.h"
#include "headers/global_variables.h"
#include "headers/product.h"


Product::~Product() {            // dekonstructor
    free(productName);
    free(producerName);
    free(productCategory);
};

void Product::deleteProduct(string name) {
    char *temp = (char *) (malloc(sizeof(char)));
    strcpy(temp, name.data());
    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", temp);
    sqldb.deleteRow("PRODUCTS", id);
};

void Product::deleteProduct(int barcode) {
    int id = sqldb.find("PRODUCTS", "BARCODE", barcode);
    sqldb.deleteRow("PRODUCTS", id);
};

void Product::addNewProduct(string name, long number, float money, int code, string producer, string category) {   // nowy produkt
        ID = sqldb.nextId("PRODUCTS");
        // TODO [comment]: ten kod powinien być w interface.cpp, żeby trzymać się spójności
        // TODO [comment]: przydałaby się też walidacja, czy dany produkt już nie istnieje w bazie
        quantity = number;
        prize = money;
        barcode = code;

        strcpy(productName, name.data());
        strcpy(producerName, producer.data());
        strcpy(productCategory, category.data());

        sqldb.insertData(ID, productName, prize, quantity, barcode, producerName, productCategory);
};

void Product::modifyProduct(string name, string new_val, string columnName) {
    char *tempName = (char *) (malloc(sizeof(char)));
    strcpy(tempName, name.data());
    char *tempCol = (char *) (malloc(sizeof(char)));
    strcpy(tempCol, columnName.data());
    char *tempNew = (char *) (malloc(sizeof(char)));
    strcpy(tempNew, new_val.data());

    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", tempName);
    int temp = 0;
    if (strcmp(tempCol, "PRODUCT_NAME") == 0) temp = 1;
    if (strcmp(tempCol, "PRODUCER_NAME") == 0) temp = 2;
    if (strcmp(tempCol, "CATEGORY") == 0) temp = 3;
    switch(temp) {
        case 1:
            sqldb.update("PRODUCTS", id, "PRODUCT_NAME", tempNew);
            break;
        case 2:
            sqldb.update("PRODUCTS", id, "PRODUCER_NAME", tempNew);
            break;
        case 3:
            sqldb.update("PRODUCTS", id, "CATEGORY", tempNew);
            break;
        default:
            break;
    }
};

void Product::modifyProduct(string name, long new_value) {
    char *tempName = (char *) (malloc(sizeof(char)));
    strcpy(tempName, name.data());

    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", tempName);
    sqldb.update("PRODUCTS", id, "QUANTITY", new_value);
};

void Product::modifyProduct(string name, float new_prize) {
    char *temp = (char *) (malloc(sizeof(char)));
    strcpy(temp, name.data());

    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", temp);
    sqldb.update("PRODUCTS", id, "PRIZE", new_prize);
};

void Product::modifyProduct(string name, int new_barcode) {
    char *temp = (char *) (malloc(sizeof(char)));
    strcpy(temp, name.data());

    int id = sqldb.find("PRODUCTS", "PRODUCT_NAME", temp);
    sqldb.update("PRODUCTS", id, "PRIZE", (long)new_barcode);
};