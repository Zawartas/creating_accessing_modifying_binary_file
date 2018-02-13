#include <cstdio>
#include <iostream>
#include <cstring>


using namespace std;

struct StudentInfo {
int indexID;
char name[30];
int groupID;
float score;
};

int main () {

int structSize = sizeof(StudentInfo);
printf("StudentInfo size: %d\n", structSize);

StudentInfo s;
FILE *input, *output;

input = fopen("formatted_data.txt", "r");
output = fopen("data_db", "wb");

int r, b, count = 0;
char n[30];
char k[30];
float m;

fscanf(input, "%d %s %s %d %f", &r, n, k, &b, &m);
strcat(n, " ");
strcat(n, k);

while (!feof(input)){

    count++;
    s.indexID = r;
    strcpy(s.name, n);
    s.groupID = b;
    s.score = m;

    fwrite(&s, structSize, 1, output);
    printf("%2d %5d %30s %3d %5.2f\n", count, s.indexID, s.name, s.groupID, s.score);

    fscanf(input, "%d %s %s %d %f", &r, n, k, &b, &m);
    strcat(n, " ");
    strcat(n, k);
}

cout << "Data read and saved to database file in binary mode.\n";
cout << "Total records written: " << count << endl;

fclose(input);
fclose(output);

return 0;
}
