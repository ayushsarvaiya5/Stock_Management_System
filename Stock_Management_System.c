
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Product {
    int id;
    char name[100];
    float price;
    int quantity;
};

struct BillingItem {
    int productId;
    char productName[100];
    float productPrice;
    int quantity;
};

// Function prototypes
int encryptFile(const char* filename);
int decryptFile(const char* filename);
void displayMenu();
void displayCustomerMenu();
void addProductToBill();
void displayOwnerMenu();
void addProduct();
void updateProduct();
void deleteProduct();
void displayAllProducts();
void searchProduct();
void saveToFile();
void loadFromFile();
void sortByPrice();
void sortByQuantity();
void searchByName();
void restockProduct();
void checkLowStockItems();
void generateReports();
void generateBill();
void updateStockToFile();
float calculateTotalStockValue();
void findHighestPricedItem();
void findLowestPricedItem();
void findTopSellingItems();
int isProductIDExists(int id);

// Global variables
struct Product stock[1000];
struct BillingItem bill[1000];
int numProducts = 0;
int numBillItems = 0;
const int SHIFT_AMOUNT = 3;

int main() {
    // Load existing stock data from a file
    decryptFile("stock.txt");
    loadFromFile();
    encryptFile("stock.txt");

    int choice;
    char password[50];

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCustomerMenu();
                break;
            case 2:
                printf("Enter the owner password: ");
                scanf("%s", password);
                if (strcmp(password, "Password") == 0) {
                    displayOwnerMenu();
                } else {
                    printf("Invalid password! Access denied.\n");
                }
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                encryptFile("stock.txt");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
	
	encryptFile("stock.txt");
	
    return 0;
}

int encryptFile(const char* filename) {
  FILE* input = fopen(filename, "rb");
  if (!input) {
    fprintf(stderr, "Error opening file: %s\n", filename);
    return 1;
  }

  // Create temporary filename for encrypted data
  char temp_filename[strlen(filename) + 5];
  strcpy(temp_filename, filename);
  strcat(temp_filename, ".tmp");
  FILE* output = fopen(temp_filename, "wb");

  char c;
  while (fread(&c, 1, 1, input) > 0) {
    // XOR each character with the shift amount
    c ^= SHIFT_AMOUNT;
    fwrite(&c, 1, 1, output);
  }

  fclose(input);
  fclose(output);

  // Replace original file with encrypted version
  if (remove(filename) != 0) {
    fprintf(stderr, "Error deleting original file: %s\n", filename);
    return 1;
  }
  if (rename(temp_filename, filename) != 0) {
    fprintf(stderr, "Error renaming temporary file: %s\n", temp_filename);
    return 1;
  }

  // printf("File encrypted successfully!\n");
  return 0;
}

int decryptFile(const char* filename) {
  FILE* input = fopen(filename, "rb");
  if (!input) {
    fprintf(stderr, "Error opening file: %s\n", filename);
    return 1;
  }

  // Create temporary filename for decrypted data
  char temp_filename[strlen(filename) + 5];
  strcpy(temp_filename, filename);
  strcat(temp_filename, ".tmp");
  FILE* output = fopen(temp_filename, "wb");

  char c;
  while (fread(&c, 1, 1, input) > 0) {
    // XOR again to undo encryption
    c ^= SHIFT_AMOUNT;
    fwrite(&c, 1, 1, output);
  }

  fclose(input);
  fclose(output);

  // Replace original file with decrypted version
  if (remove(filename) != 0) {
    fprintf(stderr, "Error deleting original file: %s\n", filename);
    return 1;
  }
  if (rename(temp_filename, filename) != 0) {
    fprintf(stderr, "Error renaming temporary file: %s\n", temp_filename);
    return 1;
  }

  // printf("File decrypted successfully!\n");
  return 0;
}

void displayMenu() {
    printf("\n===== Stock Management Menu =====\n");
    printf("1. Customer Partition\n");
    printf("2. Owner Partition\n");
    printf("3. Exit\n");
    printf("=================================\n");
}

void displayCustomerMenu() {
    printf("\n===== Customer Partition =====\n");
    printf("1. Add Product to Bill\n");
    printf("2. Generate Bill\n");
    printf("3. Back to Main Menu\n");
    printf("==============================\n");

    int choice;
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addProductToBill();
                break;
            case 2:
                generateBill();
                saveToFile();
                encryptFile("stock.txt");
                break;
            case 3:
                printf("Exiting Customer Partition. Returning to Main Menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

void displayOwnerMenu() {
    printf("\n===== Owner Partition =====\n");
    printf("1. Add Product\n");
    printf("2. Update Product\n");
    printf("3. Delete Product\n");
    printf("4. Display All Products\n");
    printf("5. Search Product\n");
    printf("6. Save to File\n");
    printf("7. Sort by Price\n");
    printf("8. Sort by Quantity\n");
    printf("9. Search by Name\n");
    printf("10. Restock Product\n");
    printf("11. Check Low Stock Items\n");
    printf("12. Reports and Analytics\n");
    printf("13. Back to Main Menu\n");
    printf("===========================\n");

    int choice;
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                displayAllProducts();
                break;
            case 5:
                searchProduct();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                sortByPrice();
                break;
            case 8:
                sortByQuantity();
                break;
            case 9:
                searchByName();
                break;
            case 10:
                restockProduct();
                break;
            case 11:
                checkLowStockItems();
                break;
            case 12:
                generateReports();
                break;
            case 13:
                printf("Exiting Owner Partition. Returning to Main Menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 13);
}
void addProductToBill() {
    int idToAdd, quantityToAdd, found = 0;

    printf("\nAdding products to the bill. Enter 0 to finish.\n");
    printf("Enter product ID to add to the bill: ");

    while (1) {
        scanf("%d", &idToAdd);

        if (idToAdd == 0) {
            break;
        }

        found = 0;
        for (int i = 0; i < numProducts; i++) {
            if (stock[i].id == idToAdd) {
                printf("Enter quantity to add: ");
                scanf("%d", &quantityToAdd);
if (quantityToAdd <= stock[i].quantity) {
                    struct BillingItem item;
                    item.productId = stock[i].id;
                    strcpy(item.productName, stock[i].name);
                    item.productPrice = stock[i].price;
                    item.quantity = quantityToAdd;

                    bill[numBillItems] = item;
                    numBillItems++;

                    stock[i].quantity -= quantityToAdd;

                    printf("Product added to the bill successfully!\n");
                } else {
                    printf("Insufficient quantity in stock!\n");
                }

                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Product with ID %d not found in stock!\n", idToAdd);
        }

        printf("Enter product ID to add to the bill (0 to finish): ");
    }

    printf("Products added to the bill. Choose 'Generate Bill' to view the final bill.\n");
}

void addProduct() {
    struct Product newProduct;
    printf("\nEnter Product ID: ");
    scanf("%d", &newProduct.id);

    // Check if the product ID already exists
    if (isProductIDExists(newProduct.id)) {
        printf("Product with ID %d already exists. Please enter a different ID.\n", newProduct.id);
        return;
    }

    printf("Enter Product Name: ");
    scanf("%s", newProduct.name);
    printf("Enter Product Price: ");
    scanf("%f", &newProduct.price);
    printf("Enter Product Quantity: ");
    scanf("%d", &newProduct.quantity);

    // Add the new product to the stock array
    stock[numProducts] = newProduct;
    numProducts++;
    
    saveToFile();
    encryptFile("stock.txt");

    printf("Product added successfully!\n");
}

void updateProduct() {
    int idToUpdate, found = 0;
    printf("\nEnter the ID of the product to update: ");
    scanf("%d", &idToUpdate);

    for (int i = 0; i < numProducts; i++) {
        if (stock[i].id == idToUpdate) {
            printf("Enter new Product Name: ");
            scanf("%s", stock[i].name);
            printf("Enter new Product Price: ");
            scanf("%f", &stock[i].price);
            printf("Enter new Product Quantity: ");
            scanf("%d", &stock[i].quantity);
            printf("Product updated successfully!\n");
            found = 1;

            saveToFile();
            encryptFile("stock.txt");

            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found!\n", idToUpdate);
    }
}

void deleteProduct() {
    int idToDelete, found = 0;
    printf("\nEnter the ID of the product to delete: ");
    scanf("%d", &idToDelete);

    for (int i = 0; i < numProducts; i++) {
        if (stock[i].id == idToDelete) {
            // Shift the elements to the left to delete the product
            for (int j = i; j < numProducts - 1; j++) {
                stock[j] = stock[j + 1];
            }
            numProducts--;
            printf("Product deleted successfully!\n");
            found = 1;

            saveToFile();
            encryptFile("stock.txt");

            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found!\n", idToDelete);
    }
}

void displayAllProducts() {
    if (numProducts == 0) {
        printf("No products in stock!\n");
    } else {
        printf("\n===== Stock List =====\n");
        printf("ID\tName\t\tPrice\t\tQuantity\n");
        for (int i = 0; i < numProducts; i++) {
            printf("%d\t%s\t\t%.2f\t\t%d\n", stock[i].id, stock[i].name, stock[i].price, stock[i].quantity);
        }
        printf("=======================\n");
    }
}

void searchProduct() {
    int idToSearch, found = 0;
    printf("\nEnter the ID of the product to search: ");
    scanf("%d", &idToSearch);

    for (int i = 0; i < numProducts; i++) {
        if (stock[i].id == idToSearch) {
            printf("Product found:\n");
            printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n", stock[i].id, stock[i].name, stock[i].price, stock[i].quantity);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found!\n", idToSearch);
    }
}

void saveToFile() {
    FILE *file = fopen("stock.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%d %s %.2f %d\n", stock[i].id, stock[i].name, stock[i].price, stock[i].quantity);
    }
    
	
    fclose(file);
    printf("Stock data saved to file successfully!\n");
}

void loadFromFile() {
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL) {
        return; // If the file doesn't exist or is not accessible, simply return
    }

    while (fscanf(file, "%d %s %f %d", &stock[numProducts].id, stock[numProducts].name, &stock[numProducts].price, &stock[numProducts].quantity) != EOF) {
        numProducts++;
    }

    fclose(file);
}

void sortByPrice() {
    // Implement sorting by price using bubble sort
    for (int i = 0; i < numProducts - 1; i++) {
        for (int j = 0; j < numProducts - i - 1; j++) {
            if (stock[j].price > stock[j + 1].price) {
                // Swap the products
                struct Product temp = stock[j];
                stock[j] = stock[j + 1];
                stock[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by price in ascending order.\n");
}

void sortByQuantity() {
    // Implement sorting by quantity using bubble sort
    for (int i = 0; i < numProducts - 1; i++) {
        for (int j = 0; j < numProducts - i - 1; j++) {
            if (stock[j].quantity > stock[j + 1].quantity) {
                // Swap the products
                struct Product temp = stock[j];
                stock[j] = stock[j + 1];
                stock[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by quantity in ascending order.\n");
}

void searchByName() {
    char nameToSearch[100];
    int found = 0;

    printf("\nEnter the name of the product to search: ");
    scanf("%s", nameToSearch);

    for (int i = 0; i < numProducts; i++) {
        if (strcmp(stock[i].name, nameToSearch) == 0) {
            printf("Product found:\n");
            printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n", stock[i].id, stock[i].name, stock[i].price, stock[i].quantity);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product with name '%s' not found!\n", nameToSearch);
    }
}

void restockProduct() {
    int idToRestock, quantityToAdd, found = 0;
    printf("\nEnter the ID of the product to restock: ");
    scanf("%d", &idToRestock);

    for (int i = 0; i < numProducts; i++) {
        if (stock[i].id == idToRestock) {
            printf("Enter the quantity to add: ");
            scanf("%d", &quantityToAdd);
            stock[i].quantity += quantityToAdd;
            printf("Product restocked successfully!\n");
            found = 1;

            saveToFile();
            encryptFile("stock.txt");
            
            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found!\n", idToRestock);
    }
}

void checkLowStockItems() {
    int threshold;
    printf("\nEnter the minimum stock threshold: ");
    scanf("%d", &threshold);

    printf("\nLow Stock Items:\n");
    printf("ID\tName\t\tPrice\t\tQuantity\n");
    for (int i = 0; i < numProducts; i++) {
        if (stock[i].quantity < threshold) {
            printf("%d\t%s\t\t%.2f\t\t%d\n", stock[i].id, stock[i].name, stock[i].price, stock[i].quantity);
        }
    }
    printf("=======================\n");
}

// Reports and Analytics

void generateReports() {
    int reportChoice;

    printf("\n===== Reports and Analytics =====\n");
    printf("1. Total Stock Value\n");
    printf("2. Highest Priced Item\n");
    printf("3. Lowest Priced Item\n");
    printf("4. Top Selling Items\n");
    printf("5. Back to Main Menu\n");
    printf("=================================\n");

    printf("Enter your choice: ");
    scanf("%d", &reportChoice);

    switch (reportChoice) {
        case 1:
            // Report: Total Stock Value
            {
                float totalValue = calculateTotalStockValue();
                printf("Total Stock Value: %.2f\n", totalValue);
                break;
            }
        case 2:
            // Report: Highest Priced Item
            findHighestPricedItem();
            break;
        case 3:
            // Report: Lowest Priced Item
            findLowestPricedItem();
            break;
        case 4:
            // Report: Top Selling Items
            findTopSellingItems();
            break;
        case 5:
            // Back to main menu
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

float calculateTotalStockValue() {
    float totalValue = 0;
    for (int i = 0; i < numProducts; i++) {
        totalValue += stock[i].price * stock[i].quantity;
    }
    return totalValue;
}

void findHighestPricedItem() {
        if (numProducts == 0) {
        printf("No products in stock!\n");
    } else {
        struct Product highestPricedItem = stock[0];
        for (int i = 1; i < numProducts; i++) {
            if (stock[i].price > highestPricedItem.price) {
                highestPricedItem = stock[i];
            }
        }

        printf("Highest Priced Item:\n");
        printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n", highestPricedItem.id, highestPricedItem.name, highestPricedItem.price, highestPricedItem.quantity);
    }
}

void findLowestPricedItem() {
    if (numProducts == 0) {
        printf("No products in stock!\n");
    } else {
        struct Product lowestPricedItem = stock[0];
        for (int i = 1; i < numProducts; i++) {
            if (stock[i].price < lowestPricedItem.price) {
                lowestPricedItem = stock[i];
            }
        }

        printf("Lowest Priced Item:\n");
        printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\n", lowestPricedItem.id, lowestPricedItem.name, lowestPricedItem.price, lowestPricedItem.quantity);
    }
}

void findTopSellingItems() {
    int numTopItems;
    printf("Enter the number of top-selling items to display: ");
    scanf("%d", &numTopItems);

    if (numProducts == 0) {
        printf("No products in stock!\n");
    } else if (numTopItems > numProducts || numTopItems <= 0) {
        printf("Invalid number of top-selling items to display!\n");
    } else {
        // Implement finding top-selling items
        // Sorting by quantity in descending order using bubble sort
        for (int i = 0; i < numProducts - 1; i++) {
            for (int j = 0; j < numProducts - i - 1; j++) {
                if (stock[j].quantity < stock[j + 1].quantity) {
                    // Swap the products
                    struct Product temp = stock[j];
                    stock[j] = stock[j + 1];
                    stock[j + 1] = temp;
                }
            }
        }

        printf("Top %d Selling Items:\n", numTopItems);
        printf("ID\tName\t\tPrice\t\tQuantity\n");
        for (int i = 0; i < numTopItems; i++) {
            printf("%d\t%s\t\t%.2f\t\t%d\n", stock[i].id, stock[i].name, stock[i].price, stock[i].quantity);
        }
        printf("=======================\n");
    }
}

// Billing and Customer Partition

void generateBill() {
    if (numBillItems == 0) {
        printf("No products added to the bill!\n");
        return;
    }

    struct tm* timeInfo;
    time_t currentTime;

    currentTime = time(NULL);
    timeInfo = localtime(&currentTime);

    printf("\n===== Bill =====\n");
    printf("Date: %02d/%02d/%d\n", timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year + 1900);
    printf("Day of the Week: ");
    switch (timeInfo->tm_wday) {
        case 0:
            printf("Sunday\n");
            break;
        case 1:
            printf("Monday\n");
            break;
        case 2:
        printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        default:
            printf("Unknown\n");
    }
    printf("Time: %02d:%02d:%02d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);

float totalAmount = 0.0;
    printf("\nID\tName\t\tPrice\t\tQuantity\tTotal\n");
    for (int i = 0; i < numBillItems; i++) {
        float subTotal = bill[i].productPrice * bill[i].quantity;
        printf("%d\t%s\t\t%.2f\t\t%d\t\t%.2f\n", bill[i].productId, bill[i].productName, bill[i].productPrice, bill[i].quantity, subTotal);
        totalAmount += subTotal;
    }
    printf("=========================================\n");
    printf("Total Amount: %.2f\n", totalAmount);
}


void updateStockToFile() {
    FILE *file = fopen("stock.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%d %s %.2f %d\n", stock[i].id, stock[i].name, stock[i].price, stock[i].quantity);
    }

    fclose(file);
}


int isProductIDExists(int id) {
    for (int i = 0; i < numProducts; i++) {
        if (stock[i].id == id) {
          return 1;
        }
    }
    return 0;
}
    