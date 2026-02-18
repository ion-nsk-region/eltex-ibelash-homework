#include "ex_1.h"

int main(void) {
    char //*string_in, 
         *string_out = "String from file";
    const char *filename = "output.txt";

    createFile(filename);
    write2File(filename, string_out);
//    readFromFileEnd(filename, string_in);

//    printf("%s\n", string_in);

    return 0;
}
