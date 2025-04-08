#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Employee {
    int id;                     // Employee ID
    char name[100];            // Employee Name
    float salary;              // Employee Salary
    char gender[10];           // Employee Gender
    int age;                   // Employee Age
    char shift[10];            // Employee Shift (Day/Night)
    char email[100];           // Employee Email
    char contact_no[15];       // Employee Contact Number
    char blood_group[5];       // Employee Blood Group
    char role[50];             // Employee Role
    char username[50];         // Login username
    char password[50];         // Login password (insecure - for demo only)
    struct Employee *next;     // Linked List pointer
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

Employee *head = NULL; // Linked List Head
TreeNode *root = NULL; // Binary Tree Root
GraphNode **graph = NULL; // Graph Adjacency List
int graph_size = 0;
Employee *current_user = NULL; // Currently logged in user

// Function Prototypes
void addEmployeeToList(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role, char *username, char *password);
void addEmployeeToTree(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role, char *username, char *password);
void addEmployeeToGraph(int supervisor_id, int supervised_id);
void viewEmployee(int id);
void displayAllEmployees();
void saveToFile(const char *filename);
void loadFromFile(const char *filename);
void deleteEmployee(int id);
void deleteFile(const char *filename);
void displayGraph();
void initializeDemoData();
bool login();
void adminMenu();
void userMenu();
void changePassword();
void addNewUser();
void manageUsers();

int main() {
    // Allocate memory for graph (example with size 100)
    graph_size = 100;
    graph = (GraphNode **)malloc(graph_size * sizeof(GraphNode *));
    for (int i = 0; i < graph_size; i++) {
        graph[i] = NULL;
    }

    // Initialize with demo data
    initializeDemoData();

    // Login system
    while (1) {
        printf("\nEmployee Record Management System\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (login()) {
                    if (strcmp(current_user->role, "admin") == 0) {
                        adminMenu();
                    } else {
                        userMenu();
                    }
                    current_user = NULL; // Logout
                }
                break;
            case 2:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void initializeDemoData() {
    // Add demo admin account
    addEmployeeToList(1, "Admin User", 10000.0, "Male", 35, "Day", "admin@company.com", "1234567890", "O+", "admin", "admin", "admin123");
    addEmployeeToTree(1, "Admin User", 10000.0, "Male", 35, "Day", "admin@company.com", "1234567890", "O+", "admin", "admin", "admin123");

    // Add demo regular employees
    addEmployeeToList(2, "John Doe", 5000.0, "Male", 28, "Day", "john@company.com", "9876543210", "A+", "developer", "john", "john123");
    addEmployeeToTree(2, "John Doe", 5000.0, "Male", 28, "Day", "john@company.com", "9876543210", "A+", "developer", "john", "john123");

    addEmployeeToList(3, "Jane Smith", 6000.0, "Female", 32, "Night", "jane@company.com", "8765432109", "B+", "manager", "jane", "jane123");
    addEmployeeToTree(3, "Jane Smith", 6000.0, "Female", 32, "Night", "jane@company.com", "8765432109", "B+", "manager", "jane", "jane123");

    // Add some supervisory relationships
    addEmployeeToGraph(3, 2); // Jane supervises John
}

bool login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    Employee *current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            current_user = current;
            printf("Login successful! Welcome, %s.\n", current->name);
            return true;
        }
        current = current->next;
    }

    printf("Invalid username or password.\n");
    return false;
}

void adminMenu() {
    int choice, id, age;
    char name[100], gender[10], shift[10], email[100], contact_no[15], blood_group[5], role[50], filename[50], username[50], password[50];
    float salary;

    while (1) {
        printf("\nAdmin Menu\n");
        printf("1. Add Employee\n");
        printf("2. View Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Save Data to File\n");
        printf("5. Load Data from File\n");
        printf("6. Delete Data File\n");
        printf("7. Display All Employees\n");
        printf("8. Add Supervision Relationship\n");
        printf("9. Display Employee Supervisory Graph\n");
        printf("10. Manage Users\n");
        printf("11. Change Password\n");
        printf("12. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Employee Name: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter Employee Salary: ");
                scanf("%f", &salary);
                printf("Enter Gender: ");
                scanf("%s", gender);
                printf("Enter Age: ");
                scanf("%d", &age);
                printf("Enter Shift (Day/Night): ");
                scanf("%s", shift);
                printf("Enter Email: ");
                scanf("%s", email);
                printf("Enter Contact Number: ");
                scanf("%s", contact_no);
                printf("Enter Blood Group: ");
                scanf("%s", blood_group);
                printf("Enter Role: ");
                scanf("%s", role);
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                addEmployeeToList(id, name, salary, gender, age, shift, email, contact_no, blood_group, role, username, password);
                addEmployeeToTree(id, name, salary, gender, age, shift, email, contact_no, blood_group, role, username, password);
                break;

            case 2:
                printf("Enter Employee ID to view: ");
                scanf("%d", &id);
                viewEmployee(id);
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
                {
                    int supervisor_id, supervised_id;
                    printf("Enter Supervisor ID: ");
                    scanf("%d", &supervisor_id);
                    printf("Enter Supervised Employee ID: ");
                    scanf("%d", &supervised_id);
                    addEmployeeToGraph(supervisor_id, supervised_id);
                }
                break;

            case 9:
                displayGraph();
                break;

            case 10:
                manageUsers();
                break;

            case 11:
                changePassword();
                break;

            case 12:
                printf("Logging out...\n");
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void userMenu() {
    int choice;

    while (1) {
        printf("\nUser Menu (Logged in as %s)\n", current_user->name);
        printf("1. View My Record\n");
        printf("2. Change Password\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewEmployee(current_user->id);
                break;

            case 2:
                changePassword();
                break;

            case 3:
                printf("Logging out...\n");
                return;

            default:
                printf("Invalid choice! Please try again.\n");
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

        // Also update the password in the tree
        TreeNode *stack[100];
        int top = -1;
        TreeNode *current = root;

        while (current != NULL || top != -1) {
            while (current != NULL) {
                stack[++top] = current;
                current = current->left;
            }
            current = stack[top--];
            if (current->emp->id == current_user->id) {
                strcpy(current->emp->password, new_password);
                break;
            }
            current = current->right;
        }
    } else {
        printf("Passwords do not match!\n");
    }
}

void manageUsers() {
    int choice;

    while (1) {
        printf("\nUser Management\n");
        printf("1. Add New User\n");
        printf("2. View All Users\n");
        printf("3. Back to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewUser();
                break;

            case 2:
                printf("\nAll Users:\n");
                printf("ID\tUsername\tRole\tName\n");
                printf("----------------------------------------\n");
                Employee *current = head;
                while (current != NULL) {
                    printf("%d\t%s\t\t%s\t%s\n", current->id, current->username, current->role, current->name);
                    current = current->next;
                }
                break;

            case 3:
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void addNewUser() {
    int id, age;
    char name[100], gender[10], shift[10], email[100], contact_no[15], blood_group[5], role[50], username[50], password[50];
    float salary;

    printf("Enter Employee ID: ");
    scanf("%d", &id);
    printf("Enter Employee Name: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter Employee Salary: ");
    scanf("%f", &salary);
    printf("Enter Gender: ");
    scanf("%s", gender);
    printf("Enter Age: ");
    scanf("%d", &age);
    printf("Enter Shift (Day/Night): ");
    scanf("%s", shift);
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Contact Number: ");
    scanf("%s", contact_no);
    printf("Enter Blood Group: ");
    scanf("%s", blood_group);
    printf("Enter Role (admin/regular): ");
    scanf("%s", role);
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    addEmployeeToList(id, name, salary, gender, age, shift, email, contact_no, blood_group, role, username, password);
    addEmployeeToTree(id, name, salary, gender, age, shift, email, contact_no, blood_group, role, username, password);

    printf("User added successfully!\n");
}

void addEmployeeToList(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role, char *username, char *password) {
    // Check if employee ID already exists
    Employee *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Employee ID already exists!\n");
            return;
        }
        temp = temp->next;
    }

    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));
    newEmployee->id = id;
    strcpy(newEmployee->name, name);
    newEmployee->salary = salary;
    strcpy(newEmployee->gender, gender);
    newEmployee->age = age;
    strcpy(newEmployee->shift, shift);
    strcpy(newEmployee->email, email);
    strcpy(newEmployee->contact_no, contact_no);
    strcpy(newEmployee->blood_group, blood_group);
    strcpy(newEmployee->role, role);
    strcpy(newEmployee->username, username);
    strcpy(newEmployee->password, password);
    newEmployee->next = head;
    head = newEmployee;
    printf("Employee added to list successfully!\n");
}

void addEmployeeToTree(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role, char *username, char *password) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->emp = (Employee *)malloc(sizeof(Employee));
    newNode->emp->id = id;
    strcpy(newNode->emp->name, name);
    newNode->emp->salary = salary;
    strcpy(newNode->emp->gender, gender);
    newNode->emp->age = age;
    strcpy(newNode->emp->shift, shift);
    strcpy(newNode->emp->email, email);
    strcpy(newNode->emp->contact_no, contact_no);
    strcpy(newNode->emp->blood_group, blood_group);
    strcpy(newNode->emp->role, role);
    strcpy(newNode->emp->username, username);
    strcpy(newNode->emp->password, password);
    newNode->left = newNode->right = NULL;

    if (root == NULL) {
        root = newNode;
    } else {
        TreeNode *current = root, *parent = NULL;
        while (current != NULL) {
            parent = current;
            if (id < current->emp->id) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (id < parent->emp->id) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
    printf("Employee added to tree successfully!\n");
}

void addEmployeeToGraph(int supervisor_id, int supervised_id) {
    // Check if both employees exist
    bool supervisor_found = false, supervised_found = false;
    Employee *current = head;
    while (current != NULL) {
        if (current->id == supervisor_id) supervisor_found = true;
        if (current->id == supervised_id) supervised_found = true;
        if (supervisor_found && supervised_found) break;
        current = current->next;
    }

    if (!supervisor_found || !supervised_found) {
        printf("One or both employee IDs not found!\n");
        return;
    }

    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    newNode->emp_id = supervised_id;
    newNode->next = NULL;

    int index = supervisor_id % graph_size;
    GraphNode *current_node = graph[index];
    if (current_node == NULL) {
        graph[index] = newNode;
    } else {
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = newNode;
    }

    printf("Supervisory relationship added.\n");
}

void viewEmployee(int id) {
    // Check if current user is admin or viewing their own record
    if (strcmp(current_user->role, "admin") != 0 && current_user->id != id) {
        printf("Access denied! You can only view your own record.\n");
        return;
    }

    Employee *current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("\nEmployee Details:\n");
            printf("ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Salary: %.2f\n", current->salary);
            printf("Gender: %s\n", current->gender);
            printf("Age: %d\n", current->age);
            printf("Shift: %s\n", current->shift);
            printf("Email: %s\n", current->email);
            printf("Contact Number: %s\n", current->contact_no);
            printf("Blood Group: %s\n", current->blood_group);
            printf("Role: %s\n", current->role);
            return;
        }
        current = current->next;
    }
    printf("Employee not found.\n");
}

void displayAllEmployees() {
    // Only admin can view all employees
    if (strcmp(current_user->role, "admin") != 0) {
        printf("Access denied! Only admin can view all employees.\n");
        return;
    }

    Employee *current = head;
    if (current == NULL) {
        printf("No employees to display.\n");
        return;
    }

    printf("\nAll Employees:\n");
    printf("ID\tName\t\tSalary\tGender\tAge\tShift\tEmail\t\tContact No\t\tBlood Group\tRole\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    while (current != NULL) {
        printf("%d\t%s\t\t%.2f\t%s\t%d\t%s\t%s\t\t%s\t\t%s\t%s\n",
               current->id, current->name, current->salary, current->gender, current->age, current->shift, current->email, current->contact_no, current->blood_group, current->role);
        current = current->next;
    }
}

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    Employee *current = head;
    int serial_number = 1;
    int demo_data_ids[] = {1, 2, 3}; // IDs of demo data
    int demo_data_count = sizeof(demo_data_ids)/sizeof(demo_data_ids[0]);

    fprintf(file, "Employee Records:\n");
    fprintf(file, "=================\n\n");

    while (current != NULL) {
        // Check if current ID is in demo data
        int is_demo_data = 0;
        for (int i = 0; i < demo_data_count; i++) {
            if (current->id == demo_data_ids[i]) {
                is_demo_data = 1;
                break;
            }
        }

        // Only count non-demo data in serial numbers
        if (!is_demo_data) {
            fprintf(file, "%d. ", serial_number++);
        } else {
            fprintf(file, "Demo. ");
        }

        fprintf(file, "ID: %d, Name: %s, Salary: %.2f, Gender: %s, Age: %d, Shift: %s, Email: %s, Contact No: %s, Blood Group: %s, Role: %s\n",
                current->id, current->name, current->salary, current->gender, current->age,
                current->shift, current->email, current->contact_no, current->blood_group, current->role);

        current = current->next;
    }

    fclose(file);
    printf("Data saved to %s successfully.\n", filename);
}
void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Clear existing data
    while (head != NULL) {
        Employee *temp = head;
        head = head->next;
        free(temp);
    }
    root = NULL; // Reset the tree

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        int id, age;
        char name[100], gender[10], shift[10], email[100], contact_no[15], blood_group[5], role[50], username[50], password[50];
        float salary;

        if (sscanf(line, "%d,%99[^,],%f,%9[^,],%d,%9[^,],%99[^,],%14[^,],%4[^,],%49[^,],%49[^,],%49[^,\n]",
                   &id, name, &salary, gender, &age, shift, email, contact_no, blood_group, role, username, password) == 12) {
            addEmployeeToList(id, name, salary, gender, age, shift, email, contact_no, blood_group, role, username, password);
            addEmployeeToTree(id, name, salary, gender, age, shift, email, contact_no, blood_group, role, username, password);
        }
    }

    fclose(file);
    printf("Data loaded from %s successfully.\n", filename);
}

void deleteEmployee(int id) {
    // Only admin can delete employees
    if (strcmp(current_user->role, "admin") != 0) {
        printf("Access denied! Only admin can delete employees.\n");
        return;
    }

    Employee *current = head;
    Employee *prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            // Also delete from the tree
            TreeNode *parent = NULL, *current_tree = root;
            while (current_tree != NULL && current_tree->emp->id != id) {
                parent = current_tree;
                if (id < current_tree->emp->id) {
                    current_tree = current_tree->left;
                } else {
                    current_tree = current_tree->right;
                }
            }

            if (current_tree != NULL) {
                // Node with only one child or no child
                if (current_tree->left == NULL) {
                    if (parent == NULL) {
                        root = current_tree->right;
                    } else if (parent->left == current_tree) {
                        parent->left = current_tree->right;
                    } else {
                        parent->right = current_tree->right;
                    }
                    free(current_tree->emp);
                    free(current_tree);
                } else if (current_tree->right == NULL) {
                    if (parent == NULL) {
                        root = current_tree->left;
                    } else if (parent->left == current_tree) {
                        parent->left = current_tree->left;
                    } else {
                        parent->right = current_tree->left;
                    }
                    free(current_tree->emp);
                    free(current_tree);
                } else {
                    // Node with two children: Get the inorder successor
                    TreeNode *successor_parent = current_tree;
                    TreeNode *successor = current_tree->right;

                    while (successor->left != NULL) {
                        successor_parent = successor;
                        successor = successor->left;
                    }

                    // Copy the successor's data to current node
                    free(current_tree->emp);
                    current_tree->emp = successor->emp;

                    // Delete the successor
                    if (successor_parent->left == successor) {
                        successor_parent->left = successor->right;
                    } else {
                        successor_parent->right = successor->right;
                    }
                    free(successor);
                }
            }

            free(current);
            printf("Employee deleted successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Employee not found.\n");
}

void deleteFile(const char *filename) {
    // Only admin can delete files
    if (strcmp(current_user->role, "admin") != 0) {
        printf("Access denied! Only admin can delete files.\n");
        return;
    }

    if (remove(filename) != 0) {
        printf("Error deleting file %s\n", filename);
    } else {
        printf("File %s deleted successfully.\n", filename);
    }
}

void displayGraph() {
    // Only admin can view the graph
    if (strcmp(current_user->role, "admin") != 0) {
        printf("Access denied! Only admin can view the supervisory graph.\n");
        return;
    }

    printf("\nEmployee Supervisory Graph:\n");
    for (int i = 0; i < graph_size; i++) {
        if (graph[i] != NULL) {
            // Find supervisor name
            char supervisor_name[100] = "Unknown";
            Employee *current = head;
            while (current != NULL) {
                if (current->id == i) {
                    strcpy(supervisor_name, current->name);
                    break;
                }
                current = current->next;
            }

            printf("%s (ID: %d) supervises: ", supervisor_name, i);
            GraphNode *current_node = graph[i];
            while (current_node != NULL) {
                // Find supervised employee name
                char supervised_name[100] = "Unknown";
                current = head;
                while (current != NULL) {
                    if (current->id == current_node->emp_id) {
                        strcpy(supervised_name, current->name);
                        break;
                    }
                    current = current->next;
                }
                printf("%s (ID: %d), ", supervised_name, current_node->emp_id);
                current_node = current_node->next;
            }
            printf("\n");
        }
    }
}
