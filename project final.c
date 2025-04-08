#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Function Prototypes
void addEmployeeToList(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role);
void addEmployeeToTree(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role);
void addEmployeeToGraph(int supervisor_id, int supervised_id);
void viewEmployee(int id);
void displayAllEmployees();
void saveToFile(const char *filename);
void loadFromFile(const char *filename);
void deleteEmployee(int id);
void deleteFile(const char *filename);
void displayGraph();

int main() {
    int choice, id, age;
    char name[100], gender[10], shift[10], email[100], contact_no[15], blood_group[5], role[50], filename[50];
    float salary;

    // Allocate memory for graph (example with size 100, you can expand this dynamically)
    graph_size = 100;
    graph = (GraphNode **)malloc(graph_size * sizeof(GraphNode *));
    for (int i = 0; i < graph_size; i++) {
        graph[i] = NULL;
    }

    while (1) {
        printf("\nEmployee Record Management System\n");
        printf("1. Add Employee (Linked List)\n");
        printf("2. View Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Save Data to File\n");
        printf("5. Load Data from File\n");
        printf("6. Delete Data File\n");
        printf("7. Display All Employees\n");
        printf("8. Add Supervision Relationship (Graph)\n");
        printf("9. Display Employee Supervisory Graph\n");
        printf("10. Exit\n");
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
                addEmployeeToList(id, name, salary, gender, age, shift, email, contact_no, blood_group, role);
                addEmployeeToTree(id, name, salary, gender, age, shift, email, contact_no, blood_group, role);
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
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addEmployeeToList(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role) {
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
    newEmployee->next = head;
    head = newEmployee;
    printf("Employee added to list successfully!\n");
}

void addEmployeeToTree(int id, char *name, float salary, char *gender, int age, char *shift, char *email, char *contact_no, char *blood_group, char *role) {
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
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    newNode->emp_id = supervised_id;
    newNode->next = NULL;

    int index = supervisor_id % graph_size;  // Simple hashing for demonstration
    GraphNode *current = graph[index];
    if (current == NULL) {
        graph[index] = newNode;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("Supervisory relationship added.\n");
}

void viewEmployee(int id) {
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
    int serial_number = 1; // Initialize serial number

    while (current != NULL) {
        fprintf(file, "%d. ID: %d, Name: %s, Salary: %.2f, Gender: %s, Age: %d, Shift: %s, Email: %s, Contact No: %s, Blood Group: %s, Role: %s\n",
                serial_number, current->id, current->name, current->salary, current->gender, current->age, current->shift, current->email, current->contact_no, current->blood_group, current->role);
        current = current->next;
        serial_number++; // Increment serial number
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

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        int id, age;
        char name[100], gender[10], shift[10], email[100], contact_no[15], blood_group[5], role[50];
        float salary;

        if (sscanf(line, "%*d. ID: %d, Name: %99[^,], Salary: %f, Gender: %9[^,], Age: %d, Shift: %9[^,], Email: %99[^,], Contact No: %14[^,], Blood Group: %4[^,], Role: %49s",
                   &id, name, &salary, gender, &age, shift, email, contact_no, blood_group, role) == 10) {
            addEmployeeToList(id, name, salary, gender, age, shift, email, contact_no, blood_group, role);
        }
    }

    fclose(file);
    printf("Data loaded from %s successfully.\n", filename);
}

void deleteEmployee(int id) {
    Employee *current = head;
    Employee *prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
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
    if (remove(filename) != 0) {
        printf("Error deleting file %s\n", filename);
    } else {
        printf("File %s deleted successfully.\n", filename);
    }
}

void displayGraph() {
    printf("\nEmployee Supervisory Graph:\n");
    for (int i = 0; i < graph_size; i++) {
        if (graph[i] != NULL) {
            printf("Supervisor ID %d supervises: ", i);
            GraphNode *current = graph[i];
            while (current != NULL) {
                printf("%d ", current->emp_id);
                current = current->next;
            }
            printf("\n");
        }
    }
}
