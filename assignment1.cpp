//
// Christina Cleveland
// Assignment 1
// Lecture 300: Instructor Maciej Zagrodzki
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
//
//Defining struct used to store info. for each item
//
struct items{
    std::string category;
    bool forSale;
    int price;
};
//
//Function used to delete an element in an array at a given index value
//
void deleteArrayElem(items arr[100], int index, int &numElem){
    for(int i = index; i <numElem-1; ++i){ //starting at the given index move through array and
        arr[i] = arr[i+1]; //shift values forward, deleting the value at given index by writing over it with the following element
    }
    --numElem;//decrease by 1 the given number of elements in the array
};
//
//Function used to search for an items match in an array of items, where a match is an item with the same
//category, opposite forSale, and appropriate price depending on the forSale value
//returns either -1 if a match was not found or the index value of the match if a match was found
//
int searchForItem(items arr[], int totItems, items newItem){
    if(totItems == 0){ //if arr is empty, don't search, add item to arr
        return -1;
    }
    for(int i = 0; i<=totItems; ++i){ //move through array of items, 1 at a time, look for match
        if(arr[i].category == newItem.category){ //check category matches
            if(arr[i].forSale == true && newItem.forSale == false){ //new item is for sale so check that match item is wanted
                if(arr[i].price <= newItem.price){ //check that wanted price is >= offered price
                    return i; //if all ifs satisfied, return index
                }
            }
            else if(arr[i].forSale == false && newItem.forSale == true){ //new item is wanted so check that match item is for sale
                if(arr[i].price >= newItem.price){ //check that wanted price is >= offered price
                    return i; //if all ifs satisfied, return index
                }
            }
        }
    }
    return -1;
};
//
//Function used to print an array of items to the terminal (prints each items' data members on one line)
//
void displayItems(items arrItems[], int totItems){
    std::cout<<"#"<<std::endl;
    for(int i = 0; i<totItems; ++i){
        std::cout<<arrItems[i].category;
        if(arrItems[i].forSale){
            std::cout<<", for sale, ";
        }
        else{
            std::cout<<", wanted, ";
        }
        std::cout<<arrItems[i].price<<std::endl;
    }
    std::cout<<"#"<<std::endl;
};
//
//main function, takes command line input for the file to open, calls functions defined above to open the given file
//check if the current items instance has a match in the array of items where the items are stored, if a match is found
//output the sale info to the terminal and deletes the match from the array, if no match is found add the new item to the array
//
int main(int argc, char* argv[]){
    std::ifstream f;
    int totItems = 0;
    int sizeItemsArr = 100;
    items arrItems[sizeItemsArr];
    f.open(argv[1]); //opens given file for reading
    if(f.fail()){ //don't try to do all this work if the file failed to open
        std::cout<<"File failed to open: "<<argv[1]<<std::endl;
        return 0;
    }
    while(!f.eof()&&totItems<sizeItemsArr){ //while loop to move through file, line by line, until the end of the file or the max num of items is reach based on items array size
        items holder; //temp instance of items used to hold the info from the current line of the file
        std::string saleWant; //string used to store 'For sale' or 'wanted' string, to be converted to bool
        std::getline(f, holder.category, ','); //read the category
        std::getline(f,saleWant, ','); //read 'for sale' or 'wanted'
        if(saleWant == " for sale"){ //convert string 'for sale' to bool true
            holder.forSale = true;
        }
        else{ //convert string 'wanted' to bool false
            holder.forSale = false;
        }
        std::string priceHolder; //string used to hold the price info before converting to int to store in holder.price
        std::getline(f, priceHolder);
        if(priceHolder.length()==0){ //don't try to convert an empty string to an int cause it won't work
            break;
        }
        holder.price = std::stoi(priceHolder); //assign the price variable for holder
        int result = searchForItem(arrItems, totItems, holder); //calls function to search through the items array for a match for the holder item, stores result as an int
        if(result == -1){ //if not match
            arrItems[totItems] = holder; //add holder to items arrya
            ++totItems; //increase total items by 1
        }
        else{ //if match was found, print the sale info, delete the match from the items array
            if(holder.forSale){
                std::cout<<holder.category<<" "<<holder.price<<std::endl;
            }
            else{
                std::cout<<arrItems[result].category<<" "<<arrItems[result].price<<std::endl;
            }
            deleteArrayElem(arrItems, result, totItems); //deletes the match
        }
    }
    f.close();
    displayItems(arrItems, totItems); //call display function to see remaining items in array
};
