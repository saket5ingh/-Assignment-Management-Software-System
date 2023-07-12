#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX 500

typedef struct student
{
    int student_id;
    char name[MAX];
    char group_partner[MAX];
    int group_id;
    int assignment_id;
    char deadline[MAX];
    char status[MAX];
    float offline_evaluation_marks;
    float viva_marks;
    struct student *left;
    struct student *right;
    int height;
    int bf;
} student;

typedef struct assignment
{
    int assignment_id;
    char topic_name[MAX];
    char status[MAX];
    struct student_group *student_group_list;
    struct assignment *left;
    struct assignment *right;
    int height;
    int bf;
} assignment;

typedef struct student_group
{
    int group_id;
    char status[MAX];
    float marks;
    struct student *student1;
    struct student *student2;
    struct student_group *left;
    struct student_group *right;
    int height;
    int bf;
    struct student_group *parent;
} student_group;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height_student(student *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int balance_factor_student(student *node)
{
    if (node == NULL)
        return 0;
    return height_student(node->left) - height_student(node->right);
}

student *rotate_left_student(student *node)
{
    student *x = node->right;
    student *T2 = x->left;

    x->left = node;
    node->right = T2;

    node->height = 1 + max(height_student(node->left), height_student(node->right));
    x->height = 1 + max(height_student(x->left), height_student(x->right));

    return x;
}

student *rotate_right_student(student *node)
{
    student *y = node->left;
    student *T2 = y->right;

    y->right = node;
    node->left = T2;

    node->height = 1 + max(height_student(node->left), height_student(node->right));
    y->height = 1 + max(height_student(y->left), height_student(y->right));

    return y;
}
int height_assignment(assignment *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}
int balance_factor_assignment(assignment *node)
{
    if (node == NULL)
        return 0;
    return height_assignment(node->left) - height_assignment(node->right);
}
assignment *rotate_left_assignmet(assignment *node)
{
    assignment *new_root = node->right;
    assignment *temp = new_root->left;

    new_root->left = node;
    node->right = temp;

    node->height = 1 + max(height_assignment(node->left), height_assignment(node->right));
    new_root->height = 1 + max(height_assignment(new_root->left), height_assignment(new_root->right));

    return new_root;
}
assignment *rotate_right_assignmet(assignment *node)
{
    assignment *new_root = node->left;
    assignment *temp = new_root->right;

    new_root->right = node;
    node->left = temp;

    node->height = 1 + max(height_assignment(node->left), height_assignment(node->right));
    new_root->height = 1 + max(height_assignment(new_root->left), height_assignment(new_root->right));

    return new_root;
}

int height_student_group(student_group *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int balance_factor_student_group(student_group *node)
{
    if (node == NULL)
        return 0;
    return height_student_group(node->left) - height_student_group(node->right);
}

student_group *rotate_left_student_group(student_group *node)
{
    student_group *x = node->right;
    student_group *T2 = x->left;

    x->left = node;
    node->right = T2;

    node->height = 1 + max(height_student_group(node->left), height_student_group(node->right));
    x->height = 1 + max(height_student_group(x->left), height_student_group(x->right));

    return x;
}

student_group *rotate_right_student_group(student_group *node)
{
    student_group *y = node->left;
    student_group *T2 = y->right;

    y->right = node;
    node->left = T2;

    node->height = 1 + max(height_student_group(node->left), height_student_group(node->right));
    y->height = 1 + max(height_student_group(y->left), height_student_group(y->right));

    return y;
}

student *insert_student_node(student *root, student *new_node)
{
    if (root == NULL)
        return new_node;

    if (new_node->student_id < root->student_id)
    {
        root->left = insert_student_node(root->left, new_node);
    }
    else if (new_node->student_id > root->student_id)
    {
        root->right = insert_student_node(root->right, new_node);
    }
    else
    {
        printf("Error: Student with ID %d already exists\n", new_node->student_id);
        return root;
    }

    root->height = 1 + max(height_student(root->left), height_student(root->right));
    root->bf = balance_factor_student(root);

    if (root->bf > 1)
    {
        if (new_node->student_id < root->left->student_id)
            return rotate_right_student(root);
        else
        {
            root->left = rotate_left_student(root->left);
            return rotate_right_student(root);
        }
    }
    else if (root->bf < -1)
    {
        if (new_node->student_id > root->right->student_id)
            return rotate_left_student(root);
        else
        {
            root->right = rotate_right_student(root->right);
            return rotate_left_student(root);
        }
    }

    return root;
}

assignment *insert_assignment_node(assignment *root, assignment *new_node)
{
    if (root == NULL)
        return new_node;

    if (new_node->assignment_id < root->assignment_id)
    {
        root->left = insert_assignment_node(root->left, new_node);
    }
    else if (new_node->assignment_id > root->assignment_id)
    {
        root->right = insert_assignment_node(root->right, new_node);
    }
    else
    {
        return root;
    }

    root->height = 1 + max(height_assignment(root->left), height_assignment(root->right));
    root->bf = balance_factor_assignment(root);

    if (root->bf > 1)
    {
        if (new_node->assignment_id < root->left->assignment_id)
            return rotate_right_assignmet(root);
        else
        {
            root->left = rotate_left_assignmet(root->left);
            return rotate_right_assignmet(root);
        }
    }
    else if (root->bf < -1)
    {
        if (new_node->assignment_id > root->right->assignment_id)
            return rotate_left_assignmet(root);
        else
        {
            root->right = rotate_right_assignmet(root->right);
            return rotate_left_assignmet(root);
        }
    }

    return root;
}

student_group *insert_student_group_node(student_group *root, student_group *new_node)
{
    if (root == NULL)
    {
        return new_node;
    }

    if (new_node->group_id < root->group_id)
    {
        root->left = insert_student_group_node(root->left, new_node);
    }
    else if (new_node->group_id > root->group_id)
    {
        root->right = insert_student_group_node(root->right, new_node);
    }
    else
    {
        return root;
    }

    root->height = 1 + max(height_student_group(root->left), height_student_group(root->right));
    root->bf = balance_factor_student_group(root);

    if (root->bf > 1)
    {
        if (balance_factor_student_group(root->left) < 0)
        {
            root->left = rotate_left_student_group(root->left);
        }
        return rotate_right_student_group(root);
    }

    if (root->bf < -1)
    {
        if (balance_factor_student_group(root->right) > 0)
        {
            root->right = rotate_right_student_group(root->right);
        }
        return rotate_left_student_group(root);
    }

    return root;
}

void insert_student_record(student **student_tree_ptr, assignment **assignment_tree_ptr, int student_id, char *name, char *group_partner, int group_id, int assignment_id, char *deadline, char *status, float offline_evaluation_marks, float viva_marks, char *topic_name)
{
    student *new_student = malloc(sizeof(student));
    new_student->student_id = student_id;
    strcpy(new_student->name, name);
    strcpy(new_student->group_partner, group_partner);
    new_student->group_id = group_id;
    new_student->assignment_id = assignment_id;
    strcpy(new_student->deadline, deadline);
    strcpy(new_student->status, status);
    new_student->offline_evaluation_marks = offline_evaluation_marks;
    new_student->viva_marks = viva_marks;
    new_student->left = NULL;
    new_student->right = NULL;
    new_student->height = 1;
    new_student->bf = 0;

    *student_tree_ptr = insert_student_node(*student_tree_ptr, new_student);

    assignment *assignment_ptr = *assignment_tree_ptr;
    while (assignment_ptr != NULL && assignment_ptr->assignment_id != assignment_id)
    {
        if (assignment_id < assignment_ptr->assignment_id)
            assignment_ptr = assignment_ptr->left;
        else
            assignment_ptr = assignment_ptr->right;
    }

    if (assignment_id == 0)
    {
        return;
    }
    if (assignment_ptr == NULL)
    {
        assignment *new_assignment = malloc(sizeof(assignment));
        new_assignment->assignment_id = assignment_id;
        strcpy(new_assignment->topic_name, topic_name);
        strcpy(new_assignment->status, "declared");
        new_assignment->student_group_list = NULL;
        new_assignment->left = NULL;
        new_assignment->right = NULL;
        new_assignment->height = 1;
        new_assignment->bf = 0;

        *assignment_tree_ptr = insert_assignment_node(*assignment_tree_ptr, new_assignment);
        assignment_ptr = new_assignment;
    }

    student_group *group_ptr = assignment_ptr->student_group_list;
    student_group *parent_group_ptr = NULL;

    while (group_ptr != NULL && group_ptr->group_id != group_id)
    {
        parent_group_ptr = group_ptr;
        if (group_id < group_ptr->group_id)
            group_ptr = group_ptr->left;
        else
            group_ptr = group_ptr->right;
    }

    if (group_ptr == NULL)
    {
        student_group *new_group = malloc(sizeof(student_group));
        new_group->group_id = group_id;
        strcpy(new_group->status, "assigned");
        new_group->marks = offline_evaluation_marks + viva_marks;
        new_group->student1 = new_student;
        new_group->student2 = NULL;
        new_group->left = NULL;
        new_group->right = NULL;
        new_group->height = 1;
        new_group->bf = 0;

        assignment_ptr->student_group_list = insert_student_group_node(assignment_ptr->student_group_list, new_group);
    }
    else
    {
        if (group_ptr->student1 == NULL)
        {
            group_ptr->student1 = new_student;
        }
        else if (group_ptr->student2 == NULL && strcmp(group_ptr->student1->name, name) != 0)
        {
            group_ptr->student2 = new_student;
        }

        group_ptr->marks = group_ptr->student1->offline_evaluation_marks + group_ptr->student1->viva_marks;
        if (group_ptr->student2 != NULL)
        {
            group_ptr->marks += group_ptr->student2->offline_evaluation_marks + group_ptr->student2->viva_marks;
        }
    }
}

void inorder_display_student(student *student_node)
{
    if (student_node != NULL)
    {
        inorder_display_student(student_node->left);
        printf("%d\t\t%s\t%s\t%d\t\t%d\t\t%s\t%s\t%.2f\t\t\t%.2f\n",
               student_node->student_id,
               student_node->name,
               student_node->group_partner,
               student_node->group_id,
               student_node->assignment_id,
               student_node->deadline,
               student_node->status,
               student_node->offline_evaluation_marks,
               student_node->viva_marks);
        inorder_display_student(student_node->right);
    }
}

void display_student(student *student_tree_ptr)
{
    if (student_tree_ptr == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("Student ID\tName\tGroup Partner\tGroup ID\tAssignment ID\tDeadline\tStatus\tOffline Eval. Marks\tViva Marks\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

    inorder_display_student(student_tree_ptr);
}
void inorder_display_assignment(assignment *assignment_node)
{
    if (assignment_node != NULL)
    {
        inorder_display_assignment(assignment_node->left);
        printf("%d\t\t%s\t\t%s\n",
               assignment_node->assignment_id,
               assignment_node->topic_name,
               assignment_node->status);
        inorder_display_assignment(assignment_node->right);
    }
}
void display_assignment(assignment *assignment_tree_ptr)
{
    if (assignment_tree_ptr == NULL)
    {
        printf("No assignment records found.\n");
        return;
    }

    printf("Assignment ID\tTopic Name\tStatus\n");
    printf("--------------------------------------------\n");

    inorder_display_assignment(assignment_tree_ptr);
}

void display_student_groups(student_group *student_group_node)
{
    if (student_group_node != NULL)
    {
        display_student_groups(student_group_node->left);
        printf("%d\n ", student_group_node->group_id);
        printf("%f\n", student_group_node->marks);
        display_student_groups(student_group_node->right);
    }
}

void display_assignment_groups_helper(assignment *assignment_ptr)
{
    if (assignment_ptr != NULL)
    {
        display_assignment_groups_helper(assignment_ptr->left);
        printf("Assignment ID: %d\n", assignment_ptr->assignment_id);
        printf("Student Groups: ");
        display_student_groups(assignment_ptr->student_group_list);
        printf("\n");
        display_assignment_groups_helper(assignment_ptr->right);
    }
}

void display_assignment_groups(assignment *assignment_tree_ptr)
{
    if (assignment_tree_ptr == NULL)
    {
        printf("No assignments found.\n");
        return;
    }

    printf("Assignment Groups:\n");
    display_assignment_groups_helper(assignment_tree_ptr);
}
assignment *search_assignment(assignment *root, int assignment_id)
{
    if (root == NULL || root->assignment_id == assignment_id)
    {
        return root;
    }
    if (assignment_id < root->assignment_id)
    {
        return search_assignment(root->left, assignment_id);
    }
    else
    {
        return search_assignment(root->right, assignment_id);
    }
}

student_group *search_student_group(student_group *root, int group_id)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->group_id == group_id)
    {
        return root;
    }
    else if (group_id < root->group_id)
    {
        return search_student_group(root->left, group_id);
    }
    else
    {
        return search_student_group(root->right, group_id);
    }
}
student *search_student(student *root, int student_id)
{
    if (root == NULL || root->student_id == student_id)
    {
        return root;
    }
    if (student_id < root->student_id)
    {
        return search_student(root->left, student_id);
    }
    return search_student(root->right, student_id);
}
void insert_assignment(assignment **assignment_tree_ptr, student **student_tree_ptr, int assignment_id, const char *topic_name, const char *deadline, const char *filename)
{
    assignment *assignment_node = search_assignment(*assignment_tree_ptr, assignment_id);
    if (assignment_node != NULL)
    {
        printf("Error: Assignment already exists!\n");
        return;
    }

    assignment *new_assignment = (assignment *)malloc(sizeof(assignment));
    new_assignment->assignment_id = assignment_id;
    strcpy(new_assignment->topic_name, topic_name);
    strcpy(new_assignment->status, "declared");
    new_assignment->student_group_list = NULL;
    new_assignment->left = NULL;
    new_assignment->right = NULL;
    new_assignment->height = 1;
    new_assignment->bf = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return;
    }

    char line[256];
    int first_student = 1;
    while (fgets(line, sizeof(line), file))
    {
        int student_id;
        char name[MAX];
        char group_partner[MAX];
        int group_id;

        sscanf(line, "%d, %[^,], %[^,], %d", &student_id, name, group_partner, &group_id);
        student *new_student = (student *)malloc(sizeof(student));
        new_student->student_id = student_id;
        strcpy(new_student->name, name);
        strcpy(new_student->group_partner, group_partner);
        new_student->group_id = group_id;
        new_student->assignment_id = assignment_id;
        strcpy(new_student->deadline, deadline);
        strcpy(new_student->status, "not submitted");
        new_student->offline_evaluation_marks = 0.0;
        new_student->viva_marks = 0.0;
        new_student->left = NULL;
        new_student->right = NULL;
        new_student->height = 1;
        new_student->bf = 0;
        *student_tree_ptr = insert_student_node(*student_tree_ptr, new_student);
        student_group *existing_student_group = search_student_group(new_assignment->student_group_list, group_id);
        if (existing_student_group == NULL)
        {
            student_group *new_student_group = (student_group *)malloc(sizeof(student_group));
            new_student_group->group_id = group_id;
            strcpy(new_student_group->status, "not submitted");
            new_student_group->marks = 0.0;
            new_student_group->student1 = new_student;
            new_student_group->student2 = NULL;
            new_student_group->left = NULL;
            new_student_group->right = NULL;
            new_student_group->height = 1;
            new_student_group->bf = 0;
            new_student_group->parent = NULL;
            new_assignment->student_group_list = insert_student_group_node(new_assignment->student_group_list, new_student_group);
        }
        else
        {
            if (first_student)
            {
                new_assignment->student_group_list = existing_student_group;
                first_student = 0;
            }
            if (existing_student_group->student1 == NULL)
            {
                existing_student_group->student1 = new_student;
            }
            else
            {
                existing_student_group->student2 = new_student;
            }
        }
    }

    fclose(file);

    *assignment_tree_ptr = insert_assignment_node(*assignment_tree_ptr, new_assignment);
}

void update_status_and_marks(student *student_tree_ptr, assignment *assignment_tree_ptr, int group_id, int assignment_id, float s1_offline_marks, float s1_viva_marks, float s2_offline_marks, float s2_viva_marks, char *new_status)
{
    assignment *assignment_ptr = search_assignment(assignment_tree_ptr, assignment_id);
    student_group *group_ptr = search_student_group(assignment_ptr->student_group_list, group_id);

    strcpy(group_ptr->status, new_status);
    strcpy(group_ptr->student1->status, new_status);
    strcpy(group_ptr->student2->status, new_status);

    if (strcmp(new_status, "evaluated") == 0)
    {
        group_ptr->marks = s1_offline_marks + s1_viva_marks + s2_offline_marks + s2_viva_marks;
        group_ptr->student1->offline_evaluation_marks = s1_offline_marks;
        group_ptr->student1->viva_marks = s1_viva_marks;
        group_ptr->student2->offline_evaluation_marks = s2_offline_marks;
        group_ptr->student2->viva_marks = s2_viva_marks;
    }

    bool all_evaluated = true;
    student_group *temp_group_ptr = assignment_ptr->student_group_list;

    while (temp_group_ptr != NULL)
    {
        if (strcmp(temp_group_ptr->status, "evaluated") != 0)
        {
            all_evaluated = false;
            break;
        }

        if (group_id < temp_group_ptr->group_id)
        {
            temp_group_ptr = temp_group_ptr->left;
        }
        else
        {
            temp_group_ptr = temp_group_ptr->right;
        }
    }

    if (all_evaluated)
    {
        strcpy(assignment_ptr->status, "evaluated");
    }
}
void print_unevaluated_assignments(assignment *root)
{
    if (root == NULL)
    {
        return;
    }

    print_unevaluated_assignments(root->left);

    if (strcmp(root->status, "declared") == 0)
    {
        printf("Assignment ID: %d\n", root->assignment_id);
        printf("Topic Name: %s\n", root->topic_name);
        printf("Status: %s\n", root->status);
        printf("Student Group List: ");
        if (root->student_group_list == NULL)
        {
            printf("None\n");
        }
        else
        {
            student_group *sg = root->student_group_list;
            while (sg != NULL)
            {
                printf("%d ", sg->group_id);
                sg = sg->right;
            }
            printf("\n");
        }
        printf("\n");
    }

    print_unevaluated_assignments(root->right);
}

int is_deadline_over(char *deadline)
{
    int deadline_day, deadline_month, deadline_year;
    sscanf(deadline, "%d-%d-%d", &deadline_day, &deadline_month, &deadline_year);

    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);
    int current_day = current_time->tm_mday;
    int current_month = current_time->tm_mon + 1;
    int current_year = current_time->tm_year + 1900;

    if (deadline_year < current_year)
    {
        return 1;
    }
    else if (deadline_year == current_year && deadline_month < current_month)
    {
        return 1;
    }
    else if (deadline_year == current_year && deadline_month == current_month && deadline_day < current_day)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void print_student_groups(struct student_group *group_root)
{
    if (group_root == NULL)
    {
        return;
    }

    print_student_groups(group_root->left);
    if (strcmp(group_root->status, "not submitted") == 0)
    {
        printf("\tGroup ID: %d, Status: %s\n", group_root->group_id, group_root->status);
        printf("\tStudent 1: ID: %d, Name: %s\n", group_root->student1->student_id, group_root->student1->name);
        printf("\tStudent 2: ID: %d, Name: %s\n", group_root->student2->student_id, group_root->student2->name);
    }

    print_student_groups(group_root->right);
}

void print_late_submissions(struct assignment *assignment_root)
{
    if (assignment_root == NULL)
    {
        return;
    }

    print_late_submissions(assignment_root->left);

    if (is_deadline_over(assignment_root->student_group_list->student1->deadline))
    {
        printf("Assignment ID: %d, Topic: %s, Deadline: %s\n",
               assignment_root->assignment_id,
               assignment_root->topic_name,
               assignment_root->student_group_list->student1->deadline);
        print_student_groups(assignment_root->student_group_list);
    }

    print_late_submissions(assignment_root->right);
}

int compareStudentGroups(const void *a, const void *b)
{
    float marksA = (*((student_group **)a))->marks;
    float marksB = (*((student_group **)b))->marks;
    if (marksA < marksB)
        return 1;
    else if (marksA > marksB)
        return -1;
    else
        return 0;
}

void printStudentGroupsForAssignmentID(assignment *root, int assignmentID)
{
    if (root == NULL)
        return;

    while (root != NULL && root->assignment_id != assignmentID)
    {
        if (assignmentID < root->assignment_id)
            root = root->left;
        else
            root = root->right;
    }

    if (root == NULL)
    {
        printf("Assignment with ID %d not found.\n", assignmentID);
        return;
    }

    if (root->student_group_list == NULL)
    {
        printf("No student groups found for Assignment ID %d.\n", assignmentID);
        return;
    }

    int numStudentGroups = 0;
    student_group *curr = root->student_group_list;
    while (curr != NULL)
    {
        numStudentGroups++;
        curr = curr->right;
    }

    student_group **studentGroupsArr = (student_group **)malloc(numStudentGroups * sizeof(student_group *));
    curr = root->student_group_list;
    int i = 0;
    while (curr != NULL)
    {
        studentGroupsArr[i++] = curr;
        curr = curr->right;
    }

    qsort(studentGroupsArr, numStudentGroups, sizeof(student_group *), compareStudentGroups);

    printf("Student Groups for Assignment ID %d (sorted by marks):\n", assignmentID);
    for (i = 0; i < numStudentGroups; i++)
    {
        printf("Group ID: %d\n", studentGroupsArr[i]->group_id);
        printf("Status: %s\n", studentGroupsArr[i]->status);
        printf("Marks: %.2f\n", studentGroupsArr[i]->marks);
        printf("\n");
    }

    free(studentGroupsArr);
}

void print_top_student_groups(assignment *root)
{
    if (root == NULL)
        return;

    print_top_student_groups(root->left);

    if (root->student_group_list != NULL)
    {
        student_group *current_group = root->student_group_list;
        float max_marks = current_group->marks;

        while (current_group != NULL)
        {
            if (current_group->marks > max_marks)
                max_marks = current_group->marks;
            current_group = current_group->right;
        }

        printf("Assignment ID: %d\n", root->assignment_id);
        printf("Topic Name: %s\n", root->topic_name);
        printf("Top Student Group(s):\n");
        current_group = root->student_group_list;
        while (current_group != NULL)
        {
            if (current_group->marks == max_marks)
            {
                printf("Group ID: %d\n", current_group->group_id);
                printf("Status: %s\n", current_group->status);
                printf("Marks: %.2f\n", current_group->marks);
            }
            current_group = current_group->right;
        }
        printf("\n");
    }

    print_top_student_groups(root->right);
}

void rangeSearchAssignment(assignment *root, int assignment_id_1, int assignment_id_2)
{
    if (root == NULL)
    {
        return;
    }
    if (root->assignment_id >= assignment_id_1 && root->assignment_id <= assignment_id_2)
    {
        printf("Assignment ID: %d\n", root->assignment_id);
        printf("Topic Name: %s\n", root->topic_name);
        printf("Assignment Status: %s\n", root->status);
        printf("Student Group Details:\n");

        student_group *group = root->student_group_list;
        while (group != NULL)
        {
            printf("Group ID: %d\n", group->group_id);
            printf("Status: %s\n", group->status);
            printf("Marks: %.2f\n", group->marks);
            printf("\n");
            group = group->right;
        }

        printf("---------------------\n");
    }
    if (root->assignment_id > assignment_id_1)
    {
        rangeSearchAssignment(root->left, assignment_id_1, assignment_id_2);
    }
    if (root->assignment_id < assignment_id_2)
    {
        rangeSearchAssignment(root->right, assignment_id_1, assignment_id_2);
    }
}

void inorder_traverse_student_groups(student_group *root, int assignment_id);
void print_student_group_details(student_group *group);
void print_yet_to_be_evaluated_groups(student *student_tree_root, assignment *assignment_tree_root);

void inorder_traverse_student_groups(student_group *root, int assignment_id)
{
    if (root == NULL)
    {
        return;
    }

    inorder_traverse_student_groups(root->left, assignment_id);
    print_student_group_details(root);
    inorder_traverse_student_groups(root->right, assignment_id);
}

void print_student_group_details(student_group *current_group)
{
    if (strcmp(current_group->status, "submitted") == 0)
    {
        printf("Pending evaluations:\n");
        printf("\tGroup ID: %d\n", current_group->group_id);
        printf("\tStatus: %s\n", current_group->status);
    }
    else if (strcmp(current_group->status, "evaluated") == 0)
    {
        student *student1 = current_group->student1;
        student *student2 = current_group->student2;
        int viva_remaining = 0;
        if (student1->viva_marks == 0)
        {
            printf("\tViva remaining for student %s (ID: %d)\n", student1->name, student1->student_id);
            viva_remaining = 1;
        }
        if (student2 != NULL && student2->viva_marks == 0)
        {
            printf("\tViva remaining for student %s (ID: %d)\n", student2->name, student2->student_id);
            viva_remaining = 1;
        }
        if (viva_remaining)
        {
            printf("\tViva is remaining for group %d\n", current_group->group_id);
        }
    }
    printf("\n");
}

void print_yet_to_be_evaluated_groups(student *student_tree_root, assignment *assignment_tree_root)
{
    if (assignment_tree_root == NULL)
    {
        return;
    }

    print_yet_to_be_evaluated_groups(student_tree_root, assignment_tree_root->left);

    if (strcmp(assignment_tree_root->status, "declared") == 0)
    {
        printf("Assignment ID: %d\n", assignment_tree_root->assignment_id);
        printf("Topic Name: %s\n", assignment_tree_root->topic_name);
        printf("\n");
        inorder_traverse_student_groups(assignment_tree_root->student_group_list, assignment_tree_root->assignment_id);
    }

    print_yet_to_be_evaluated_groups(student_tree_root, assignment_tree_root->right);
}

void read_input_file(const char *filename, student **student_tree_ptr, assignment **assignment_tree_ptr)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening the file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int student_id;
        char name[50], group_partner[50];
        int group_id, assignment_id;
        char deadline[11], status[20], topic_name[50];
        float offline_evaluation_marks, viva_marks;

        sscanf(line, "%d,%[^,],%[^,],%d,%d,%[^,],%[^,],%f,%f,%[^,\n]", &student_id, name, group_partner, &group_id, &assignment_id, deadline, status, &offline_evaluation_marks, &viva_marks, topic_name);

        insert_student_record(student_tree_ptr, assignment_tree_ptr, student_id, name, group_partner, group_id, assignment_id, deadline, status, offline_evaluation_marks, viva_marks, topic_name);
    }

    fclose(file);
}

void append_to_input_file(const char *filename, int student_id, char *name, char *group_partner, int group_id, int assignment_id, char *deadline, char *status, float offline_evaluation_marks, float viva_marks, char *topic_name)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("Error opening the file");
        return;
    }

    fprintf(file, "\n%d,%s,%s,%d,%d,%s,%s,%.1f,%.1f,%s", student_id, name, group_partner, group_id, assignment_id, deadline, status, offline_evaluation_marks, viva_marks, topic_name);

    fclose(file);
}

int main()
{
    student *student_tree = NULL;
    assignment *assignment_tree = NULL;
    int choice, group_id, assignment_id, assignment_id_1, assignment_id_2;
    char topic_name[50], deadline[20], filename[50], new_status[20];
    float s1_offline_marks, s1_viva_marks, s2_offline_marks, s2_viva_marks;

    read_input_file("input1.txt", &student_tree, &assignment_tree);
    do
    {
        printf("\nMenu:\n");
        printf("1. Insert student record\n");
        printf("2. Insert assignment\n");
        printf("3. Update student database\n");
        printf("4. Print not evluateed assignments\n");
        printf("5. Print late submission student groups\n");
        printf("6. Print student groups not yet evaluated\n");
        printf("7. Print student groups for assignment ID\n");
        printf("8. Print top student groups\n");
        printf("9. Range search assignment\n");
        printf("10. Student Details\n");
        printf("11. Assignment Details\n");
        printf("12. Student Group Details\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int student_id, group_id, assignment_id;
            char name[50], group_partner[50], deadline[11], status[20], topic_name[50];
            float offline_evaluation_marks, viva_marks;

            printf("Enter student ID: ");
            scanf("%d", &student_id);
            printf("Enter student name: ");
            scanf(" %[^\n]", name);
            printf("Enter group partner name: ");
            scanf(" %[^\n]", group_partner);
            printf("Enter group ID: ");
            scanf("%d", &group_id);
            printf("Enter assignment ID: ");
            scanf("%d", &assignment_id);
            printf("Enter deadline (dd-mm-yyyy): ");
            scanf(" %10s", deadline);
            printf("Enter status: ");
            scanf(" %19s", status);
            printf("Enter offline evaluation marks: ");
            scanf("%f", &offline_evaluation_marks);
            printf("Enter viva marks: ");
            scanf("%f", &viva_marks);
            printf("Enter topic name: ");
            scanf(" %[^\n]", topic_name);

            insert_student_record(&student_tree, &assignment_tree, student_id, name, group_partner, group_id, assignment_id, deadline, status, offline_evaluation_marks, viva_marks, topic_name);

            append_to_input_file("input1.txt", student_id, name, group_partner, group_id, assignment_id, deadline, status, offline_evaluation_marks, viva_marks, topic_name);

            printf("Student record inserted successfully!\n");
            break;
        }
        case 2:
            printf("Enter assignment ID: ");
            scanf("%d", &assignment_id);
            printf("Enter topic name: ");
            scanf("%s", topic_name);
            printf("Enter deadline: ");
            scanf("%s", deadline);
            printf("Enter filename: ");
            scanf("%s", filename);
            insert_assignment(&assignment_tree, &student_tree, assignment_id, topic_name, deadline, filename);
            break;

        case 3:
            printf("Enter group ID: ");
            scanf("%d", &group_id);
            printf("Enter assignment ID: ");
            scanf("%d", &assignment_id);
            printf("Enter S1 offline marks: ");
            scanf("%f", &s1_offline_marks);
            printf("Enter S1 viva marks: ");
            scanf("%f", &s1_viva_marks);
            printf("Enter S2 offline marks: ");
            scanf("%f", &s2_offline_marks);
            printf("Enter S2 viva marks: ");
            scanf("%f", &s2_viva_marks);
            printf("Enter new status: ");
            scanf("%s", new_status);
            update_status_and_marks(student_tree, assignment_tree, group_id, assignment_id, s1_offline_marks, s1_viva_marks, s2_offline_marks, s2_viva_marks, new_status);
            break;

        case 4:
            print_unevaluated_assignments(assignment_tree);
            break;

        case 5:
            print_late_submissions(assignment_tree);
            break;

        case 6:
            print_yet_to_be_evaluated_groups(student_tree, assignment_tree);
            break;

        case 7:
            printf("Enter assignmentID: ");
            scanf("%d", &assignment_id);
            printStudentGroupsForAssignmentID(assignment_tree, assignment_id);
            break;

        case 8:
            print_top_student_groups(assignment_tree);
            break;
        case 9:
            printf("Enter assignment ID 1: ");
            scanf("%d", &assignment_id_1);
            printf("Enter assignment ID 2: ");
            scanf("%d", &assignment_id_2);
            rangeSearchAssignment(assignment_tree, assignment_id_1, assignment_id_2);
            break;
		case 10:
			display_student(student_tree);
			break;
		case 11:
			display_assignment(assignment_tree);
			break;
		case 12:
			display_assignment_groups(assignment_tree);
			break;
		case 13:
			printf("Exiting...\n");
			break;
		default:
			printf("Invalid choice. Please enter a valid choice.\n");
			break;
		}
	} while (choice != 13);
	return 0;
}
