#include <fstream>
#include <string>
#include <vector>
void initialize (int B);
int create_id (char* input_file, char* output_file);
int return_id (char* str, char attribute);
void destroy();

typedef struct user* deiktisUser;
typedef struct item* deiktisItem;

typedef struct user{
    std::string uname;
    int uid;
    deiktisUser  next;
    
}user;
typedef struct item{
    std::string iname;
    int iid;
    deiktisItem next;
    
}item;


