#include <iostream>
#include <string>
#include <vector>
#include <ctime>

std::vector<std::string> roomTypes = {"bedroom","kitchen","bathroom","child room","living"};
std::vector<std::string> houseTypes = {"dwelling","garage","barn","bath"};
struct room{
    std::string type;
    double area;
};

double roomInit(room& someRoom){
    int n = roomTypes.size();
    someRoom.type = roomTypes[rand()%5];
    someRoom.area = (float) 50*rand()/RAND_MAX+10;
    return someRoom.area;

}

struct floor{
    std::vector<room> rooms;
    double ceilingHeight;
};

double floorInit(floor& someFloor){
    int n = rand()%3+2;
    someFloor.rooms.resize(n);
    double livingSpace = 0;

    for(int i = 0; i < n; i++){
        livingSpace+= roomInit(someFloor.rooms[i]);
    }
    someFloor.ceilingHeight = (float) 2*rand()/RAND_MAX+2;
    return livingSpace;

}
struct house{
    std::vector<floor> floors;
    std::string type;
    double area;
    bool oven;
};

double houseInit(house& someHouse, std::string typeOfHouse){
    someHouse.type = typeOfHouse;
    int n = rand()%3+1;
    someHouse.floors.resize(n);
    double livingSpace = 0;

    double max = 0;

    for(int i = 0; i < n; i++){

        double sM = floorInit(someHouse.floors[i]);
        if(sM > max) {
            max = sM;
        }

        livingSpace+=sM;

    }
    someHouse.area = max;
    someHouse.oven = (rand()%2 == 1);
    return livingSpace;
};

//ввести структуру "участок"

struct homestead{
    int number;
    std::vector<house> houses;
    double area;

};
double homesteadInit(homestead& someHomestead, int num){
    someHomestead.number = num;
    int n = rand()%5+1;
    someHomestead.houses.resize(n);
    int livingSpace = houseInit(someHomestead.houses[0], houseTypes[0]);
    someHomestead.area = someHomestead.houses[0].area;
    for(int i = 1; i < n; i++){
        livingSpace+= houseInit(someHomestead.houses[i], houseTypes[rand() % 4]);
        someHomestead.area += someHomestead.houses[i].area;
    }
    someHomestead.area*=(float) rand()/RAND_MAX+1;

    return livingSpace;

}

struct village{
    std::string name;
    std::vector<homestead> homesteads;
    double area;
    double livingSpace;
};

void villageInit(village& someVillage, std::string someName){
    someVillage.name = someName;
    int n = rand()%20+5;
    someVillage.homesteads.resize(n);
    someVillage.livingSpace = 0;
    someVillage.area = 0;
    for(int i = 0; i < n; i++){
        someVillage.livingSpace+= homesteadInit(someVillage.homesteads[i], i);
        someVillage.area+= someVillage.homesteads[i].area;
    }
    someVillage.area*=(float) 0.2 * rand()/RAND_MAX+1;


}



int main() {
    std::srand(std::time(nullptr));
    double x;
    village someVillage;
    villageInit(someVillage,"New Vasyuki");
    std::cout << "Ratio New Vasyuki livingSpace to total area "<< (float) someVillage.livingSpace/someVillage.area << std::endl;
    std::cout << "Numbers of homesteads " << someVillage.homesteads.size() << std::endl;
    for(int i = 0; i < someVillage.homesteads.size(); i++){
        std::cout << "homestead # " << someVillage.homesteads[i].number <<" Number of buildings "<< someVillage.homesteads[i].houses.size() << std::endl;
    }

    return 0;
}
