
#include <stdio.h>
#include <string.h>

#define MAX_SEM 8
#define MAX_COURSES 6

typedef struct
{
    char code[20];
    char name[50];
    int credit;
    float marks;
    float gradePoint;
} Course;

typedef struct
{
    Course courses[MAX_COURSES];
    int courseCount;
    float sgpa;
} Semester;

Semester semesters[MAX_SEM];
int semesterCount = 0;

// Marks থেকে grade point বের করা
float getGradePoint(float marks)
{
    if (marks >= 80) return 4.0;
    else if (marks >= 70) return 3.5;
    else if (marks >= 60) return 3.0;
    else if (marks >= 50) return 2.5;
    else if (marks >= 40) return 2.0;
    else return 0.0;
}

// Login Function
int login()
{
    char username[30];
    char password[30];

    const char correctUser[] = "BitBuds";
    const char correctPass[] = "1111";

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, correctUser) == 0 && strcmp(password, correctPass) == 0)
    {
        printf("\nLogin successful! Welcome \n");
        return 1;
    }
    else
    {
        printf("\nInvalid username or password. Exiting...\n");
        return 0;
    }
}

// Input Semester
void inputSemester()
{
    if (semesterCount >= MAX_SEM)
    {
        printf("Maximum semester limit reached!\n");
        return;
    }

    Semester sem = semesters[semesterCount];  // pointer নয়, direct variable
    printf("\nEnter number of courses for Semester %d (max %d): ",
           semesterCount + 1, MAX_COURSES);
    scanf("%d", &sem.courseCount);
    getchar(); // newline consume

    if (sem.courseCount <= 0 || sem.courseCount > MAX_COURSES)
    {
        printf("Invalid number of courses!\n");
        return;
    }

    float totalPoints = 0, totalCredits = 0;
    for (int i = 0; i < sem.courseCount; i++)
    {
        printf("\nCourse %d code: ", i + 1);
        scanf("%s", sem.courses[i].code);
        getchar(); // consume newline

        printf("Course %d name: ", i + 1);
        fgets(sem.courses[i].name, sizeof(sem.courses[i].name), stdin);
        sem.courses[i].name[strcspn(sem.courses[i].name, "\n")] = 0; // remove newline

        printf("Credit: ");
        scanf("%d", &sem.courses[i].credit);

        printf("Marks: ");
        scanf("%f", &sem.courses[i].marks);

        sem.courses[i].gradePoint = getGradePoint(sem.courses[i].marks);

        totalPoints += sem.courses[i].gradePoint * sem.courses[i].credit;
        totalCredits += sem.courses[i].credit;
    }

    sem.sgpa = totalPoints / totalCredits;
    semesters[semesterCount] = sem;  // save to array
    semesterCount++;
    printf("\n Semester %d SGPA calculated successfully!\n", semesterCount);
}

// Display SGPA
void displaySGPA()
{
    if (semesterCount == 0)
    {
        printf("No semester data available!\n");
        return;
    }
    for (int i = 0; i < semesterCount; i++)
    {
        printf("\n================= Semester %d =================\n", i + 1);
        printf("%-10s %-30s %-8s %-8s %-8s\n",
               "Code", "Course Name", "Credit", "Marks", "GP");
        printf("-------------------------------------------------------------\n");
        for (int j = 0; j < semesters[i].courseCount; j++)
        {
            printf("%-10s %-30s %-8d %-8.1f %-8.2f\n",
                   semesters[i].courses[j].code,
                   semesters[i].courses[j].name,
                   semesters[i].courses[j].credit,
                   semesters[i].courses[j].marks,
                   semesters[i].courses[j].gradePoint);
        }
        printf("-------------------------------------------------------------\n");
        printf("Semester %d SGPA: %.2f\n", i + 1, semesters[i].sgpa);
    }
}

// Display CGPA
void displayCGPA()
{
    if (semesterCount == 0)
    {
        printf("No semester data available!\n");
        return;
    }

    float totalPoints = 0, totalCredits = 0;
    for (int i = 0; i < semesterCount; i++)
    {
        for (int j = 0; j < semesters[i].courseCount; j++)
        {
            totalPoints += semesters[i].courses[j].gradePoint * semesters[i].courses[j].credit;
            totalCredits += semesters[i].courses[j].credit;
        }
    }

    float cgpa = totalPoints / totalCredits;
    printf("\n=========================================\n");
    printf(" Overall CGPA up to Semester %d = %.2f\n", semesterCount, cgpa);
    printf("=========================================\n");
}

// Main Menu
int main()
{
    if (!login()) return 0;

    int choice;
    do
    {
        printf("\n               ===== CGPA Counter System =====\n");
        printf("                 1. Input Semester Data\n");
        printf("                 2. Show SGPA of Each Semester\n");
        printf("                 3. Show Overall CGPA\n");
        printf("                 4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputSemester();
            break;
        case 2:
            displaySGPA();
            break;
        case 3:
            displayCGPA();
            break;
        case 4:
            printf("Thank you.....\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
