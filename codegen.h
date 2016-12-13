#ifndef CODEGEN_H
#define CODEGEN_H

void createTMFile(char * infileName);
void generateCode(TreeNode * t, char * infileName);
void processCode(TreeNode * t);
void processCodeR(TreeNode * t);

void processIO(TreeNode * t);
void processInit(TreeNode * t);
void processInitGlobalsStatics(TreeNode * t);

std::string man_to_string(int i);
// bool checkArrayBothSides(TreeNode * t, bool leftArr, bool rightArr, bool &ans);
// void checkRightArray(TreeNode * t, bool &ans);
// void checkLeftArray(TreeNode * t, bool &ans);





#endif