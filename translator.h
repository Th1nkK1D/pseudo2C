int translator();
void writeStdFunction(FILE* pOut);
void writeIndent(FILE* pOut);
int processLine(char buffer[],FILE* pOut,int line);
int prepareArg(char arg[4][12],char varSet[64],TEMP_T tempData);
int writeOut(char arg[4][12],char printSet[64],int count,FILE* pOut);