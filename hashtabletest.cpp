#include <cctype>
#include <climits>
#include <iostream>
#include <string>

using namespace std;

int hashTableSize = 100;

struct item {
	string value = "";
	item* next = NULL;
};

item hashTable[100];

//Prototype
int FindValueIndex(string value);
void InsertValue(string value);
void Command();
void RouteCommand(string cmd);
void HelpMenu();
string tolower(string str);
void Add();
void Display();
void Remove();
void Find();

int main(int argc, char** argv){
	cout << "=====HASH TABLE EXAMPLE=====" << endl;
	cout << "Enter \"Help\" for help menu." << endl;
	Command();	
	return 0;
}
string lowercase(string str){
	int index = 0;
	for(auto& letter : str){
		str[index++] = tolower(letter);
	}
	return str;
}
void Find(){
	string value = "";
	cout << "What key would you like to find:";
	cin >> value;
	int index = FindValueIndex(value);
	item* current = &hashTable[index];
	cout << "------------------------------------------" << endl;
	cout<< "[" << index + 1 << "] " << "[" << current->value;
	while(current->next != NULL){
		current = current->next;
		cout << "," << current->value;
	}
	cout << "]" << endl;
	Command();
}	
void HelpMenu(){
	cout << "==========HELP MENU========" << endl;
	cout << "Help\t\tDisplay this help menu" << endl;
	cout << "Add\t\tEnter new item into hash table" << endl;
	cout << "Remove\t\tRemove item from hash table" << endl;
	cout << "Display\t\tDisplay contents of hash table" << endl;
	cout << "Quit\t\tExit the program" << endl;
	cout << "Find\t\tFind the bucket that contains the given key" << endl;
	Command();
}
void RouteCommand(string cmd){
	cmd = lowercase(cmd);
	if(cmd == "help"){
		HelpMenu();
	}else if(cmd == "add"){
		Add();
	}else if(cmd == "quit"){
		exit(0);
	}else if(cmd == "display"){
		Display();
	}else if(cmd == "remove"){
		Remove();
	}else if(cmd == "find"){
		Find();
	}else{
		cin.clear();
		Command();
	}
}
void Display(){
	int index = 0;
	for(auto& curItem : hashTable){
	cout << "------------------------------------------" << endl;
	cout << "[" << index + 1 << "] : " << "[" << hashTable[index].value;
	item* next = hashTable[index].next;
		while(next != NULL){
			cout << "," << next->value;
			next = next->next;
		}
		cout << "]" << endl;
		index++;
	}
	Command();
}
void Remove(){
	int index = '\0';
	string value = "";
	while(value == ""){
		cout << "Value to Remove: ";
		cin >> value;
	}
	index = FindValueIndex(value);
	item* current = &hashTable[index];
	char ans;
	while(1){
		cout << "Would you like to remove " << current->value << "?";
		cin >> ans;
		if(tolower(ans) == 'y'){
			current->value = "";
			current->next = NULL;
			break;
		}else{
			if(current->next != NULL){
				current = current->next;
			}else{
				cout << "There are no more items that you can remove." << endl;
			}
		}
	}
	Command();
}
void Add(){
	string value = "";
	while(value == ""){
		cout << "New Value:";
		cin >> value;
	}
	cout << "Inserting \"" << value << "\" into hash table." << endl;
	InsertValue(value);
	Command();
}	
void Command(){
	string cmd = "";
	cout << "Command:";
	cin >> cmd;
	cin.clear();
	RouteCommand(cmd);	
}
void InsertValue(string value){
	int index = FindValueIndex(value);
	if(hashTable[index].value != ""){
		char resp;
		while(1){
			cout << "There is a matching permutation of the key. Replace?[Y/N]:";
			cin >> resp;
			if(resp  == 'y'){
				cout << endl;
				item* current = &hashTable[index];
				char ans;
				while(1){
					cout << "Replace " << current->value << "?";
					cin >> ans;
					if(tolower(ans) == 'y'){
						current->value = value;
						break;
					}else{
						if(current->next != NULL){
							current = current->next;
						}else{
							cout << "There aren't any more options." << endl;
							break;
						}
					}
				}
				break;
			}else if(tolower(resp) == 'n'){
				char resp2;
				while(1){
					cout << "Would you like to add it as a unique key to the bucket [Y/N]:";
					cin >> resp2;
					if(tolower(resp2) == 'y'){
						item* current = &hashTable[index];
						while(current->next != NULL){
							current = current->next;
						}
						current->next = new item;
						current->next->value = value;
						break;
					}else{
						cout << endl;
						break;
					}
				}
				break;
			}
		}
	}else{
		hashTable[index].value = value;	
	}
}
int FindValueIndex(string value){
	int index = 0;
	for(auto& letter : value){
		index += (int)letter;
	}
	index %= hashTableSize;
	return index;
}
