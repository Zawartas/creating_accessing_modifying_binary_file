#include <cstdio>
#include <iostream>

using namespace std;

struct StudentInfo {
int indexID;
char name[30];
int groupID;
float score;
};

int main () {

int structSize = sizeof(StudentInfo);
int r, recNum, found;
long POS;
printf("StudentInfo size: %d\n", structSize);

StudentInfo s;
FILE *input;

input = fopen("data_db", "rb+"); //+means that the file has to exist

int count = 0;

rewind(input);

    cout << "________________________________________________\n";
    cout << "Demonstrating searching for records.\n";
    cout << "Looking for index number 10017.\n";

r = 10017;
found = 0;
POS = ftell(input);
do {
    fread(&s, structSize, 1, input);
    if (s.indexID == r){
        cout << endl << "Found index number: " << r;
        found = POS/structSize +1;
        cout << " at record number " << found << endl;
        cout << "Name and marks are: " << s.name << " " << s.score << endl;
        break;
    }
    else {
        fread(&s, structSize, 1, input);
        POS = ftell(input);
        }
    } while (!feof(input));

if (found == 0)
    cout << "\nIndex number has not been found in database.\n";
    cout << "________________________________________________\n";
    cout << "Demonstrating direct access to records.\n";
    cout << "Accessing sixth record in the database.\n";
    recNum = 6;

    POS = (recNum - 1)*structSize;
    fseek(input, POS, SEEK_SET);
    //we can use SEEK_SET, SEEK_CUR, SEEK_END
    //it means move pointer POS amount of bytes from
    //SET - beginning of file, CUR - from current position
    //END - from end of file
    //value can have minus so (input, -7, SEEK_END)
    //means 7 bytes back from the end

    fread(&s, structSize, 1, input);
    printf("Data under record %d: \nstarting byte: %d\n index: %d\n name: %s\n group: %d\n score: %5.2f\n",
           recNum, POS, s.indexID, s.name, s.groupID, s.score);
    cout << "________________________________________________\n";
    cout << "Demonstrating adjusting records.\n";
    cout << "Record at index number 10029.\n";

r = 10029;
found = 0;
rewind(input);
POS = ftell(input);
fread(&s, structSize, 1, input);
do {
    if (s.indexID == r) {found = 1; break;}
    else {
        POS = ftell(input);
        fread(&s, structSize, 1, input);
        }
    } while (!feof(input));
if (found == 0)
    cout << "\nIndex number has not been found in database.\n";
    cout << "________________________________________________\n";

printf("Data under record %d: \nstarting byte: %d\n index: %d\n name: %s\n group: %d\n score: %5.2f\n",
   POS/structSize+1, POS, s.indexID, s.name, s.groupID, s.score);
       cout << "\nWe adjust the score to 66.6\n";
       s.score = 66.6;
       fseek(input, POS, SEEK_SET); //we again move in front of that set of data
       fwrite(&s, structSize, 1, input); //and write new data
       fseek(input, POS, SEEK_SET); //move back again
       fread(&s, structSize, 1, input); //and read to verify
       printf("Data under record %d: \nstarting byte: %d\n index: %d\n name: %s\n group: %d\n score: %5.2f\n",
   POS/structSize+1, POS, s.indexID, s.name, s.groupID, s.score); //and print to check


fclose(input);

return 0;
}
