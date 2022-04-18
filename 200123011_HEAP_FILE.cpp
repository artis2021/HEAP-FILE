#include<bits/stdc++.h>
using namespace std;
class Page{
    int numRecords;
    int freeSpacePointer;
    // next and prev are also there
    int freeSpace;
    vector<int> begining;
    vector<int> data;
    public:
    Page(int size){
        numRecords = 0;
        freeSpacePointer = 0;
        freeSpace = size - 16;
    }
    bool insert(int key, int size){
        if(freeSpace>=size+4){
            begining.push_back(freeSpacePointer);
            freeSpacePointer+=size;
            data.push_back(key);
            numRecords++;
            freeSpace = freeSpace - (size+4);
            return true;
        }
        return false;
    }
    int search(int key){
        for(int i=0; i<numRecords; i++){
            if(key==data[i])
            return i;
        }
        return -1;
    }
    int getNumRecords(){
        return numRecords;
    }
};
class HeapFile{
    vector<Page> pages;
    int pageSize;
    public:
    HeapFile(int size){
        pageSize = size;
    }
    int insert(int key, int size){
        for(int i=0; i<pages.size(); i++){
            if(pages[i].insert(key,size)){
                return 0;
            }
        }
        pages.push_back(Page(pageSize));
        pages[pages.size()-1].insert(key,size);
        return 0;
    }
    void search(int x){
        bool isFound = false;
        int slotId = 0;
        int pageId = 0;
        for(int i=0; i<pages.size(); i++){
            slotId = pages[i].search(x);
            if(slotId!=-1){
               isFound = true;
               pageId = i;
               break;
            }
        }
        if(isFound){
            cout<<pageId<<" "<<slotId<<"\n";
        }else{
            cout<<"-1 -1\n";
        }
    }
    void status(){
        cout<<pages.size()<<" ";
        for(int i=0; i<pages.size(); i++){
            cout<<pages[i].getNumRecords()<<" ";
        }
        cout<<"\n";
    }
};
int main(){
    int pageSize;
    cin>>pageSize;
    HeapFile h(pageSize);
    int opCode;
    while(true){
        cin>>opCode;
        switch(opCode){
            case 1:{
                int size,key;
                cin>>size>>key;
                h.insert(key,size);
            }
            break;
            case 2:{
                h.status();
            }
            break;
            case 3:{
                int key;
                cin>>key;
                h.search(key);
            }
            break;
            case 4:{
                return 0;
            }

        }
    }

}
