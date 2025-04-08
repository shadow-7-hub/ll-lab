#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Employee {
    int id;
    char name[100];
    int age;
    char gender[10];
    char shift[10];
    char email[100];
    char contact[15];
    float salary;
    char blood_group[5];
    char role[20]; // "admin" or "user"
    char username[50];
    char password[50];
    struct Employee *next;
} Employee;

typedef struct TreeNode {
    Employee *emp;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct GraphNode {
    int emp_id;
    struct GraphNode *next;
} GraphNode;

Employee *head = NULL; // Linked List
TreeNode *root = NULL; // BST
GraphNode **graph = NULL; // Graph (Adjacency List)
int graph_size = 10; // Max employees for demo
Employee *current_user = NULL;

// Function Prototypes
void addEmployee(int id, char *name, int age, char *gender, char *shift, char *email, char *contact, float salary, char *blood_group, char *role, char *username, char *password);
void addEmployeeToTree(Employee *emp);
void addEmployeeToGraph(int supervisor_id, int supervised_id);
Employee* searchEmployee(int id);
void deleteEmployee(int id);
void displayAllEmployees();
void saveToFile(const char *filename);
void loadFromFile(const char *filename);
void deleteFile(const char *filename);
void displayGraph();
void initializeDemoData();
bool login(char *role);
void adminMenu();
void userMenu();
void changePassword();

int main() {
    graph = (GraphNode **)malloc(graph_size * sizeof(GraphNode *));
    for (int i = 0; i < graph_size; i++) graph[i] = NULL;

    initializeDemoData(); // Add demo data

    while (1) {
        printf("\nEmployee Record Management System\n");
        printf("1. Login as Admin\n");
        printf("2. Login as User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (login("admin")) {
                    adminMenu();
                    current_user = NULL;
                }
                break;
            case 2:
                if (login("user")) {
                    userMenu();
                    current_user = NULL;
                }
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void initializeDemoData() {
    // Demo Admin
    addEmployee(1, "Admin", 30, "Male", "Day", "admin@company.com", "1234567890", 10000.0, "O+", "admin", "admin", "admin123");
    // Demo Employees
    addEmployee(2, "John Doe", 28, "Male", "Day", "john@company.com", "9876543210", 5000.0, "A+", "user", "john", "john123");
    addEmployee(3, "Jane Smith", 32, "Female", "Night", "jane@company.com", "8765432109", 6000.0, "B+", "user", "jane", "jane123");
    // Supervisory Relationship (Jane supervises John)
    addEmployeeToGraph(3, 2);
}

void addEmployee(int id, char *name, int age, char *gender, char *shift, char *email, char *contact, float salary, char *blood_group, char *role, char *username, char *password) {
    Employee *newEmp = (Employee *)malloc(sizeof(Employee));
    newEmp->id = id;
    strcpy(newEmp->name, name);
    newEmp->age = age;
    strcpy(newEmp->gender, gender);
    strcpy(newEmp->shift, shift);
    strcpy(newEmp->email, email);
    strcpy(newEmp->contact, contact);
    newEmp->salary = salary;
    strcpy(newEmp->blood_group, blood_group);
    strcpy(newEmp->role, role);
    strcpy(newEmp->username, username);
    strcpy(newEmp->password, password);
    newEmp->next = head;
    head = newEmp;

    addEmployeeToTree(newEmp); // Add to BST
    printf("Employee added successfully!\n");
}

void addEmployeeToTree(Employee *emp) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->emp = emp;
    newNode->left = newNode->right = NULL;

    if (root == NULL) root = newNode;
    else {
        TreeNode *current = root;
        while (1) {
            if (emp->id < current->emp->id) {
                if (current->left == NULL) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            } else {
                if (current->right == NULL) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
        }
    }
}

void addEmployeeToGraph(int supervisor_id, int supervised_id) {
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    newNode->emp_id = supervised_id;
    newNode->next = NULL;

    int index = supervisor_id % graph_size;
    if (graph[index] == NULL) graph[index] = newNode;
    else {
        GraphNode *temp = graph[index];
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
}

Employee* searchEmployee(int id) {
    TreeNode *current = root;
    while (current != NULL) {
        if (id == current->emp->id) return current->emp;
        else if (id < current->emp->id) current = current->left;
        else current = current->right;
    }
    return NULL;
}

void deleteEmployee(int id) {
    // Delete from Linked List
    Employee *current = head, *prev = NULL;
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Employee not found!\n");
        return;
    }
    if (prev == NULL) head = current->next;
    else prev->next = current->next;

    // Delete from BST
    TreeNode *parent = NULL, *currentTree = root;
    while (currentTree != NULL && currentTree->emp->id != id) {
        parent = currentTree;
        if (id < currentTree->emp->id) currentTree = currentTree->left;
        else currentTree = currentTree->right;
    }
    if (currentTree == NULL) {
        printf("Employee not found in tree!\n");
        return;
    }
    // Node with 0 or 1 child
    if (currentTree->left == NULL) {
        if (parent == NULL) root = currentTree->right;
        else if (parent->left == currentTree) parent->left = currentTree->right;
        else parent->right = currentTree->right;
        free(currentTree);
    } else if (currentTree->right == NULL) {
        if (parent == NULL) root = currentTree->left;
        else if (parent->left == currentTree) parent->left = currentTree->left;
        else parent->right = currentTree->left;
        free(currentTree);
    } else {
        // Node with 2 children: Get inorder successor
        TreeNode *successor = currentTree->right;
        while (successor->left != NULL) successor = successor->left;
        Employee *temp = successor->emp;
        deleteEmployee(successor->emp->id); // Recursively delete successor
        currentTree->emp = temp;
    }
    printf("Employee deleted successfully!\n");
}

void displayAllEmployees() {
    printf("\nAll Employees:\n");
    printf("ID\tName\t\tAge\tGender\tShift\tSalary\tEmail\t\tContact\t\tBlood Group\n");
    printf("----------------------------------------------------------------------------------------\n");
    Employee *current = head;
    while (current != NULL) {
        printf("%d\t%s\t\t%d\t%s\t%s\t%.2f\t%s\t%s\t%s\n",
               current->id, current->name, current->age, current->gender,
               current->shift, current->salary, current->email, current->contact, current->blood_group);
        current = current->next;
    }
}

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "Employee Records:\n");
    fprintf(file, "=================\n\n");
    Employee *current = head;
    int serial = 1;
    while (current != NULL) {
        fprintf(file, "%d. ID: %d, Name: %s, Age: %d, Gender: %s, Shift: %s, Email: %s, Contact: %s, Salary: %.2f, Blood Group: %s, Role: %s, Username: %s, Password: %s\n",
                serial++, current->id, current->name, current->age, current->gender,
                current->shift, current->email, current->contact, current->salary,
                current->blood_group, current->role, current->username, current->password);
        current = current->next;
    }
    fclose(file);
    printf("Data saved to %s successfully!\n", filename);
}

void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char line[500];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "ID:") != NULL) {
            int id, age, serial;
            char name[100], gender[10], shift[10], email[100], contact[15], blood_group[5], role[20], username[50], password[50];
            float salary;
            sscanf(line, "%d. ID: %d, Name: %[^,], Age: %d, Gender: %[^,], Shift: %[^,], Email: %[^,], Contact: %[^,], Salary: %f, Blood Group: %[^,], Role: %[^,], Username: %[^,], Password: %s",
                   &serial, &id, name, &age, gender, shift, email, contact, &salary, blood_group, role, username, password);
            addEmployee(id, name, age, gender, shift, email, contact, salary, blood_group, role, username, password);
        }
    }
    fclose(file);
    printf("Data loaded from %s successfully!\n", filename);
}

void deleteFile(const char *filename) {
    if (remove(filename) == 0) printf("File %s deleted successfully!\n", filename);
    else printf("Error deleting file!\n");
}

void displayGraph() {
    printf("\nSupervisory Relationships:\n");
    for (int i = 0; i < graph_size; i++) {
        if (graph[i] != NULL) {
            Employee *supervisor = searchEmployee(i);
            if (supervisor == NULL) continue;
            printf("%s (ID: %d) supervises: ", supervisor->name, i);
            GraphNode *current = graph[i];
            while (current != NULL) {
                Employee *emp = searchEmployee(current->emp_id);
                if (emp != NULL) printf("%s (ID: %d), ", emp->name, emp->id);
                current = current->next;
            }
            printf("\n");
        }
    }
}

bool login(char *role) {
    char username[50], password[50];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    Employee *current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0 && strcmp(current->role, role) == 0) {
            current_user = current;
            printf("Login successful! Welcome, %s.\n", current->name);
            return true;
        }
        current = current->next;
    }
    printf("Invalid credentials or insufficient privileges.\n");
    return false;
}

void adminMenu() {
    while (1) {
        printf("\nAdmin Menu\n");
        printf("1. Add Employee\n");
        printf("2. Search Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Save Data to File\n");
        printf("5. Load Data from File\n");
        printf("6. Delete Data File\n");
        printf("7. Display All Employees\n");
        printf("8. Display Supervisory Graph\n");
        printf("9. Change Password\n");
        printf("10. Logout\n");
        printf("Enter your choice: ");

        int choice, id, age;
        char name[100], gender[10], shift[10], email[100], contact[15], blood_group[5], filename[50], new_password[50], username[50], password[50];
        float salary;

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Age: ");
                scanf("%d", &age);
                printf("Enter Gender: ");
                scanf("%s", gender);
                printf("Enter Shift: ");
                scanf("%s", shift);
                printf("Enter Email: ");
                scanf("%s", email);
                printf("Enter Contact: ");
                scanf("%s", contact);
                printf("Enter Salary: ");
                scanf("%f", &salary);
                printf("Enter Blood Group: ");
                scanf("%s", blood_group);
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                addEmployee(id, name, age, gender, shift, email, contact, salary, blood_group, "user", username, password);
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                Employee *emp = searchEmployee(id);
                if (emp != NULL) {
                    printf("\nEmployee Found:\n");
                    printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nShift: %s\nEmail: %s\nContact: %s\nSalary: %.2f\nBlood Group: %s\nUsername: %s\n",
                           emp->id, emp->name, emp->age, emp->gender, emp->shift, emp->email, emp->contact, emp->salary, emp->blood_group, emp->username);
                } else printf("Employee not found!\n");
                break;
            case 3:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                deleteEmployee(id);
                break;
            case 4:
                printf("Enter filename to save: ");
                scanf("%s", filename);
                saveToFile(filename);
                break;
            case 5:
                printf("Enter filename to load: ");
                scanf("%s", filename);
                loadFromFile(filename);
                break;
            case 6:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(filename);
                break;
            case 7:
                displayAllEmployees();
                break;
            case 8:
                displayGraph();
                break;
            case 9:
                changePassword();
                break;
            case 10:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void userMenu() {
    while (1) {
        printf("\nUser Menu\n");
        printf("1. View My Profile\n");
        printf("2. Change Password\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYour Profile:\n");
                printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nShift: %s\nEmail: %s\nContact: %s\nSalary: %.2f\nBlood Group: %s\nUsername: %s\n",
                       current_user->id, current_user->name, current_user->age, current_user->gender,
                       current_user->shift, current_user->email, current_user->contact, current_user->salary,
                       current_user->blood_group, current_user->username);
                break;
            case 2:
                changePassword();
                break;
            case 3:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void changePassword() {
    char new_password[50], confirm_password[50];
    printf("Enter new password: ");
    scanf("%s", new_password);
    printf("Confirm new password: ");
    scanf("%s", confirm_password);

    if (strcmp(new_password, confirm_password) == 0) {
        strcpy(current_user->password, new_password);
        printf("Password changed successfully!\n");
    } else {
        printf("Passwords don't match. Try again.\n");
    }
}
