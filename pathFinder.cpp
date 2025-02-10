#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

// To convert coordinates to 1D index
int toIndex(int x, int y, int width) {
    return y * width + x;
}

bool FindPath(std::pair<int, int> Start,
      std::pair<int, int> Target,
      const std::vector<int>& Map,
      std::pair<int, int> MapDimensions,
      std::vector<int>& OutPath) {
                  
          int mapWidth = MapDimensions.first;
          int mapHeight = MapDimensions.second;
          
          std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
          
          if (Start == Target) {
              return true;   // path with 0 length
          }
          
          std::queue<std::pair<int, int>> queue;
          std::unordered_map<int, int> parent;
          std::vector<std::vector<bool>> visited(mapHeight, std::vector<bool>(mapWidth, false));
          
          queue.push(Start);
          visited[Start.second][Start.first] = true;
          
          bool pathFound = false;
          
          while (!queue.empty()) {
              auto current = queue.front();
              queue.pop();
              
              int currentX = current.first;
              int currentY = current.second;
              
              for (const auto& direction : directions) {
                  int nextX = currentX + direction.first;
                  int nextY = currentY = direction.second;
                  
                  // Check if traversable
                  if (nextX >= 0 && nextY >= 0 && nextX < mapWidth && nextY < mapHeight && 
                        !visited[nextY][nextX] && Map[toIndex(nextX, nextY, mapWidth)] == 1) {
                            
                        visited[nextY][nextX] = true;
                        parent[toIndex(nextX, nextY, mapWidth)] = toIndex(currentX, currentY, mapWidth);
                        queue.push({nextX, nextY});
                        
                        // If target reached
                        if (nextX == Target.first && nextY == Target.second) {
                            pathFound = true;
                            break;
                        }
                    }
                }
                
                if (pathFound) 
                    break;
            }
            
            if (!pathFound) {
                OutPath.clear();
                return false;
            }
                
            int currentIndex = toIndex(Target.first, Target.second, mapWidth);
            while (currentIndex != toIndex(Start.first, Start.second, mapWidth)) {
                OutPath.push_back(currentIndex);
                currentIndex = parent[currentIndex];
            }
            
            OutPath.push_back(toIndex(Start.first, Start.second, mapWidth));
            
            std::reverse(OutPath.begin(), OutPath.end());
            return true;
        }
        
int main() {
    int mapWidth, mapHeight;
    std::cout << "Enter the map dimentions (width and height): ";
    std::cin >> mapWidth >> mapHeight;
    
    std::vector<int> Map(mapWidth * mapHeight);
    std::cout << "Enter the map: ";
    for (int i = 0; i < mapWidth * mapHeight ; i++) {
        std::cin >> Map[i];
    }
    
    int startX, startY, targetX, targetY;
    std::cout << "Enter start coordinates: ";
    std::cin >> startX >> startY;
    
    std::cout << "Enter target coordinates: ";
    std::cin >> targetX >> targetY;
    
    std::pair<int, int> Start = {startX, startY}; 
    std::pair<int, int> Target = {targetX, targetY};
    std::pair<int, int> MapDimensions = {mapWidth, mapHeight};
    std::vector<int> OutPath;
    
    bool pathFound = FindPath(Start, Target, Map, MapDimensions, OutPath);
    
    if(pathFound) {
        std::cout << "Path found \n Path length: " << OutPath.size() - 1 << "\n"; //  Path length excludes the starting point
        std::cout << "Path: {";
        for (int i : OutPath) {
            std::cout << i << ", ";
        }
        std::cout << "} \n";
    } else {
        std::cout << "No path found \n";
    }
    
    return 0;
}