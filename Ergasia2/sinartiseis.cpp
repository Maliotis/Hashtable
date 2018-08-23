#include "sinartiseis.h"
using namespace std;
int C;
int UID = -1;
int IID = -1;
deiktisUser arxiu = NULL;
deiktisItem arxii = NULL;
deiktisUser nodeUser;
deiktisItem nodeItem;
deiktisUser tempUser;
deiktisItem tempItem;
//Vector is a dynamically alocated array and can be resized,
//(STL) Standard Template Library search for container component.
// < > takes the type of of the vector you want to create,
//Search for generic classes for more info.
vector<deiktisUser> tableU;
vector<deiktisItem> tableI;

deiktisUser push_User(deiktisUser arxiUser,string name){
    nodeUser = new user;
    nodeUser->uname = name;
    nodeUser->uid = ++UID;
    nodeUser->next = arxiUser;
    arxiUser = nodeUser;
    return arxiUser;

}

deiktisItem push_Item(deiktisItem arxiItem,string name){
    nodeItem = new item;
    nodeItem->iname = name;
    nodeItem->iid = ++IID;
    nodeItem->next = arxiItem;
    arxiItem = nodeItem;
    return arxiItem;
}

void initialize (int B)
{
    C = B;
    for (int i=0; i<B; i++){
        nodeUser = new user;
        nodeUser->next = NULL;
        tableU.push_back(nodeUser);
        nodeItem = new item;
        nodeItem->next = NULL;
        tableI.push_back(nodeItem);
    }
}

int create_id (char* input_file, char* output_file)
{
    int ret;
    char* word1 = new char;
    char* word2 = new char;
    int rating,time;
    int sum=0;
    int temp;
    int tempI;
    int sumI;
    int tempWord1=-1,tempWord2=-1;
    ifstream file (input_file);
    ofstream writeFile (output_file);
    if(!file){
        ret = 0;
    }
    else{
        ret=1;
        while(!file.eof()){
            temp = 0; sum = 0; sumI = 0; tempI = 0;
            file >> word1 >> word2 >> rating >> time;
            for(int j=0; word1[j]!='\0'; j++){
                //sum = sum + word1[j];
                // The j+1 increases the sum value in order to optimize the code.
                sum = sum + (j+1)*word1[j];
            }
            for (int g=0 ;word2[g] != '\0'; g++){
                //sum = sum + word2[g];
                // The g+1 increases the sum value in order to optimize the code.
                sumI = sumI + (g+1)*word2[g];
            }
            temp = sum % C;
            tempI = sumI % C;
            
            arxiu = tableU[temp];
            while(arxiu != NULL){
                if((arxiu->uname).compare(word1)==0){
                    tempWord1 = arxiu->uid;
                    break;
                }
                arxiu = arxiu->next;
            }
            if(arxiu == NULL){
                // takes as parameter the firstUser and the name and pushes it in the start.
                tableU[temp] = push_User(tableU[temp], word1);
                tempWord1 = UID;
            }
            arxii = tableI[tempI];
            while (arxii != NULL) {
                if((arxii->iname).compare(word2)==0){
                    tempWord2 = arxii->iid;
                    break;
                }
                arxii = arxii->next;
            }
            if(arxii == NULL){
                tableI[tempI] = push_Item(tableI[tempI], word2);
                tempWord2 = IID;
            }
            writeFile << tempWord1 << " " << tempWord2 << " " << rating << " " << time << endl;
            }
        }
    file.close();
    writeFile.close();
    return ret;
}

int return_id (char* str, char attribute)
{
    int sum =0;
    int temp=0;
    int ret = -1;
    
    for(int d=0; str[d] != '\0';d++){
        sum = sum + str[d];
    }
    temp = sum % C;
    if (attribute == 'u'|| attribute == 'U'){
        arxiu = tableU[temp];
        while(arxiu != NULL){
            if((arxiu->uname).compare(str)==0){
                ret = arxiu->uid;
            }
            arxiu = arxiu->next;
        }
    }
    if(attribute == 'i'|| attribute == 'I'){
        arxii = tableI[temp];
        while(arxii != NULL){
            if((arxii->iname).compare(str)==0){
                ret = arxii->iid;
            }
            arxii = arxii->next;
        }
    }
    return ret;
}

void destroy()
{
    deiktisUser tempUser;
    deiktisItem tempItem;
    for(int i = 0; i < C; i++){
        arxiu = tableU[i];
        while(arxiu != NULL){
            tempUser = arxiu->next;
            delete arxiu;
            arxiu = tempUser;
        }
        arxii = tableI[i];
        while(arxii != NULL){
            tempItem = arxii->next;
            delete arxii;
            arxii = tempItem;
        }
    }
}
