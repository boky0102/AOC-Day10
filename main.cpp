#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using pathMap = std::vector<std::vector<int>>;

enum direction {
        LEFT,
        RIGHT,
        TOP,
        BOTTOM
};


bool pathValid(int posX, int posY, direction dir, pathMap &map){
    auto width = map[0].size();
    auto height = map.size();

    if(dir == direction::LEFT){
        if(posX - 1 < 0){
            return false;
        }
        if(map[posY][posX - 1] != map[posY][posX] + 1){
            return false;
        }
        return true;
    }

    if(dir == direction::RIGHT){
        if(posX + 1 == width){
            return false;
        }

        if(map[posY][posX + 1] != map[posY][posX] + 1){
            return false;
        }
        return true;
    }

    if(dir == direction::TOP){
        if(posY - 1 < 0){
            return false;
        }

        if(map[posY - 1][posX] != map[posY][posX] + 1){
            return false;
        }
        return true;
    }

    if(dir == direction::BOTTOM){
        if(posY + 1 >= height){
            return false;
        }

        if(map[posY + 1][posX] != map[posY][posX] + 1){
            return false;
        }
        return true;
    }

    return true;
}


// if no path is found return 0 else return += findPath;
void findPath(int posX, int posY, pathMap &map, int pathStep, int& sum){
    if(pathStep == 9){
        sum++;
        //map[posY][posX] = -1; part1 :D
    }

    if(pathValid(posX, posY, direction::RIGHT, map)){
        findPath(posX + 1, posY, map, pathStep + 1, sum);
    }

    if(pathValid(posX, posY, direction::LEFT, map)){
        findPath(posX - 1, posY, map, pathStep + 1, sum);
    }

    if(pathValid(posX, posY, direction::TOP, map)){
        findPath(posX, posY - 1, map, pathStep + 1, sum);
    }

    if(pathValid(posX, posY, direction::BOTTOM, map)){
        findPath(posX, posY + 1, map, pathStep + 1, sum);
    }

    return;

}

void resetPathMap(pathMap &map){
    for(auto& mapLine: map){
        for(auto& point: mapLine){
            if(point == -1){
                point = 9;
            }
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::ifstream ifs("dummy.txt");

    std::string line;

    pathMap trails;

    while(std::getline(ifs, line)){
        std::vector<int> linevec;
        for(const auto& elem: line){
            int elint = elem - '0';
            linevec.emplace_back(elint);
        }

        trails.emplace_back(linevec);
    }

    int y = 0;


    int totalSum = 0;

    for(const auto& ln : trails){
        int x = 0;
        for(const auto& elem: ln){
            if(elem == 0){
                int sum = 0;
                findPath(x, y, trails, 0,sum);
                totalSum += sum;
                resetPathMap(trails);
            }
            x++;
        }
        y++;
    }

    std::cout << "TOTAL SUM :" << totalSum << std::endl;
    return 0;
}
