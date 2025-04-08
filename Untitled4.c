
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int id;
    char name[100];
    float salary;
    char role[50];
    struct Employee *next; // Linked List pointer
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
void addEmployeeToList(int id, char *name, float salary, char *role);
void addEmployeeToTree(int id, char *name, float salary, char *role);
void addEmployeeToGraph(int supervisor_id, int supervised_id);
void viewEmployee(int id);
void displayAllEmployees();
void saveToFile(const char *filename);
void loadFromFile(const char *filename);
void deleteEmployee(int id);
void deleteFile(const char *filename);
void displayGraph();

int main() {
    int choice, id;
    char name[100], role[50], filename[50];
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
                printf("Enter Role (admin/user): ");
                scanf("%s", role);
                addEmployeeToList(id, name, salary, role);
                addEmployeeToTree(id, name, salary, role);
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

void addEmployeeToList(int id, char *name, float salary, char *role) {
    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));
    newEmployee->id = id;
    strcpy(newEmployee->name, name);
    newEmployee->salary = salary;
    strcpy(newEmployee->role, role);
    newEmployee->next = head;
    head = newEmployee;
    printf("Employee added to list successfully!\n");
}

void addEmployeeToTree(int id, char *name, float salary, char *role) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->emp = (Employee *)malloc(sizeof(Employee));
    newNode->emp->id = id;
    strcpy(newNode->emp->name, name);
    newNode->emp->salary = salary;
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
    printf("ID\tName\t\tSalary\tRole\n");
    printf("----------------------------------------\n");
    while (current != NULL) {
        printf("%d\t%s\t%.2f\t%s\n",
               current->id, current->name, current->salary, current->role);
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
    while (current != NULL) {
        fprintf(file, "%d,%s,%.2f,%s\n",
                current->id, current->name, current->salary, current->role);
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

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int id;
        char name[100], role[50];
        float salary;

        if (sscanf(line, "%d,%99[^,],%f,%49s", &id, name, &salary, role) == 4) {
            addEmployeeToList(id, name, salary, role);
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
