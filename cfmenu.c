
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 #define MAX_NAME_LENGTH 50
 #define STUDENT_PRICE 6
 #define ACADEMIC_PERSONAL_PRICE 16
 #define ADMINISTRATIVE_PERSONAL_PRICE 12
int menuSize; // for further calculations
struct normalMenu{
    char date[MAX_NAME_LENGTH];
    char soup[MAX_NAME_LENGTH];
    char main_dish[MAX_NAME_LENGTH];
    char side_dish[MAX_NAME_LENGTH];
    char extra[MAX_NAME_LENGTH];
    int sale_count[3];
};

struct veganMenu{
    char date[MAX_NAME_LENGTH];
    char soup[MAX_NAME_LENGTH];
    char main_dish[MAX_NAME_LENGTH];
    char side_dish[MAX_NAME_LENGTH];
    char extra[MAX_NAME_LENGTH];
    int sale_count[3];
};
struct vegetarianMenu{
    char date[MAX_NAME_LENGTH];
    char soup[MAX_NAME_LENGTH];
    char main_dish[MAX_NAME_LENGTH];
    char side_dish[MAX_NAME_LENGTH];
    char extra[MAX_NAME_LENGTH];
    int sale_count[3];
};

typedef struct{
    char *monthName;
    struct veganMenu *veganMenu;
    struct vegetarianMenu *vegetarianMenu;
    struct normalMenu *normalMenu;
}Cafeteria;

void initialize_menus(Cafeteria *cafeteria, char *csv_file_name);
void record_customer_counts(Cafeteria *cafeteria);
void calc_and_show_income(Cafeteria *cafeteria);

int main(){

    Cafeteria cafe = {NULL , NULL , NULL, NULL};
    char filename[] = "cafeteria_march_menu.csv";
    initialize_menus(&cafe , filename);
    record_customer_counts(&cafe);
    calc_and_show_income(&cafe);
    
    free(cafe.normalMenu);
    cafe.normalMenu = NULL;
    free(cafe.veganMenu);
    cafe.veganMenu = NULL;
    free(cafe.vegetarianMenu);
    cafe.vegetarianMenu = NULL;
    free(cafe.monthName);
    cafe.monthName = NULL;
   
    return 0;
}
void initialize_menus(Cafeteria *cafeteria, char *csv_file_name){
   
    
    FILE *fp=fopen(csv_file_name , "r");
    
    if(fp==NULL)
    {
        printf("Error opening the file\n");
        exit(0);
    }

    
    int normal_count = 0;
    int vegan_count = 0;
    int vegetarian_count = 0;
    // To count how many menus there are with reading each line in the file and save the result in a global variable.
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        // Remove the newbuffer character at the end of the buffer
        buffer[strcspn(buffer, "\n")] = 0;

        // Get the first field in the buffer
        char *field = strtok(buffer, ",");
        if (field != NULL) {
            // Remove the quotes around the field if present
            if (field[0] == '"' && field[strlen(field) - 1] == '"') {
                field[strlen(field) - 1] = 0;
                field++;
            }

            // Check if the field is "Normal", "Vegan", or "Vegetarian"
            if (strcmp(field, "Normal") == 0) {
                normal_count++;
            } else if (strcmp(field, "Vegan") == 0) {
                vegan_count++;
            } else if (strcmp(field, "Vegetarian") == 0) {
                vegetarian_count++;
            }
        }
    }
    menuSize = normal_count; // since there are 3 menus for each day any of menu counts can be used to initialize menuSize. menuSize will be used in further calculations so it is defined as global variable.
   //Memory allocations
    cafeteria->normalMenu = malloc(normal_count*sizeof(struct normalMenu));
    cafeteria->veganMenu = malloc(vegan_count*sizeof(struct veganMenu));
    cafeteria->vegetarianMenu = malloc(vegetarian_count*sizeof(struct vegetarianMenu));
    cafeteria->monthName = malloc(6*sizeof(char));
    rewind(fp); // set file position to the beginning of the file

   
    //Below code for reading each line and checking if all date fields are equal to Mar. setMonth is initially 1 , if the file has any date field other than "Mar" this variable will be set to 0
    //to show monthName is read from the file instead of directly setting it to "March"
    int setMonth = 1;
    while (fgets(buffer, sizeof(buffer), fp)) {
        char *monthField = strtok(buffer, ","); // set pointer to first field of the Line before comma which is "Normal" "Vegan" or "Vegetarian"
        monthField = strtok(NULL, ","); // set pointer to second field which represents Dates.
        char monthName[4];
        sscanf(monthField, "\"%*d-%3s", monthName); // to match an input string that starts with a '"' character followed by an integer , followed by a '-' followed by up to 3 characters. integer and first two characters are discarded.
        if (strcmp(monthName, "Mar") != 0) {
            setMonth = 0;
            break;
        }
    }
    if(setMonth){
        strcpy(cafeteria->monthName , "March");
    }
    
    //printf("%s" , cafeteria->monthName);

    // Reset the counts to use as indices into the arrays
    normal_count = 0;
    vegan_count = 0;
    vegetarian_count = 0;
   
    rewind(fp); // set file position to the beginning of the file
    while(fgets(buffer, sizeof(buffer), fp)){
        // Remove the newbuffer character at the end of the buffer
        buffer[strcspn(buffer, "\n")] = 0;
        // Get the first field in the buffer
        char *field = strtok(buffer, ",");
         if (field != NULL) {
            // Remove the quotes around the field if present
            if (field[0] == '"' && field[strlen(field) - 1] == '"') {
                field[strlen(field) - 1] = 0;
                field++;
            }
            // Check if the field is "Normal", "Vegan", or "Vegetarian"
            if(strcmp(field,"Normal")==0){
                strncpy(cafeteria->normalMenu[normal_count].date, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->normalMenu[normal_count].soup, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->normalMenu[normal_count].main_dish, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->normalMenu[normal_count].side_dish, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->normalMenu[normal_count].extra, strtok(NULL , ","), MAX_NAME_LENGTH);
                normal_count++;
            }
            else if(strcmp(field,"Vegan")==0){
                strncpy(cafeteria->veganMenu[vegan_count].date, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->veganMenu[vegan_count].soup, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->veganMenu[vegan_count].main_dish, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->veganMenu[vegan_count].side_dish, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->veganMenu[vegan_count].extra, strtok(NULL , ","), MAX_NAME_LENGTH);
                vegan_count++;
            }
            else if(strcmp(field,"Vegetarian")==0){
                strncpy(cafeteria->vegetarianMenu[vegetarian_count].date, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->vegetarianMenu[vegetarian_count].soup, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->vegetarianMenu[vegetarian_count].main_dish, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->vegetarianMenu[vegetarian_count].side_dish, strtok(NULL , ","), MAX_NAME_LENGTH);
                strncpy(cafeteria->vegetarianMenu[vegetarian_count].extra, strtok(NULL , ","), MAX_NAME_LENGTH);
                vegetarian_count++;
            }
            

         }
    }


    
    fclose(fp);

    //name of the month (to show monthName in cafeteria struct)
    printf("\n");
    printf("MONTH NAME : %s", cafeteria->monthName);
    printf("\n");
    //normal menu
    printf("~ ~ ~ ~ Normal menu for the first and last days of the month:\ndate--> %s\nsoup--> %s\nmain_dish %s\nside_dish %s\nextra-->%s\n",cafeteria->normalMenu[0].date , cafeteria->normalMenu[0].soup , cafeteria->normalMenu[0].main_dish , cafeteria->normalMenu[0].side_dish , cafeteria->normalMenu[0].extra);
    printf("\n");
    printf("~ ~ ~ ~ Normal menu for the first and last days of the month:\ndate--> %s\nsoup--> %s\nmain_dish %s\nside_dish %s\nextra-->%s\n",cafeteria->normalMenu[22].date , cafeteria->normalMenu[22].soup , cafeteria->normalMenu[22].main_dish , cafeteria->normalMenu[22].side_dish , cafeteria->normalMenu[22].extra);
    printf("\n");
    //vegan menu
    printf("~ ~ ~ ~ Vegan menu for the first and last days of the month:\ndate--> %s\nsoup--> %s\nmain_dish %s\nside_dish %s\nextra-->%s\n",cafeteria->veganMenu[0].date , cafeteria->veganMenu[0].soup , cafeteria->veganMenu[0].main_dish , cafeteria->veganMenu[0].side_dish , cafeteria->veganMenu[0].extra);
    printf("\n");
    printf("~ ~ ~ ~ Vegan menu for the first and last days of the month:\ndate--> %s\nsoup--> %s\nmain_dish %s\nside_dish %s\nextra-->%s\n",cafeteria->veganMenu[22].date , cafeteria->veganMenu[22].soup , cafeteria->veganMenu[22].main_dish , cafeteria->veganMenu[22].side_dish , cafeteria->veganMenu[22].extra);
    printf("\n");
    //vegetarian menu
    printf("~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\ndate--> %s\nsoup--> %s\nmain_dish %s\nside_dish %s\nextra-->%s\n",cafeteria->vegetarianMenu[0].date , cafeteria->vegetarianMenu[0].soup , cafeteria->vegetarianMenu[0].main_dish , cafeteria->vegetarianMenu[0].side_dish , cafeteria->vegetarianMenu[0].extra);
    printf("\n");
    printf("~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\ndate--> %s\nsoup--> %s\nmain_dish %s\nside_dish %s\nextra-->%s\n",cafeteria->vegetarianMenu[22].date , cafeteria->vegetarianMenu[22].soup , cafeteria->vegetarianMenu[22].main_dish , cafeteria->vegetarianMenu[22].side_dish , cafeteria->vegetarianMenu[22].extra);
    printf("\n");
    printf("Example output for normal menu ====> %s |%s | %s | %s | %s\n" , cafeteria->normalMenu[2].date, cafeteria->normalMenu[2].soup , cafeteria->normalMenu[2].main_dish , cafeteria->normalMenu[2].side_dish , cafeteria->normalMenu[2].extra);
    printf("Example output for vegan menu ====> %s |%s | %s | %s | %s\n" , cafeteria->veganMenu[7].date, cafeteria->veganMenu[7].soup , cafeteria->veganMenu[7].main_dish , cafeteria->veganMenu[7].side_dish , cafeteria->veganMenu[7].extra);
    printf("Example output for normal menu ====> %s |%s | %s | %s | %s\n" , cafeteria->vegetarianMenu[13].date, cafeteria->vegetarianMenu[13].soup , cafeteria->vegetarianMenu[13].main_dish , cafeteria->vegetarianMenu[13].side_dish , cafeteria->vegetarianMenu[13].extra);
}

void record_customer_counts(Cafeteria *cafeteria) {
    srand(time(0));
    int lower = 0, upper = 50; // ranges for random number generation
    for (int i = 0; i < menuSize; i++) {
        for (int j = 0; j < sizeof(cafeteria->normalMenu->sale_count)/sizeof(cafeteria->normalMenu->sale_count[0]); j++) {
            cafeteria->veganMenu[i].sale_count[j] = (rand() % (upper - lower + 1)) + lower;
            cafeteria->vegetarianMenu[i].sale_count[j] = (rand() % (upper - lower + 1)) + lower;
            cafeteria->normalMenu[i].sale_count[j] = (rand() % (upper - lower + 1)) + lower;
        }
    }
    
    printf("\n");
    printf("Counts for  the example  Vegan Menu ,  Date : %s , Student : %d , Academic Personal : %d , Administrative Personal : %d\n",cafeteria->veganMenu[3].date, cafeteria->veganMenu[3].sale_count[0],cafeteria->veganMenu[3].sale_count[1],cafeteria->veganMenu[3].sale_count[2]);
    printf("Counts for the example  Normal Menu ,  Date : %s , Student : %d , Academic Personal : %d , Administrative Personal : %d\n",cafeteria->normalMenu[11].date, cafeteria->normalMenu[11].sale_count[0],cafeteria->normalMenu[11].sale_count[1],cafeteria->normalMenu[11].sale_count[2]);
    printf("Counts for  the example  Vegetarian Menu ,  Date : %s , Student : %d , Academic Personal : %d , Administrative Personal : %d\n",cafeteria->vegetarianMenu[22].date, cafeteria->vegetarianMenu[22].sale_count[0],cafeteria->vegetarianMenu[22].sale_count[1],cafeteria->vegetarianMenu[22].sale_count[2]);
    printf("\n");
}

void calc_and_show_income(Cafeteria *cafeteria) {
    int normalMenuIncome = 0;
    int veganMenuIncome = 0;
    int vegetarianMenuIncome = 0;
    int studentIncome = 0;
    int academicIncome = 0;
    int administrativeIncome = 0;
    
    //sizeler hesaplancak

    for (int i = 0; i < menuSize; i++) {
        normalMenuIncome += cafeteria->normalMenu[i].sale_count[0] * STUDENT_PRICE + cafeteria->normalMenu[i].sale_count[1] * ACADEMIC_PERSONAL_PRICE + cafeteria->normalMenu[i].sale_count[2] * ADMINISTRATIVE_PERSONAL_PRICE;
        veganMenuIncome += cafeteria->veganMenu[i].sale_count[0] * STUDENT_PRICE + cafeteria->veganMenu[i].sale_count[1] * ACADEMIC_PERSONAL_PRICE + cafeteria->veganMenu[i].sale_count[2] * ADMINISTRATIVE_PERSONAL_PRICE;
        vegetarianMenuIncome += cafeteria->vegetarianMenu[i].sale_count[0] * STUDENT_PRICE + cafeteria->vegetarianMenu[i].sale_count[1] * ACADEMIC_PERSONAL_PRICE + cafeteria->vegetarianMenu[i].sale_count[2] * ADMINISTRATIVE_PERSONAL_PRICE;

        studentIncome += (cafeteria->normalMenu[i].sale_count[0] + cafeteria->veganMenu[i].sale_count[0] + cafeteria->vegetarianMenu[i].sale_count[0]) * 6;
        academicIncome += (cafeteria->normalMenu[i].sale_count[1] + cafeteria->veganMenu[i].sale_count[1] + cafeteria->vegetarianMenu[i].sale_count[1]) * 16;
        administrativeIncome += (cafeteria->normalMenu[i].sale_count[2] + cafeteria->veganMenu[i].sale_count[2] + cafeteria->vegetarianMenu[i].sale_count[2]) * 12;
    }

    printf("************ The Sales Results ************\n");
    printf("Total income by menu type:\n");
    printf("Normal Menu: %d TL\n", normalMenuIncome);
    printf("Vegan Menu: %d TL\n", veganMenuIncome);
    printf("Vegetarian Menu: %d TL\n", vegetarianMenuIncome);

    printf("Total income by customer type:\n");
    printf("Students: %d TL\n", studentIncome);
    printf("Academic Personnel: %d TL\n", academicIncome);
    printf("Administrative Personnel: %d TL\n", administrativeIncome);

    int totalIncome = normalMenuIncome + veganMenuIncome + vegetarianMenuIncome;
    printf("Overall monthly income: %d TL\n", totalIncome);
}