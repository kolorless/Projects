//CSE 1320 FINAL PROJECT -- DRUG STORE MANAGEMENT SYSTEM -- 
//Comments are added to make it easy for the class to understand the program.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DRUGS 1000
#define MAX_NAME_LENGTH 100
#define MAX_DESC_LENGTH 100
#define TAX_RATE 0.08 //This is to add a mock tax rate of 8% which can obviously be changed depending on the location.

struct Drug // Struct to represent information of a drug.
{
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    float price;
    int quantity;
};

int num_drugs=0;
struct Drug drugs[MAX_DRUGS];
int cart[MAX_DRUGS][2];
int cart_size=0;
int cart_quantity[MAX_DRUGS]={0};

// All the functions that are going to be used in the program :
void display_drugs();
void add_to_cart(int drug_id, int quantity);
void remove_from_cart(int drug_id, int quantity);
void display_cart();
void checkout();
float calculate_total(int cart[][2], int cart_size);

int main() {
    int choice, drug_id, quantity;
    int cashorcard;

    struct Drug demo_drugs[] = {
        {1, "Paracetamol", "Pain reliever", 2.5, 50},
        {2, "Ibuprofen", "Anti-inflammatory", 3.0, 40},
        {3, "Aspirin", "Blood thinner", 1.8, 60},
        {4, "Omeprazole", "Antacid", 4.5, 30},
        {5, "Loratadine", "Antihistamine", 3.2, 20},
        {6, "Mortar-LC", "To stop flared up Sinus", 6.9, 100},
        {7, "Meftal-Spas", "Stop Stomach-ache", 2.0, 70},
        {8, "Flomist", "Prevent Nose-Bleeding", 4.2, 55},
        {9, "Dettol", "Disinfectant", 2.0, 90},
        {10, "Benadryl", "Cure chest congestion", 3.9, 10}
    };
    
    int num_demo_drugs = sizeof(demo_drugs) / sizeof(demo_drugs[0]); // Calculate the number of demo drugs used in the program.

    for (int i=0; i<num_demo_drugs; i++) // Copy demo drugs to the drugs array
    {     
        drugs[i] = demo_drugs[i];
    }

    num_drugs = num_demo_drugs;

    // Main menu loop
    while (1) 
    {
        printf("\n-- Drug Store Management System --\n");
        printf("1. Display Available Drugs\n");
        printf("2. Add Drugs to Cart\n");
        printf("3. Remove Drugs from Cart\n");
        printf("4. View Cart\n");
        printf("5. Checkout\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) //Switch used for ease of choice.
        {
            case 1:
                display_drugs();
                break;
                
            case 2:
                printf("Enter Drug ID: ");
                scanf("%d", &drug_id);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);
                add_to_cart(drug_id - 1, quantity);  // Adjusting index.
                break;
                
            case 3:
                printf("Enter Drug ID (from cart): ");
                scanf("%d", &drug_id);
                printf("Enter Quantity to Remove: ");
                scanf("%d", &quantity);
                remove_from_cart(drug_id - 1, quantity);  // Adjusting index like in case 2.
                break;
                
            case 4:
                display_cart();
                break;
                
            case 5:
                checkout();
                printf("Please follow the checkout procedure below: \n");
                printf("Press 1 to pay by Cash or press 2 to pay by Card?: ");
                scanf("%d", &cashorcard);
                if(cashorcard==1)
                {
                    printf("An employee will be attending you shortly to collect the cash.\n");
                    printf("Have a good day.");
                    exit(0);
                }
                else
                {
                    printf("Please tap or insert your card in the machine on your right hand side.\n");
                    printf("Have a good day.");
                    exit(0);
                }
                break;
                
            case 6:
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
} //End of int main() now. Codes for different functions are writte below: 

// Function to display available drugs
void display_drugs() 
{
    printf("\n** Available Drugs **\n");
    printf("ID | Name                 | Description                                        | Price  | Quantity\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    for (int i=0; i<num_drugs; i++) 
    {
        printf("%-2d | %-20s | %-50s | %.2f\t| %d\n", drugs[i].id, drugs[i].name, drugs[i].description, drugs[i].price, drugs[i].quantity - cart_quantity[i]);
    }
}

// Function to add drugs to the cart
void add_to_cart(int drug_id, int quantity) 
{

    if (drug_id<0 || drug_id>=num_drugs) 
    {
        printf("Invalid drug ID.\n");
        return;
    }
    if (quantity<=0) 
    {
        printf("Invalid quantity.\n");
        return;
    }
    if (drugs[drug_id].quantity-cart_quantity[drug_id] < quantity) 
    {
        printf("Insufficient quantity in stock.\n");
        return;
    }

    // Add drug to cart
    cart[cart_size][0]=drug_id;
    cart[cart_size][1]=quantity;
    cart_size++;
    cart_quantity[drug_id]+=quantity;

    printf("Drug successfuly added to cart.\n");
}

// Function to remove drugs from the cart
void remove_from_cart(int drug_id, int quantity) 
{

    int index=-1;
    for (int i=0; i<cart_size; i++) 
    {
        if (cart[i][0] == drug_id) 
        {
            index=i;
            break;
        }
    }

    // If the drug is not found in the cart
    if (index == -1) 
    {
        printf("Drug not found in cart.\n");
        return;
    }

    // Check if the quantity to remove is valid
    if (quantity<=0 || quantity>cart[index][1]) 
    {
        printf("Invalid quantity.\n");
        return;
    }

    // Update the quantity in the cart
    cart[index][1] -= quantity;
    cart_quantity[drug_id] -= quantity;

    // If the quantity becomes zero, remove the drug entry from the cart
    if (cart[index][1] == 0) 
    {
        for (int i=index; i<cart_size - 1; i++) 
        {
            cart[i][0] = cart[i+ 1][0];
            cart[i][1] = cart[i+ 1][1];
        }
        cart_size--;
    }

    printf("Drug removed from cart.\n");
}

// Function to display the cart
void display_cart() 
{
    printf("\n** Cart **\n");
    printf("ID | Name                 | Description                                        | Price  | Quantity\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    
    float total = 0;
    for (int i=0; i<cart_size; i++) 
    {
        int id = cart[i][0];
        int quantity = cart[i][1];
        printf("%-2d | %-20s | %-50s | %.2f\t| %d\n", drugs[id].id, drugs[id].name, drugs[id].description, drugs[id].price, quantity);
        total += drugs[id].price * quantity;
    }
    
    if (cart_size == 0){
        printf("Cart Empty\n\n");
    }
    
    total *= (1 + TAX_RATE);     // Adding  tax
    printf("Total (+ 8%% Texas State Tax): %.2f\n", total);
}

// Performing checkout
void checkout() 
{
    printf("\n-- Checkout --\n");
    display_cart();
    printf("Total amount to pay (+ 8%% Texas State Tax): %.2f\n", calculate_total(cart, cart_size)*(1 + TAX_RATE));

    for (int i = 0; i < cart_size; i++) 
    {
        int id = cart[i][0];
        int quantity = cart[i][1];
        drugs[id].quantity -= quantity;
    }

    cart_size = 0; //This is to empty the cart afterwards.
    memset(cart_quantity, 0, sizeof(cart_quantity));

    printf("Thank you for shopping with us!\n");
}

// Function to calculate the total cost
float calculate_total(int cart[][2], int cart_size) 
{
    float total = 0;
    for (int i=0; i<cart_size; i++) 
    {
        int id = cart[i][0];
        int quantity = cart[i][1];
        total += drugs[id].price * quantity;
    }
    return total;
} //End of code.