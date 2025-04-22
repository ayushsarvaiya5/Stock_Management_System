# Stock Management System

A simple, console-based stock management system in C designed for managing products in a small retail environment. The system supports two main roles: **Admin** and **Customer**. The admin can manage the stock, while customers can view products and make purchases. The data is stored securely with encryption, ensuring that only authorized users can access and modify the stock information.

## 🔐 Admin Login
- **Password:** `Password`

## 📦 Features

### 👨‍💼 Admin Functionalities:
- ➕ **Add** new products to the stock
- ✏️ **Update** existing product details
- ❌ **Delete** products from inventory
- 📥 **Restock** products (increase quantity)
- 📃 **View** all available products
- 🔐 **Encryption** of all data after any modification

### 🛒 Customer Functionalities:
- 👀 **View** available products with quantity and price
- 🧾 **Purchase** products and generate a real-time bill
- 💵 **See total cost** and quantity summary

### 🔒 Security:
- Product data is stored in a file (`stock.txt`) and **encrypted** for security.
- Encryption happens automatically after each admin operation.

## 🗃️ File Structure

- `Stock_Management_System.c` – Main source code file with full logic for admin and customer operations
- `stock.txt` – Encrypted file storing the product data
- `readme.md` – You're reading it 🙂


## Code Structure

### Function Prototypes
The following functions are used within the program:

- **`encryptFile(const char* filename)`**: Encrypts the stock file.
- **`decryptFile(const char* filename)`**: Decrypts the stock file.
- **`displayMenu()`**: Displays the main menu.
- **`displayCustomerMenu()`**: Displays the customer menu.
- **`addProductToBill()`**: Adds a product to the customer's bill.
- **`displayOwnerMenu()`**: Displays the admin menu.
- **`addProduct()`**: Adds a new product to the stock.
- **`updateProduct()`**: Updates product information.
- **`deleteProduct()`**: Deletes a product from the stock.
- **`displayAllProducts()`**: Displays all products in the stock.
- **`saveToFile()`**: Saves product data to a file.
- **`loadFromFile()`**: Loads product data from a file.
- **`restockProduct()`**: Restocks a product with additional quantity.
- **`generateBill()`**: Generates the final bill for the customer.

### Global Variables
- **`stock[1000]`**: Array storing all products in stock.
- **`bill[1000]`**: Array storing the customer's bill items.
- **`numProducts`**: Tracks the number of products in stock.
- **`numBillItems`**: Tracks the number of items in the bill.

### Encryption/Decryption
The encryption and decryption process ensures the security of stock data. The `encryptFile()` function performs encryption using XOR and a **shift amount** of 3. Similarly, the `decryptFile()` function reverses the process.

## 🛠️ How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/ayushsarvaiya5/Stock_Management_System.git
   cd Stock_Management_System

2. Compile the code
   ```bash
    gcc Stock_Management_System.c -o Stock_Management_System

3. Run the program
   ```bash
    ./Stock_Management_System
