#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//---------------------------------------------
//-------------------STRUCTS-------------------
//Structs for Towns
typedef struct town_node *ptrT;
struct town_node{
    ptrT prev;
    char town_name[46];
    int town_population;
    ptrT next;
};
typedef ptrT LinkedListT;
typedef ptrT posT;
//Struct for District
typedef struct district_node *ptrD;
struct district_node{
    ptrD prev;
    char district_name[46];
    int district_population;
    ptrT towns;
    ptrD next;
};
typedef ptrD LinkedListD;
typedef ptrD posD;
//---------------------------------------------
//------------------GLOBAL---------------------
int isRead=0; // If the Unsorted list is read then, isRead=1.
int isPopulated=0; // If the Sorting list is populated then, isPopulated=1.
int isSorted=0; //If the districts are sorted in the SortingList then isSorted=1.
int isSortedT=0;// If the towns are sorted in the SortingList then isSortedT=1.
LinkedListD SortingDistricts;//For Sorting Purpose, After the sorting process the SortingDistricts will be the head of the sorted list.
//---------------------------------------------
//------------Function Declarations------------
LinkedListD CreateEmptyD();
LinkedListT CreateEmptyT();
void loadInputFile(LinkedListD);
void printListD(LinkedListD);
void populateDistrictList(LinkedListD,char*,char*,int);
void InsertDistrictLast(LinkedListD L,char* district_name);
void radixSortDistricts(LinkedListD);
char *converted(int pop,int max);
void extendNames(LinkedListD L, int length);
void UnextendNames(LinkedListD L);
int  getMaxLengthDistrict(LinkedListD L);
void AddNewDistrictAndSort(LinkedListD);
void AddNewTownAndSort(LinkedListD L);
void CalculateTotalPol(LinkedListD );
void printDistrictInfoOnly(LinkedListD L);
void changePopT(LinkedListD L);
void DisplayMainMenu();
void saveOutputToFile(LinkedListD L);
int  getMaxTownPop(LinkedListD P);
void sortTowns(LinkedListD L);
void deleteTownsOfD(ptrD nodeD);
void deleteDistrictUsingName(LinkedListD L,char* district_name);
void delete_nodeD(LinkedListD , ptrD);
void deleteTownFromDistrict(LinkedListD L);
//---------------------------------------------
//-------------------MAIN----------------------
int main()  {
    //Creating the head for the loaded Info List before Sorting.
    LinkedListD UnsortedDistricts=CreateEmptyD();
    //Creating the head for the list of Sorted Info.
    SortingDistricts=CreateEmptyD();
    //Choosing Operation using User Input.
    int op=0;
    while(op!=14){
        DisplayMainMenu();
        scanf("%d",&op);
        switch(op){
            case 1: // Load the file into the UnsortedDistricts List.
                if(isRead==0){
                loadInputFile(UnsortedDistricts);}else{
                    printf("The List has already been loaded.");
                }
                break;
            case 2: // Print the info in the UnsortedDistricts List
                if(isRead==1) {
                    printf("\n--------Unsorted--------");
                    printListD(UnsortedDistricts);
                }else{
                    printf("The List hasn't been Loaded yet, Please choose (option 1.) first to load the list !\n");
                }
                break;
            case 3: // Radix Sort Info, based on District name alphabetically.
                if(isRead==1){
                    if(isSorted==1){
                        printf("The List has already been sorted!\n");
                    }else{
                        if(isPopulated==0){
                        loadInputFile(SortingDistricts); //Fill SortingDistricts with Information
                        isPopulated=1;
                        }
                        radixSortDistricts(SortingDistricts); //Radix Sort SortingDistricts list.
                        UnextendNames(SortingDistricts); //Remove Special Char# from names, used for sorting Purposes.
                    }
                }else printf("You have to load the list first!(Choose option 1.)!\n");
                break;
            case 4:// Radix Sort Towns Based on Town Population.
                if(isRead==1){
                    if(isSorted==1) {
                        sortTowns(SortingDistricts);
                    }else
                    {
                        printf("Please Sort the districts first--Choose Option 3!\n");
                    }
                }else{
                    printf("Please load the Lists first! -- Choose Option 1!\n");
                }
                break;
            case 5: //Prints Sorted Information.
                if(isRead==1){
                    if(isSorted==1&&isSortedT==1){
                        printListD(SortingDistricts);
                    }else printf("Please sort the list first! Choose Option(3) then Option(4), then try again!.\n");
                }else{
                    printf("Please load the list first!\n");
                }
                break;
            case 6: // Adds a new district to the SortedDistricts List and sorts it again to make sure its sorted right.
                if(isRead==1){
                    if(isPopulated==1){
                        AddNewDistrictAndSort(SortingDistricts);
                    }else{
                        loadInputFile(SortingDistricts);
                        AddNewDistrictAndSort(SortingDistricts);
                        isPopulated=1;
                    }
                }else printf("Please load the Lists first! -- Choose Option 1!\n");
                break;
            case 7: // Adds a town to a Certain District.
                if(isRead==1){
                    if(isPopulated==1){
                        AddNewTownAndSort(SortingDistricts);
                    }else{
                        loadInputFile(SortingDistricts);
                        AddNewTownAndSort(SortingDistricts);
                        isPopulated=1;
                    }
                }else printf("Please load the Lists first! -- Choose Option 1!\n");
                break;
            case 8://Delete Town From Specific District
            if(isRead==1){
                if(isSorted==1&&isSortedT==1){
                    deleteTownFromDistrict(SortingDistricts);
                }else printf("Please sort the list first! Choose Option(3) then Option(4), then try again!.\n");
            }else printf("Please load the Lists first! -- Choose Option 1!\n");
                break;
            case 9: //Delete a certain District using its name, after Deleting all of its towns.
                if(isRead==1) {
                    if(isSorted==1){
                        char d_name[46];
                        printf("\nPlease Enter the name of the district that you want to delete:");
                        scanf(" %[^\n]%*c", d_name);
                        deleteDistrictUsingName(SortingDistricts,d_name);
                    }else printf("Please Sort the districts first! Choose the sort choice from the list!\n");
                }else printf("Please load the Lists first! -- Choose Option 1!\n");
                break;
            case 10: // Calculate the total Population of Palestine, and prints the max and min town populations.
                if(isRead==1){
                    if(isSorted==1){
                        CalculateTotalPol(SortingDistricts);
                    }else printf("Please Sort the List first!\n");

                }else printf("Please load the Lists first! -- Choose Option 1!\n");
                break;
            case 11: // Printf Districts Names and Districts Populations without town information.
                if(isRead==1){
                    if(isSorted==1){
                        printDistrictInfoOnly(SortingDistricts);
                    }else printf("Please Sort the List first!\n");

                }else printf("Please load the Lists first! -- Choose Option 1!\n");
                break;
            case 12:// Change Population of a Certain Town.
                if(isRead==1){
                    if(isSorted==1){
                        changePopT(SortingDistricts);
                    }else printf("Please Sort the list first!,Choose Option(3).\n");
                }else printf("Please load he list first!\n");
                break;
            case 13: //Saves the SortingDistricts to Output txt File.
                if(isRead==1){
                    if(isSorted==1){
                        saveOutputToFile(SortingDistricts);
                    }else printf("Please Sort the list first -- Choose Option 3!\n");

                }else printf("Please load the Lists first! -- Choose Option 1!\n");
                break;
            case 14:// Case 14, op=14 , it exists the loop and closes the program.
                printf("\n=========================\n");
                printf ("Thank you for using my program!\n");
                printf ("Goodbye!\n");
                printf("=========================\n");
                break;
            default: //Default case in case user inputs something unexpected.
                printf("\nPlease choose a valid operation by writing the operation number !\n\n");
                break;
        }
    }
    return 0;
}
//---------------------------------------------
//------------Function Definitions-------------
LinkedListD CreateEmptyD(){
    struct district_node* L;
    L=(LinkedListD)malloc(sizeof(struct district_node));
    if(L==NULL){
        printf("Out of Memory! \n");
        return NULL;
    }
    L->next=NULL;
    L->prev=NULL;
    return L;
}
LinkedListT CreateEmptyT(){
    struct town_node* L;
    L=(LinkedListT)malloc(sizeof(struct town_node));
    if(L==NULL) {
        printf("Out of Memory!\n");
        return NULL;
    }
    L->next=NULL;
    L->prev=NULL;
    return L;
}
void loadInputFile(LinkedListD UnsortedDistrict){
    char line[50];
    FILE * fpointer_in = fopen("districts.txt", "r");
    if (fpointer_in != NULL) {
        printf("Loading ...\n");
        //int counter = 1;
        while (fgets(line, 50, fpointer_in) != NULL) {
            //printf("Reading Line#%d\n", counter++);
            char *district_name = strtok(line, "|");
            char *town_name = strtok(NULL, "|");
            int population = atoi(strtok(NULL, "|"));
            populateDistrictList(UnsortedDistrict,district_name,town_name,population);
        }
        printf("--->Reading Successful!\n");
        isRead = 1;
    } else {
        printf("----File not found----\n---Error opening File---\n\n\n");
    }
    fclose(fpointer_in);
}
void InsertDistrictLast(LinkedListD L,char* district_name){ // Function to Populate the district list.
    LinkedListD last_district = L;  // Find The position of last district to Insert after it.
    while (last_district->next != NULL) {
        last_district = last_district->next;
    }
    LinkedListD district_ptr = L->next;
    while (district_ptr != NULL) { //Checks if the district already exists to populate it, if it doesn't it creates a new district
        if (strcmp(district_ptr->district_name, district_name) == 0) { // if it exists it breaks out of the loop.
            break;
        }
        district_ptr=district_ptr->next;
    }
    if (district_ptr == NULL) { // it creates a district in case it doesn't exist already
        LinkedListD new_district = CreateEmptyD();
        strcpy(new_district->district_name, district_name);
        last_district->next = new_district;
        new_district->prev = last_district;
        //  printf("New District Inserted\n"); // it inserts a districts at last position(After populating it).
    }
}
void populateDistrictList(LinkedListD L,char* district_name,char* town_name,int population){ // Function to Populate the district list.
    LinkedListD last_district = L;  // Find The position of last district to Insert after it.
    while (last_district->next != NULL) {
        last_district = last_district->next;
    }
    LinkedListD district_ptr = L->next;
    while (district_ptr != NULL) { //Checks if the district already exists to populate it, if it doesn't it creates a new district
        if (strcmp(district_ptr->district_name, district_name) == 0) { // if it exists, Create a new town and insert it.
            LinkedListT new_town=CreateEmptyT();
            strcpy(new_town->town_name, town_name);
            new_town->town_population = population;
            district_ptr->district_population+=new_town->town_population;
            LinkedListT last_town=district_ptr->towns;
            if (last_town!=NULL) { //If there is a town we have to find the last position to insert after it.
                while (last_town->next != NULL) { //Finding Last Town
                    last_town=last_town->next;
                }
                last_town->next=new_town; //Inserting After Last Town.
                new_town->prev=last_town;
            } else {
                district_ptr->towns=new_town; //If the town is the first one we insert it at the town pointer.
            }
          //  printf("Town Inserted into existing district\n"); //Town inserted into district that already exist.
            break;
        }
        district_ptr=district_ptr->next;
    }
    if (district_ptr == NULL) { // it creates a district in case it doesn't exist already
        LinkedListD new_district = CreateEmptyD();
        strcpy(new_district->district_name, district_name);
        LinkedListT new_town = CreateEmptyT();
        strcpy(new_town->town_name, town_name);
        new_town->town_population = population; // it populates the town and district node
        new_district->towns=new_town;
        //printf("Town Inserted into new District\n");
        new_district->district_population = population;
        last_district->next = new_district;
        new_district->prev = last_district;
      //  printf("New District Inserted\n"); // it inserts a districts at last position(After populating it).
    }
}
void printListD(LinkedListD Districts) {
    printf("\n----------LIST----------\n");
    if(Districts==NULL||Districts->next==NULL){
        printf("\n\n=====LIST IS EMPTY=====\n\n");
        return;
    }
    posD indexD = Districts->next;
    while (indexD != NULL) {
        posT indexT = indexD->towns;
        if (indexT!=NULL) {
            while (indexT != NULL) {
                printf("%s|%s|%d\n", indexD->district_name, indexT->town_name, indexT->town_population);
                indexT = indexT->next;
            }
        }else printf("%s|Has No Towns Yet|0\n",indexD->district_name);
        indexD = indexD->next;
    }
}
void AddNewDistrictAndSort(LinkedListD L){
    char d_name[46];
    printf("\nPlease Enter the name of the District you want to add:");
    scanf(" %[^\n]%*c",d_name);
    InsertDistrictLast(L,d_name);
    isSorted=0;
    radixSortDistricts(L);
    UnextendNames(L);
}
void AddNewTownAndSort(LinkedListD L){
    char d_name[46];
    char t_name[46];
    int t_pop=0;
    int flag=0;
    printf("\nPlease Enter the name of the District you want to add the town to:");
    scanf(" %[^\n]%*c",d_name);
    printf("\nPlease Enter a name of town you want to add %s:",d_name);
    scanf(" %[^\n]%*c",t_name);
    printf("\nPlease Enter the population of  the town (%s) that you want to add:",t_name);
    scanf("%d", &t_pop);
    ptrD P=L->next;
    while (P!=NULL){
        if(strcmp(P->district_name,d_name)==0){
            populateDistrictList(L,d_name,t_name,t_pop);
            isSortedT=0;
            sortTowns(L);
            flag=1;
        }
        P=P->next;
    }
    if (flag==1){
        printf("\n--->Town %s Added successfully to District %s!\n",t_name,d_name);
    }else printf("\nDistrict %s not found, can't add town.\nPlease make sure you spelled the district name right, or add it using option 6!\n\n",d_name);

}
void deleteDistrictUsingName(LinkedListD L,char* district_name){
    ptrD P=L->next;
    while (P!=NULL) {
        if (strcmp(P->district_name, district_name) == 0) {
            deleteTownsOfD(P);
            delete_nodeD(L, P);
            printf("District #%s deleted!\n", district_name);
            return;
        }
        P = P->next;
    }
    printf("\nDistrict Not Found!\n");
}
void delete_nodeD(LinkedListD L, ptrD old){
    if (old!=NULL){
        if(old==L->next){ // If the node is the first, Make the head point to the second and the second prev to the head, and free old.
            if(old->next!=NULL) { // If it is not the first and last node.
                L->next = old->next;
                old->next->prev = L;
                free(old);
            }else{ // If old is first and last
                L->next=NULL;
                L->prev=NULL;
                free(old);
            }
        }else if(old->next!=NULL) { // If old is not the first node, and not the last node.
            old->prev->next = old->next;
            old->next->prev = old->prev;
            free(old);
        }else{ //If Old is the last node, make the one before it point to NULL, and free Old.
            old->prev->next=NULL;
            free(old);
        }
    }
}
void deleteTownsOfD(ptrD nodeD){
    if(nodeD==NULL||nodeD->towns==NULL){ //If District is Empty or if it has no towns, exit
        return;
    }
    ptrT P=nodeD->towns;
    while (P!=NULL){ // Traverse Towns and delete them and free their memory.
        ptrT next = P->next;
        free(P);
        P=next;
    }
}
void CalculateTotalPol(LinkedListD Districts){
    if(Districts==NULL||Districts->next==NULL){
        printf("\n\n=====LIST IS EMPTY=====\n\n");
        return;
    }
    char maxtown_name[46];
    int maxtown_pop;
    char mintown_name[46];
    int mintown_pop;
    int totalPalestinePop=0;
    posD indexD = Districts->next;
    strcpy(maxtown_name,indexD->towns->town_name);
    strcpy(mintown_name,indexD->towns->town_name);
    maxtown_pop=indexD->towns->town_population;
    mintown_pop=indexD->towns->town_population;
    while (indexD != NULL) {
        posT indexT = indexD->towns;
        while (indexT != NULL) {
            if(indexT->town_population>maxtown_pop){
                maxtown_pop=indexT->town_population;
                strcpy(maxtown_name,indexT->town_name);
            }
            if(indexT->town_population<mintown_pop){
                mintown_pop=indexT->town_population;
                strcpy(mintown_name,indexT->town_name);
            }
            totalPalestinePop+=indexT->town_population;
            indexT = indexT->next;
        }
        indexD = indexD->next;
    }
    printf("\n=========================\n");
    printf("Palestine's Total Population =%d\n",totalPalestinePop);
    printf("--------------------------\n");
    printf("Max Population:%s,%d\n",maxtown_name,maxtown_pop);
    printf("Min Population:%s,%d\n",mintown_name,mintown_pop);
    printf("=========================\n");
}
void printDistrictInfoOnly(LinkedListD L){
    if(L==NULL||L->next==NULL){
        printf("\n\n=====LIST IS EMPTY=====\n\n");
        return;
    }
    printf("\n=========================\n");
    posD indexD = L->next;
    while (indexD != NULL) {
        printf("%s, %d\n",indexD->district_name,indexD->district_population);
        indexD = indexD->next;
    }
    printf("=========================\n");
}
void DisplayMainMenu() {
    printf("-----------------------\n");
    printf("----Operations Menu----\n");
    printf("1. Load the input file.\n");
    printf("2. Print the loaded information before sorting.\n");
    printf("3. Sort the districts alphabetically.\n");
    printf("4. Sort the towns for each district based on population in ascending order.\n");
    printf("5. Print the sorted information.\n");
    printf("6. Add a new district to the list of sorted districts.\n");
    printf("7. Add a new town to a certain district.\n");
    printf("8. Delete a town from a specific district. \n");
    printf("9. Delete a complete district.\n");
    printf("10.Calculate the population of Palestine, the max and min town population.\n");
    printf("11.Print the districts and their total population.\n");
    printf("12.Change the population of a town.\n");
    printf("13.Save to output file.\n");
    printf("14.Exit\n");
    printf("-----------------------\n");
    printf("Choose Operation Number:");
}
void radixSortDistricts(LinkedListD ListToSort) { // Function to radixSort LinkedListD alphabetically based on the district_name
    if (ListToSort==NULL||ListToSort->next==NULL) { //Check if the inputted linked list is empty
        printf("---ERROR---List is empty, Can't sort an empty list.\n");
        return;
    }
    int max=getMaxLengthDistrict(ListToSort); // int max is set to getMaxLengthDistrict which returns the maximum length of a district name.
    extendNames(ListToSort, max); // Adds a special Character'#' to make names of equal length.
    //printf("=====District Names Extended====\n");
    LinkedListD sortStation[256]; // Defining and Creating an Array of LinkedLists used in sorting, as a temporary stations.
    for (int i=0;i<256;i++){ // One list for each Character, in case a town contains a special char such as (a'a) which is the english writing for the letter "ein" in arabic.
        sortStation[i]=CreateEmptyD();
    }
    //printf("=====Filling Sorting Stations====\n");
    printf("Sorting...\n");
    for (int currentCharPos=max-1;currentCharPos>=0;currentCharPos--){
        ptrD P=ListToSort->next;
        ptrD nextP;
        while (P!=NULL) {
            nextP=P->next;
            int letter=P->district_name[currentCharPos];
            P->next=sortStation[tolower(letter)]->next; // tolower so that no matter uppercase or lowercase, district names will still be sorted correct alphabetically
            sortStation[tolower(letter)]->next=P;
            P=nextP;
        }
        ptrD last = ListToSort; //After Splitting the districts into stations based on the char at currentCharPos, they must be reconnected.
        for (int i=0; i<256; i++) {
            P=sortStation[i]->next;
            while (P!=NULL) {
                last->next=P;
                last=P;
                P=P->next;
            }
            sortStation[i]->next=NULL;
        }
        last->next=NULL;
    }
    ptrD P=SortingDistricts->next;
    if (P!=NULL){
        P->prev=SortingDistricts;
        while (P!=NULL&&P->next!=NULL){
           P->next->prev=P;
           P=P->next;
        }

    }
    for (int i = 0; i < 256; i++) {
        free(sortStation[i]); //Empty Station Lists to go through the next iteration of RadixSort.
    }
    printf("--->Sorting Districts Successful!\n");
    isSorted=1; //Flag to prevent from sorting the list again.
}
int  getMaxLengthDistrict(LinkedListD L){
    int max=0;
    posD P=L->next;
    while (P!=NULL){
        int name_length= strlen(P->district_name);
        if(name_length>max){
            max=name_length;
        }
        P=P->next;
    }
    return max;
}
void extendNames(LinkedListD L, int length){
    posD P= L->next;
    while(P!=NULL){ //Loop to traverse the list and compare each district name length with the max length and then make them equal.
        int lengthP= strlen(P->district_name);
        if(lengthP<length){
            int extendAmount=length-lengthP;
            for(int i=0; i<extendAmount;++i){
                strcat(P->district_name,"#");
            }
        }
        P=P->next;
    }
}
void UnextendNames(LinkedListD L){
    int max=getMaxLengthDistrict(L);
    posD P=L->next;
    while (P!=NULL) {
        int index=0;
        for (int i=0;i<max;i++) {
            if (P->district_name[i]!='#') {
                P->district_name[index++]=P->district_name[i];
            }
        }
        P->district_name[index]='\0';
        P=P->next;
    }
}
void saveOutputToFile(LinkedListD L){
    FILE* fpointerEmpty= fopen("sorted_districts.txt","w");
    fclose(fpointerEmpty);
    if(L==NULL||L->next==NULL){
        printf("\n\n=====LIST IS EMPTY=====\n\n");
        return;
    }
    FILE* fpointer =fopen("sorted_districts.txt","a");
    posD indexD = L->next;
    while (indexD != NULL) {
        posT indexT = indexD->towns;
        fprintf(fpointer,"%s District, Population=%d\n",indexD->district_name,indexD->district_population);
        while (indexT != NULL) {
            fprintf(fpointer,"%s,%d\n",indexT->town_name, indexT->town_population);
            indexT = indexT->next;
        }
        indexD = indexD->next;
    }
    printf("Output Saved to file (sorted_district.txt) Successfully!\n");
    fclose(fpointer);
}
void changePopT(LinkedListD L) {
    if (L == NULL || L->next == NULL) {
        printf("\n\n=====LIST IS EMPTY=====\n\n");
        return;
    }
    char district_name[46];
    char town_name[46];
    int townpop;
    printf("\nPlease Enter the name of the District, that town is in:");
    scanf(" %[^\n]%*c", district_name);
    printf("\nPlease Enter the name of the town you want to change the population of:");
    scanf(" %[^\n]%*c", town_name);
    printf("\nPlease Enter the population you want to set:");
    scanf("%d", &townpop);
    posD indexD = L->next;
    while (indexD != NULL) {
        if (strcmp(indexD->district_name, district_name) == 0) {
            posT indexT = indexD->towns;
            while (indexT != NULL) {
                if (strcmp(indexT->town_name, town_name) == 0) {
                    int Diff;
                    if (indexT->town_population > townpop) {
                        Diff = indexT->town_population - townpop;
                        indexT->town_population = townpop;
                        printf("Town Population Changed!\n");
                        indexD->district_population = indexD->district_population - Diff;
                        printf("Total District Population Changed!\n");
                    } else if (indexT->town_population < townpop) {
                        Diff = townpop - indexT->town_population;
                        indexT->town_population = townpop;
                        printf("Town Population Changed!\n");
                        indexD->district_population = indexD->district_population + Diff;
                        printf("Total District Population Changed!\n");
                    } else {
                        printf("Town Population is the same! nothing changes!\n");
                    }
                }
                indexT = indexT->next;
            }
        }
        indexD = indexD->next;
    }
}
void sortTowns(LinkedListD L){
    if(L==NULL||L->next==NULL){
        printf("===List is Empty===\n nothing to sort.");
        return;
    }
    L=L->next;
    while (L!=NULL){
        int maxPop;
        maxPop= getMaxTownPop(L);
        LinkedListT LT = CreateEmptyT();
        LT->next=L->towns;
        LinkedListT SortingStationsT[10];
        for(int i=0;i<10;i++){
            SortingStationsT[i]=CreateEmptyT();
        }
      //  printf("Sorting Towns of %s ...\n",L->district_name);
        for (int digitPos=maxPop-1;digitPos>=0;digitPos--){
            ptrT P=LT->next;
            ptrT nextP;
            while (P != NULL) {
                nextP = P->next;
                int pop = P->town_population;
                char* popString = converted(pop, maxPop);
                int digitAtPos = popString[digitPos] - '0';
                if (SortingStationsT[digitAtPos]->next==NULL||SortingStationsT[digitAtPos]->next->town_population>=P->town_population){
                    P->next = SortingStationsT[digitAtPos]->next;
                    SortingStationsT[digitAtPos]->next = P;
                } else {
                    ptrT pos = SortingStationsT[digitAtPos]->next;
                    while (pos->next != NULL && pos->next->town_population < P->town_population) {
                        pos = pos->next;
                    }
                    P->next = pos->next;
                    pos->next = P;
                }
                P=nextP;
            }
            ptrT last= LT;
            for(int i=0;i<10; i++){
                P=SortingStationsT[i]->next;
                while (P!=NULL) {
                    last->next = P;
                    last = P;
                    P = P->next;
                }
                SortingStationsT[i]->next=NULL;
            }
            last->next=NULL;
        }
        for(int i=0;i<10;i++){
            free(SortingStationsT[i]);
        }
        ptrT curP=LT->next;
        if (curP!=NULL){
            curP->prev=LT;
            while (curP!=NULL&&curP->next!=NULL){
                curP->next->prev=curP;
                curP=curP->next;
            }
        }
        L->towns=LT->next;
        free(LT);
        L=L->next;
    }
    isSortedT=1;
    printf("--->Sorting Towns Successful!\n");
}
int  getMaxTownPop(LinkedListD P){
    int max=0;
    posT PT=P->towns;
    while (PT!=NULL){
        int pop_length=0;
        int population=PT->town_population;
        while (population!=0){
            population=population/10;
            pop_length++;
            if(pop_length>max){
                max=pop_length;
            }
        }
        PT=PT->next;
    }
    return max;
}
char* converted(int pop, int max) {
    char* popStr = (char*)malloc(max + 1);
    if (popStr == NULL) {
        printf("Out Of Memory!\n");
        return NULL;
    }
    snprintf(popStr, max + 1, "%d", pop);
    int popLength = strlen(popStr);
    if (popLength<max) {
        int zerosCount = max-popLength;
       for (int i=popLength;i>=0;--i){
            popStr[i+zerosCount]=popStr[i];
        }
        for (int i=0; i<zerosCount; i++) {
            popStr[i]='0';
        }
    }
    return popStr;
}
void deleteTownFromDistrict(LinkedListD L){
    char d_name[46];
    char t_name[46];
    printf("\nPlease Enter the name of the District you want to delete the town from:");
    scanf(" %[^\n]%*c",d_name);
    printf("\nPlease Enter the name of the town you want to delete %s:",d_name);
    scanf(" %[^\n]%*c",t_name);
    ptrD indexD=L->next;
    while (indexD!=NULL){ //Check if the district or the town exists.
        if (strcmp(d_name,indexD->district_name)==0) { //If the district exists, Search for the town
            ptrT indexT=indexD->towns;
            while (indexT!=NULL){
                if (strcmp(indexT->town_name,t_name)==0){ //If the town exists delete it
                    if(indexT==indexD->towns){//If the node is the first node, check if it is the last too
                        if(indexT->next==NULL){ // If it is the last make the towns pointer, point to NULL
                            indexD->towns=NULL;
                            indexD->district_population-=indexT->town_population;
                            free(indexT);
                            printf("Town %s Deleted from District %s successfully!\n",t_name,d_name);
                            return;
                        }else{// If it is not the last, make towns pointer point to the second node
                            indexD->towns=indexT->next;
                            indexT->next->prev=NULL;
                            indexD->district_population-=indexT->town_population;
                            free(indexT);
                            printf("Town %s Deleted from District %s successfully!\n",t_name,d_name);
                            return;
                        }
                    }else if(indexT->next==NULL) {//If it is the last, make its prev point to NULL, and free it.
                        indexT->prev->next = NULL;
                        indexD->district_population-=indexT->town_population;
                        free(indexT);
                        printf("Town %s Deleted from District %s successfully!\n",t_name,d_name);
                        return;
                    } else{ //If it is not the first node, and it is not the last node, then make the previous node point to the next node, and free indexT.
                        indexT->prev->next=indexT->next;
                        indexT->next->prev=indexT->prev;
                        indexD->district_population-=indexT->town_population;
                        free(indexT);
                        printf("Town %s Deleted from District %s successfully!\n",t_name,d_name);
                        return;
                    }
                }
                indexT=indexT->next;
            }

        }
        indexD=indexD->next;
    }
    printf("--->Deletion Failed\nTown Or District Not Found!\n");
}
//---------------------------------------------
//----------------END OF CODE------------------
//---------------------------------------------
