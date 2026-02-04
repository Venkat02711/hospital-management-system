#include <stdio.h>
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    struct Patient p;

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Disease: ");
    scanf(" %[^\n]", p.disease);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Patient added successfully!\n");
}

void viewPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Patient Records ---\n");
    while (fread(&p, sizeof(p), 1, fp)) {
        printf("\nID: %d", p.id);
        printf("\nName: %s", p.name);
        printf("\nAge: %d", p.age);
        printf("\nDisease: %s\n", p.disease);
    }

    fclose(fp);
}

void searchPatient() {
    FILE *fp = fopen("patients.dat", "rb");
    struct Patient p;
    int id, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("\nPatient Found!");
            printf("\nName: %s", p.name);
            printf("\nAge: %d", p.age);
            printf("\nDisease: %s\n", p.disease);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Patient not found!\n");

    fclose(fp);
}

void updatePatient() {
    FILE *fp = fopen("patients.dat", "rb+");
    struct Patient p;
    int id, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Patient ID to update: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", p.name);
            printf("Enter new Age: ");
            scanf("%d", &p.age);
            printf("Enter new Disease: ");
            scanf(" %[^\n]", p.disease);

            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);
            found = 1;
            printf("Patient updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Patient not found!\n");

    fclose(fp);
}

void deletePatient() {
    FILE *fp = fopen("patients.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Patient p;
    int id, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            found = 1;
        } else {
            fwrite(&p, sizeof(p), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found)
        printf("Patient deleted successfully!\n");
    else
        printf("Patient not found!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== Hospital Management System =====\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: deletePatient(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}